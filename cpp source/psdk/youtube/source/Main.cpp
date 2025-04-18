#include "plugin.h"
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <fstream>
#include "CHud.h"
#include <thread>
#include <bass.h>
#include <map>
#include <sstream>

#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "bass.lib")

using namespace plugin;

bool isTyping = false;
std::string userInput;
bool mp3IsOpen = false; // Track if MP3 is open

// Configuration variables
std::string apiKey;
int startKey = VK_F7;  // Default start key (F7)
int stopKey = VK_F8;   // Default stop key (F8)
// Logging function
void Log(const std::string& text) {
    std::ofstream log("youtube_plugin_log.txt", std::ios::app);
    log << text << std::endl;
    log.close();
}
// Function to load configuration from config.cfg
void LoadConfig() {
    std::ifstream configFile("config.cfg");
    if (!configFile.is_open()) {
        Log("Error opening config.cfg.");
        return;
    }

    std::map<std::string, std::string> config;
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream lineStream(line);
        std::string key, value;

        // Skip empty lines and lines starting with #
        if (line.empty() || line[0] == '#') continue;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
            // Trim spaces from both key and value (if any)
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(value.find_last_not_of(" \t") + 1);
            config[key] = value;
        }
    }

    // Set the variables based on config file
    if (config.find("youtubeapi_key") != config.end()) apiKey = config["youtubeapi_key"];
    if (config.find("startkey") != config.end()) startKey = std::stoi(config["startkey"]); // Convert string to integer
    if (config.find("stopkey") != config.end()) stopKey = std::stoi(config["stopkey"]); // Convert string to integer

    configFile.close();
    Log("Configuration loaded.");
}




