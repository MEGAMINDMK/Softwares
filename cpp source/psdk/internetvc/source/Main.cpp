#include "plugin.h"
#include "CFont.h"
#include "CHud.h"
#include "CPad.h"
#include <windows.h>
#include <wininet.h>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <map>
#include <locale>
#include <codecvt>
#include "CSprite2d.h"
#include "game_vc/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "game_vc/stb_image.h"

#pragma comment(lib, "wininet.lib")

using namespace plugin;

class GoogleSearchBrowser {
public:
    GoogleSearchBrowser() {
        LoadConfig();

        Events::gameProcessEvent += [this]() {

            //  ADD THIS RIGHT HERE:
            if (GetAsyncKeyState(VK_ESCAPE) & 1 && active) {
                active = false;
                return;
            }

            if (GetAsyncKeyState(keyToggleSearch) & 1) {
                ResetInterface();
            }
            

            if (!active) {
                CPad::GetPad(0)->DisablePlayerControls = false;  // Re-enable controls when not active
                return;
            }

            HandleTyping();
            HandleNavigation();
            CPad::GetPad(0)->DisablePlayerControls = true;  // Disable controls when active
            };

        Events::drawHudEvent += [this]() {
            DrawUI();
            };
    }


private:
    bool active = false;
    bool typingEnabled = true;
    std::string query;
    std::vector<std::pair<std::string, std::string>> results;
    int selectedIndex = 0;
    int currentPage = 0;
    int resultsPerPage = 5;
    std::mutex resultsMutex;

    bool viewingResult = false;
    std::pair<std::string, std::string> currentResult;

    int searchBarWidth = 1000;
    int searchBarX = 300;
    float fontScale = 1.0f;
    float resultFontScale = 0.7f;
    float resultSpacing = 30.0f;
    std::string apiKey;

    // Configurable keys
    int keyToggleSearch = VK_F7;
    int keySubmitQuery = VK_RETURN;
    int keyBackspace = VK_BACK;
    int keyViewBack = VK_BACK;
    int keyUp = VK_UP;
    int keyDown = VK_DOWN;
    int keyLeft = VK_LEFT;
    int keyRight = VK_RIGHT;
    int keySpace = VK_SPACE;

    int GetVirtualKeyCode(const std::string& name) {
        static std::map<std::string, int> keyMap = {
            {"VK_F1", VK_F1}, {"VK_F2", VK_F2}, {"VK_F3", VK_F3}, {"VK_F4", VK_F4},
            {"VK_F5", VK_F5}, {"VK_F6", VK_F6}, {"VK_F7", VK_F7}, {"VK_F8", VK_F8},
            {"VK_F9", VK_F9}, {"VK_F10", VK_F10}, {"VK_F11", VK_F11}, {"VK_F12", VK_F12},
            {"VK_RETURN", VK_RETURN}, {"VK_BACK", VK_BACK}, {"VK_SPACE", VK_SPACE},
            {"VK_UP", VK_UP}, {"VK_DOWN", VK_DOWN}, {"VK_LEFT", VK_LEFT}, {"VK_RIGHT", VK_RIGHT}
        };
        auto it = keyMap.find(name);
        return it != keyMap.end() ? it->second : -1;
    }

    void LoadConfig() {
        std::ifstream configFile("config.cfg");
        if (!configFile.is_open()) {
            Log("Failed to open config.cfg, using default values.");
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line.find("search_bar_width") != std::string::npos)
                searchBarWidth = std::stoi(line.substr(line.find("=") + 1));
            else if (line.find("font_scale") != std::string::npos)
                fontScale = std::stof(line.substr(line.find("=") + 1));
            else if (line.find("result_font_scale") != std::string::npos)
                resultFontScale = std::stof(line.substr(line.find("=") + 1));
            else if (line.find("result_spacing") != std::string::npos)
                resultSpacing = std::stof(line.substr(line.find("=") + 1));
            else if (line.find("results_per_page") != std::string::npos)
                resultsPerPage = std::stoi(line.substr(line.find("=") + 1));
            else if (line.find("search_bar_x") != std::string::npos)
                searchBarX = std::stoi(line.substr(line.find("=") + 1));
            else if (line.find("googleapi_key") != std::string::npos)
                apiKey = line.substr(line.find("=") + 1);
            else if (line.find("key_toggle_search") != std::string::npos)
                keyToggleSearch = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_submit_query") != std::string::npos)
                keySubmitQuery = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_backspace") != std::string::npos)
                keyBackspace = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_view_back") != std::string::npos)
                keyViewBack = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_up") != std::string::npos)
                keyUp = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_down") != std::string::npos)
                keyDown = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_left") != std::string::npos)
                keyLeft = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_right") != std::string::npos)
                keyRight = GetVirtualKeyCode(line.substr(line.find("=") + 1));
            else if (line.find("key_space") != std::string::npos)
                keySpace = GetVirtualKeyCode(line.substr(line.find("=") + 1));
        }

