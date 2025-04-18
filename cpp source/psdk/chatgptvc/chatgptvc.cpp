#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <sstream>
#include <wchar.h>
#include <fstream>
#include <map>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

// Helper to read configuration from a file
std::map<std::string, std::string> readConfig(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open config file." << std::endl;
        return config;
    }

    std::string line;
    while (getline(file, line)) {
        size_t pos = line.find("=");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config[key] = value;
        }
    }

    file.close();
    return config;
}

// Helper to read full request body
std::string receiveRequest(SOCKET clientSocket) {
    char buffer[4096];
    std::string request;
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        request.append(buffer, bytesReceived);
        if (request.find("\r\n\r\n") != std::string::npos) break; // header end
    }
    return request;
}

// Extract URL-decoded body
std::string urlDecode(const std::string& str) {
    std::string ret;
    char ch;
    int i, ii;
    for (i = 0; i < str.length(); i++) {
        if (int(str[i]) == 37) {
            sscanf_s(str.substr(i + 1, 2).c_str(), "%x", &ii); // Use sscanf_s for safety
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
        else if (str[i] == '+') {
            ret += ' ';
        }
        else {
            ret += str[i];
        }
    }
    return ret;
}

// Converts a char* string to wchar_t*
std::wstring toWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

std::string sendToGroq(const std::string& userMessage, const std::string& assistantMessage, const std::string& model, int maxTokens, const std::string& apiKey) {
    std::wstring wideApiKey = toWString(apiKey);
    std::wstring wideHost = L"api.openai.com";

    HINTERNET hSession = InternetOpenW(L"GroqProxy", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hSession) return "InternetOpen failed";

    HINTERNET hConnect = InternetConnectW(hSession, wideHost.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) return "InternetConnect failed";

    const wchar_t* acceptTypes[] = { L"*/*", NULL };
    HINTERNET hRequest = HttpOpenRequestW(hConnect, L"POST", L"/openai/v1/chat/completions", NULL, NULL, acceptTypes, INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, 0);
    if (!hRequest) return "HttpOpenRequest failed";

    std::string postData =
        "{"
        "\"model\":\"" + model + "\","
        "\"messages\":["
        "{\"role\":\"system\",\"content\":\"" + assistantMessage + "\"},"
        "{\"role\":\"user\",\"content\":\"" + userMessage + "\"}"
        "],"
        "\"max_tokens\":" + std::to_string(maxTokens) + ""
        "}";

    // Create the authorization header by concatenating strings
    std::wstring wideHeaders = L"Content-Type: application/json\r\nAuthorization: Bearer " + wideApiKey;

    BOOL sent = HttpSendRequestW(hRequest, wideHeaders.c_str(), (DWORD)wideHeaders.length(), (LPVOID)postData.c_str(), (DWORD)postData.length());
    if (!sent) return "HttpSendRequest failed";

    char buffer[4096];
    DWORD bytesRead;
    std::string response;

    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = 0;
        response += buffer;
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);

    return response;
}

void handleClient(SOCKET clientSocket, const std::map<std::string, std::string>& config) {
    std::string request = receiveRequest(clientSocket);

    if (request.find("POST /chat") != std::string::npos) {
        std::string body = request.substr(request.find("\r\n\r\n") + 4);
        std::string userInput;

        size_t inputPos = body.find("input=");
        if (inputPos != std::string::npos) {
            userInput = body.substr(inputPos + 6);
        }
        else {
            std::string error = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\n\r\n{\"error\":\"Message is required\"}";
            send(clientSocket, error.c_str(), error.length(), 0);
            closesocket(clientSocket);
            return;
        }

        userInput = urlDecode(userInput);

        std::string assistantMessage = config.at("assistant_message");
        std::string model = config.at("model");
        int maxTokens = std::stoi(config.at("max_tokens"));
        std::string apiKey = config.at("api_key");

        std::string groqResponse = sendToGroq(userInput, assistantMessage, model, maxTokens, apiKey);

        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " << groqResponse.length() << "\r\n\r\n" << groqResponse;

        std::string fullResponse = ss.str();
        send(clientSocket, fullResponse.c_str(), fullResponse.length(), 0);
    }
    else {
        std::string notFound = "HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\n\r\n{\"error\":\"Route not found\"}";
        send(clientSocket, notFound.c_str(), notFound.length(), 0);
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Read configuration from file
    std::map<std::string, std::string> config = readConfig("config.cfg");

    if (config.empty()) {
        std::cerr << "Error reading configuration." << std::endl;
        return 1;
    }

    // Retrieve the port from the configuration
    int port = 3310;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    // std::cout << "ChatGPT Proxy server running at http://localhost:" << port << std::endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            handleClient(clientSocket, config);
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