// YouTube search function
std::string YouTubeSearch(const std::wstring& query) {
    std::wstring path = L"/youtube/v3/search?part=snippet&type=video&maxResults=1&q=" + query + L"&key=" + std::wstring(apiKey.begin(), apiKey.end());

    std::string result;
    Log("Starting YouTubeSearch...");

    HINTERNET hSession = WinHttpOpen(L"YTSearch", WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
    if (!hSession) return "";

    HINTERNET hConnect = WinHttpConnect(hSession, L"www.googleapis.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) return "";

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(), NULL, WINHTTP_NO_REFERER, NULL, WINHTTP_FLAG_SECURE);
    if (!hRequest) return "";

    if (WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, 0) && WinHttpReceiveResponse(hRequest, NULL)) {
        DWORD size = 0;
        do {
            DWORD downloaded = 0;
            WinHttpQueryDataAvailable(hRequest, &size);
            if (!size) break;
            char* buffer = new char[size + 1];
            ZeroMemory(buffer, size + 1);
            WinHttpReadData(hRequest, buffer, size, &downloaded);
            result.append(buffer, downloaded);
            delete[] buffer;
        } while (size > 0);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    Log("YouTubeSearch result: " + result);
    return result;
}

// Function to extract values from the JSON response
std::string Extract(const std::string& json, const std::string& key) {
    Log("Extracting key: " + key);
    size_t keyPos = json.find(key);
    if (keyPos == std::string::npos) return "";

    size_t start = json.find("\"", keyPos + key.length());
    size_t end = json.find("\"", start + 1);
    return json.substr(start + 1, end - start - 1);
}

// Function to download MP3 from YouTube
void DownloadMP3(const std::string& videoId) {
    Log("Downloading video ID: " + videoId);

    std::string cmd = "yt-dlp -x --audio-format mp3 -o \"temp.%(ext)s\" https://youtube.com/watch?v=" + videoId;
    std::wstring wcmd(cmd.begin(), cmd.end());

    STARTUPINFOW si = { sizeof(si) };
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi = {};
    if (!CreateProcessW(NULL, &wcmd[0], NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        Log("Error creating process: " + std::to_string(GetLastError()));
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    Log("Download complete.");
    CHud::SetHelpMessage("Downloading complete. Ready to play.", true, false);
}

bool bassInitialized = false; // Global flag to track BASS initialization

// Function to play MP3 file using BASS
void PlayMP3() {
    Log("Attempting to play temp.mp3");

    if (GetFileAttributesA("temp.mp3") == INVALID_FILE_ATTRIBUTES) {
        Log("temp.mp3 file not found.");
        CHud::SetHelpMessage("Failed to find MP3.", true, false);
        return;
    }

    // Initialize BASS only if it is not already initialized
    if (!bassInitialized) {
        if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
            Log("BASS initialization failed: " + std::to_string(BASS_ErrorGetCode()));
            CHud::SetHelpMessage("Failed to initialize BASS.", true, false);
            return;
        }
        bassInitialized = true; // Set the flag to true after initializing BASS
    }

    // Load the MP3 file using BASS
    HSTREAM stream = BASS_StreamCreateFile(FALSE, "temp.mp3", 0, 0, 0);
    if (!stream) {
        Log("Failed to load MP3: " + std::to_string(BASS_ErrorGetCode()));
        CHud::SetHelpMessage("Failed to load MP3.", true, false);
        BASS_Free();
        bassInitialized = false; // Reset the flag if BASS fails to load the MP3
        return;
    }

    // Play the MP3 file
    if (!BASS_ChannelPlay(stream, FALSE)) {
        Log("Failed to play MP3: " + std::to_string(BASS_ErrorGetCode()));
        CHud::SetHelpMessage("Failed to play MP3.", true, false);
        BASS_StreamFree(stream);
        BASS_Free();
        bassInitialized = false; // Reset the flag if the playback fails
        return;
    }

    mp3IsOpen = true; // Mark MP3 as open
    CHud::SetHelpMessage("Now Playing!", true, false);
    Log("MP3 playback started.");
}

// Function to stop the music
void StopMusic() {
    Log("Stopping music...");

    if (!mp3IsOpen) {
        Log("MP3 alias not open, nothing to stop.");
        CHud::SetHelpMessage("No music is currently playing.", true, false);
        return;
    }

    BASS_ChannelStop(0);  // Stop all channels
    BASS_Free();  // Free BASS resources
    mp3IsOpen = false;
    CHud::SetHelpMessage("Music stopped.", true, false);
    Log("Music stopped.");
}

// Main plugin class
class youtube {
public:
    youtube() {
        Log("Plugin initialized.");

        // Load config on startup
        LoadConfig();

        Events::gameProcessEvent += [] {
            if (GetAsyncKeyState(startKey) & 1) {
                // Start key (user-defined in config)
                if (!isTyping) {
                    userInput.clear();
                    isTyping = true;
                    CHud::SetHelpMessage("Type song name... then press Enter", true, false);
                    return;
                }
            }

            if (GetAsyncKeyState(stopKey) & 1) {
                // Stop key (user-defined in config)
                StopMusic();
                return;
            }

            if (isTyping) {
                for (int key = 'A'; key <= 'Z'; key++) {
                    if (GetAsyncKeyState(key) & 1) {
                        userInput += (char)key;
                        CHud::SetHelpMessage(("Typing: " + userInput).c_str(), true, false);
                        return;
                    }
                }
                for (int key = '0'; key <= '9'; key++) {
                    if (GetAsyncKeyState(key) & 1) {
                        userInput += (char)key;
                        CHud::SetHelpMessage(("Typing: " + userInput).c_str(), true, false);
                        return;
                    }
                }

                if (GetAsyncKeyState(VK_SPACE) & 1) {
                    userInput += ' ';
                    CHud::SetHelpMessage(("Typing: " + userInput).c_str(), true, false);
                    return;
                }

                if ((GetAsyncKeyState(VK_BACK) & 1) && !userInput.empty()) {
                    userInput.pop_back();
                    CHud::SetHelpMessage(("Typing: " + userInput).c_str(), true, false);
                    return;
                }

                if (GetAsyncKeyState(VK_RETURN) & 1) {
                    if (userInput.empty()) {
                        CHud::SetHelpMessage("Please enter a song name.", true, false);
                        return;
                    }

                    isTyping = false;

                    std::wstring wquery(userInput.begin(), userInput.end());
                    CHud::SetHelpMessage("Searching...", true, false);
                    Log("Searching for song: " + userInput);

                    std::string json = YouTubeSearch(wquery);
                    std::string videoId = Extract(json, "\"videoId\"");
                    std::string title = Extract(json, "\"title\"");

                    if (videoId.empty()) {
                        Log("Video ID not found. Aborting.");
                        CHud::SetHelpMessage("Video not found.", true, false);
                        return;
                    }

                    Log("Found video: " + title);
                    CHud::SetHelpMessage(title.c_str(), true, false);

                    std::thread downloadThread([videoId]() {
                        DeleteFileA("temp.mp3");
                        DownloadMP3(videoId);
                        PlayMP3();
                        });

                    downloadThread.detach();
                }
            }
            };
    }
} youtubePlugin;