        configFile.close();
    }

    void ResetInterface() {
        active = true;
        query.clear();
        viewingResult = false;
        {
            std::lock_guard<std::mutex> lock(resultsMutex);
            results.clear();
        }
        selectedIndex = 0;
        currentPage = 0;
        typingEnabled = true;
    }

    void HandleTyping() {
        if (!typingEnabled || viewingResult) return;

        for (int key = 'A'; key <= 'Z'; ++key)
            if (GetAsyncKeyState(key) & 1) query += (char)key;
        for (int key = '0'; key <= '9'; ++key)
            if (GetAsyncKeyState(key) & 1) query += (char)key;

        if (GetAsyncKeyState(keySpace) & 1) query += ' ';
        if (GetAsyncKeyState(keyBackspace) & 1 && !query.empty()) query.pop_back();

        if (GetAsyncKeyState(keySubmitQuery) & 1) {
            std::thread(&GoogleSearchBrowser::PerformSearch, this, query).detach();
            typingEnabled = false;
        }
    }

    void HandleNavigation() {
        std::lock_guard<std::mutex> lock(resultsMutex);
        if (results.empty()) return;

        if (viewingResult) {
            if (GetAsyncKeyState(keyViewBack) & 1) {
                viewingResult = false;
            }
            return;
        }

        if (GetAsyncKeyState(keyUp) & 1 && selectedIndex > 0) selectedIndex--;
        if (GetAsyncKeyState(keyDown) & 1 && selectedIndex < (int)results.size() - 1) selectedIndex++;
        if (GetAsyncKeyState(keyLeft) & 1 && currentPage > 0) currentPage--;
        if (GetAsyncKeyState(keyRight) & 1 && (currentPage + 1) * resultsPerPage < (int)results.size()) currentPage++;

        if (GetAsyncKeyState(keySubmitQuery) & 1 && !results.empty()) {
            currentResult = results[selectedIndex];
            viewingResult = true;
        }
    }

    void DrawUI() {
        if (!active) return;

        if (viewingResult) {
            DrawResultViewer();
            return;
        }

        float y = 60.0f;
        float x = (float)searchBarX;

        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetBackground(false);
        CFont::SetScale(fontScale, 1.5f);
        CFont::SetProportional(true);
        CFont::SetColor(CRGBA(255, 255, 0, 255));
        CFont::SetOrientation(ALIGN_LEFT);

        std::string searchText = "Search: " + query;
        CFont::PrintString(x, y, searchText.c_str());
        y += 40.0f;

        CFont::SetScale(resultFontScale, 1.2f);
        CFont::SetFontStyle(FONT_SUBTITLES);

        int startIndex = currentPage * resultsPerPage;
        int endIndex = std::min(startIndex + resultsPerPage, (int)results.size());

        for (int i = startIndex; i < endIndex; i++) {
            std::string title, url, description;
            std::tie(title, url) = results[i];

            size_t sepPos = title.find(" - ");
            if (sepPos != std::string::npos) {
                description = title.substr(sepPos + 3);
                title = title.substr(0, sepPos);
            }

            std::string formattedTitle = (i == selectedIndex ? "> " : "") + title;

            CFont::SetColor(i == selectedIndex ? CRGBA(0, 255, 0, 255) : CRGBA(255, 255, 255, 220));
            CFont::PrintString(x, y, formattedTitle.c_str());
            y += resultSpacing * 0.9f;

            CFont::SetColor(CRGBA(150, 200, 255, 200));
            CFont::PrintString(x + 20.0f, y, url.c_str());
            y += resultSpacing * 0.8f;

            CFont::SetColor(CRGBA(180, 180, 180, 200));
            CFont::PrintString(x + 20.0f, y, description.c_str());
            y += resultSpacing * 1.2f;
        }

        if (results.size() > resultsPerPage) {
            float paginationY = y + 10.0f;
            CFont::SetScale(0.5f, 1.0f);
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            std::string pageText = "Page " + std::to_string(currentPage + 1) + " / " + std::to_string((results.size() / resultsPerPage) + 1);
            CFont::PrintString(x, paginationY, pageText.c_str());
        }
    }

    void DrawResultViewer() {
        float x = (float)searchBarX;
        float y = 80.0f;

        std::string description = currentResult.first;

        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetBackground(false);
        CFont::SetProportional(true);
        CFont::SetOrientation(ALIGN_LEFT);

        CFont::SetScale(1.0f, 1.5f);
        CFont::SetColor(CRGBA(255, 255, 0, 255));
        CFont::PrintString(x, y, "Viewing Result:");
        y += 50.0f;

        CFont::SetScale(0.8f, 1.2f);
        CFont::SetColor(CRGBA(180, 180, 180, 255));
        CFont::PrintString(x, y, description.c_str());
        y += 40.0f;

        CFont::SetColor(CRGBA(200, 200, 200, 255));
        CFont::SetScale(0.6f, 1.0f);
        CFont::PrintString(x, y, "Press BACKSPACE to return.");
    }

    std::string DecodeUnicode(const std::string& input) {
        std::string output;
        std::stringstream ss;
        for (size_t i = 0; i < input.size(); ++i) {
            if (input[i] == '\\' && i + 5 < input.size() && input[i + 1] == 'u') {
                std::string hex = input.substr(i + 2, 4);
                wchar_t wc = (wchar_t)std::stoi(hex, nullptr, 16);
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
                output += convert.to_bytes(wc);
                i += 5;
            }
            else {
                output += input[i];
            }
        }
        return output;
    }

    std::string SanitizeString(const std::string& input) {
        std::string output;
        std::string decoded = DecodeUnicode(input);
        for (char c : decoded) {
            if ((unsigned char)c >= 32 && (unsigned char)c <= 126)
                output += c;
            else if (c == '\n' || c == '\r' || c == '\t')
                output += ' ';
            else
                output += '?';
        }
        return output;
    }

    void PerformSearch(const std::string& queryText) {
        if (queryText.empty()) return;
        Log("Search query: " + queryText);

        std::string response = FetchFromGoogleSearch(queryText);
        if (response.empty()) return;

        std::vector<std::pair<std::string, std::string>> parsedResults = ParseTitles(response);

        {
            std::lock_guard<std::mutex> lock(resultsMutex);
            results = parsedResults;
        }

        if (parsedResults.empty()) {
            active = false;
        }
        else {
            selectedIndex = std::clamp(selectedIndex, 0, (int)parsedResults.size() - 1);
        }

        query.clear();
    }

    std::string FetchFromGoogleSearch(const std::string& queryText) {
        std::string result;

        HINTERNET hInternet = InternetOpenA("VCBrowser/1.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) return "";

        HINTERNET hConnect = InternetConnectA(hInternet, "google-search74.p.rapidapi.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            return "";
        }

        std::string path = "/?query=" + queryText + "&limit=10&related_keywords=true";
        HINTERNET hRequest = HttpOpenRequestA(hConnect, "GET", path.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
        if (!hRequest) {
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return "";
        }

        std::string headers =
            "x-rapidapi-host: google-search74.p.rapidapi.com\r\n"
            "x-rapidapi-key: " + apiKey + "\r\n";

        if (!HttpSendRequestA(hRequest, headers.c_str(), headers.length(), NULL, 0)) {
            InternetCloseHandle(hRequest);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return "";
        }

        DWORD bytesRead = 0;
        char buffer[4096];

        while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
            result.append(buffer, bytesRead);
        }

        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return result;
    }

    std::vector<std::pair<std::string, std::string>> ParseTitles(const std::string& json) {
        std::vector<std::pair<std::string, std::string>> output;
        std::regex entryRegex(R"(\{\"position\":\d+,\s*\"url\":\"([^\"]+)\",\s*\"title\":\"([^\"]+)\",\s*\"description\":\"([^\"]+)\")");

        std::sregex_iterator iter(json.begin(), json.end(), entryRegex);
        std::sregex_iterator end;
        int count = 0;

        while (iter != end) {
            std::smatch match = *iter;
            if (match.size() >= 4) {
                std::string url = DecodeUnicode(match[1].str());
                std::replace(url.begin(), url.end(), '\\', '/');
                while (url.find("////") != std::string::npos)
                    url.replace(url.find("////"), 4, "//");

                if (url.find("https://") == 0) {
                    url = "https://" + url.substr(8);
                }
                else if (url.find("http://") == 0) {
                    url = "http://" + url.substr(7);
                }

                std::string title = SanitizeString(match[2].str());
                std::string description = SanitizeString(match[3].str());

                output.emplace_back(title + " - " + description, url);
                Log("Result " + std::to_string(++count) + ": " + title + " - " + url);
            }
            ++iter;
        }

        Log("Parsed " + std::to_string(count) + " results.");
        return output;
    }

    void Log(const std::string& message) {
        std::ofstream logFile("log.txt", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

GoogleSearchBrowser googleBrowser;

class EmbeddedImagePlugin {
public:
    CSprite2d sprite;
    RwTexture* texture = nullptr;
    bool textureReady = false;

    // Position and scale for drawing
    float posX = 100.0f;
    float posY = 100.0f;
    float scale = 1.0f;

    // Variables to store the screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // Screen width
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Screen height

    void CreateTextureFromMemory() {
        int width, height, channels;
        unsigned char* pixels = stbi_load_from_memory(
            embeddedImageData,
            static_cast<int>(embeddedImageSize),
            &width, &height, &channels,
            STBI_rgb_alpha
        );
        if (!pixels) {
            OutputDebugStringA("Failed to decode embedded image\n");
            return;
        }

        RwRaster* raster = RwRasterCreate(
            width, height,
            32,
            rwRASTERTYPETEXTURE | rwRASTERFORMAT8888
        );
        if (!raster) {
            stbi_image_free(pixels);
            OutputDebugStringA("Failed to create raster\n");
            return;
        }

        void* dst = RwRasterLock(raster, 0, rwRASTERLOCKWRITE);
        if (dst) {
            memcpy(dst, pixels, width * height * 4);
            RwRasterUnlock(raster);
            texture = RwTextureCreate(raster);
            sprite.m_pTexture = texture;
            textureReady = true;
        }
        else {
            OutputDebugStringA("Failed to lock raster\n");
        }
        stbi_image_free(pixels);
    }

    EmbeddedImagePlugin() {
        Events::initGameEvent += [this] {
            // Adjust the position of the image to the bottom-right corner
            // Position it at the bottom-right corner of the screen
            posX = screenWidth - embeddedImageWidth * scale;  // Adjust for image width
            posY = screenHeight - embeddedImageHeight * scale;  // Adjust for image height

            // Create the texture from memory
            CreateTextureFromMemory();
            };

        Events::drawingEvent += [this] {
            if (!textureReady) return;

            // Compute draw rectangle based on image size and scale
            int w = static_cast<int>(embeddedImageWidth * scale);
            int h = static_cast<int>(embeddedImageHeight * scale);

            sprite.Draw(
                CRect(posX, posY, posX + w, posY + h),
                CRGBA(255, 255, 255, 255)
            );
            };

        Events::d3dLostEvent += [this] {
            if (texture) {
                sprite.Delete();
                textureReady = false;
                texture = nullptr;
            }
            };
    }
} embeddedImagePlugin;
