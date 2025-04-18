#include "plugin.h"
#include "game_vc/CWorld.h"
#include "game_vc/CPed.h"
#include "game_vc/CPlayerPed.h"
#include "game_vc/CEntity.h"
#include "game_vc/CHud.h"
#include "game_vc/CTimer.h"
#include "game_vc/CPools.h"
#include <Windows.h>
#include <math.h>
#include <game_vc/CMessages.h>
#include <vector>
#include <string>
#include "game_vc/CPlaceable.h"
#include "game_vc/CVector.h"
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <wininet.h>
#include <codecvt>

#pragma comment(lib, "wininet.lib")

using namespace plugin;

//==================== CORE SYSTEMS ====================//
/*std::ofstream logFile("log.txt", std::ios::out | std::ios::app);

void Log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}*/

std::wstring StringToWString(const std::string& str) {
    try {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str);
    }
    catch (...) {
        //  Log("String conversion error");
        return L"";
    }
}

std::string CleanResponse(const std::string& response) {
    try {
        std::string cleaned = response;
        const std::string unwanted[] = {
            "\\n", "\\\"", "\\\\", "**", "`",
            "*", "\t", "\u003c", "\u003e", "\\r"
        };

        for (const auto& pattern : unwanted) {
            size_t pos;
            while ((pos = cleaned.find(pattern)) != std::string::npos) {
                cleaned.replace(pos, pattern.length(), "");
            }
        }

        cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(),
            [](unsigned char c) { return !std::isalnum(c) && c != ' '; }),
            cleaned.end());

        return cleaned;
    }
    catch (...) {
        //  Log("Error in CleanResponse");
        return "";
    }
}

std::string SendToNodeServer(const std::string& input) {
    HINTERNET hInternet = nullptr;
    HINTERNET hConnect = nullptr;
    HINTERNET hRequest = nullptr;

    try {
        //    Log("Sending request: " + input);
        hInternet = InternetOpenA("VCMPChatGPT", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) {
            //    Log("InternetOpen failed");
            return "Connection failed";
        }

        hConnect = InternetConnectA(hInternet, "localhost", 3310, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            //   Log("InternetConnect failed");
            return "Connection failed";
        }

        hRequest = HttpOpenRequestA(hConnect, "POST", "/chat", NULL, NULL, NULL,
            INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
        if (!hRequest) {
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            //    Log("HttpOpenRequest failed");
            return "Connection failed";
        }

        std::string postData = "input=" + input;
        const char* headers = "Content-Type: application/x-www-form-urlencoded";

        if (!HttpSendRequestA(hRequest, headers, (DWORD)strlen(headers),
            (LPVOID)postData.c_str(), (DWORD)postData.length())) {
            //  Log("HttpSendRequest failed");
            InternetCloseHandle(hRequest);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return "Request failed";
        }

        std::string response;
        char buffer[2048];
        DWORD bytesRead = 0;

        while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            response += buffer;
        }

        size_t contentPos = response.find("\"content\":\"");
        if (contentPos != std::string::npos) {
            contentPos += 11;
            size_t endPos = response.find("\"", contentPos);
            if (endPos != std::string::npos) {
                return CleanResponse(response.substr(contentPos, endPos - contentPos));
            }
        }

        return "No response";
    }
    catch (...) {
        //  Log("Error in SendToNodeServer");
        if (hRequest) InternetCloseHandle(hRequest);
        if (hConnect) InternetCloseHandle(hConnect);
        if (hInternet) InternetCloseHandle(hInternet);
        return "Error";
    }
}

//==================== PED INTERACTION ====================//
class PedInteraction {
    enum eInteractionState {
        STATE_IDLE,
        STATE_PROMPTED,
        STATE_TYPING,
        STATE_TALKING
    };

    CPed* m_pInteractingPed;
    eInteractionState m_eState;
    unsigned int m_uiLastPressTime;
    std::string m_sCurrentInput;
    std::unordered_map<int, bool> m_keyStates;
    bool m_bLastEState;
    bool m_bLastYState;

public:
    PedInteraction() :
        m_pInteractingPed(nullptr),
        m_eState(STATE_IDLE),
        m_uiLastPressTime(0),
        m_bLastEState(false),
        m_bLastYState(false)
    {
        Events::gameProcessEvent += [this] { Process(); };
    }

private:
    void Process() {
        CPlayerPed* player = FindPlayerPed();
        if (!player || player->m_fHealth <= 0.0f) return;

        switch (m_eState) {
        case STATE_IDLE:    HandleIdle(player); break;
        case STATE_PROMPTED: HandlePrompted(); break;
        case STATE_TYPING:  HandleTyping(); break;
        case STATE_TALKING: HandleTalking(); break;
        }
    }

    void HandleIdle(CPlayerPed* player) {
        if (KeyPressed('E')) {
            if (CPed* ped = FindNearestPed(player)) {
                m_pInteractingPed = ped;
                MakePedFacePlayer(m_pInteractingPed, FindPlayerPed());
                CHud::SetHelpMessage(L"Press ~y~Y~w~ to chat", true, false);
                m_eState = STATE_PROMPTED;
                m_uiLastPressTime = CTimer::m_snTimeInMilliseconds;
            }
        }
    }

    void HandlePrompted() {
        if (!IsPedValid()) {
            Reset();
            return;
        }

        if (KeyPressed('Y')) {
            m_sCurrentInput.clear();
            CHud::SetHelpMessage(L"Type your message (~g~ENTER~w~ to send)", true, false);
            m_eState = STATE_TYPING;
        }
        else if (CTimer::m_snTimeInMilliseconds - m_uiLastPressTime > 5000) {
            Reset();
        }
    }

    void HandleTyping() {
        MakePedFacePlayer(m_pInteractingPed, FindPlayerPed());
        m_pInteractingPed->SetIdle();

        for (int key = 0x20; key <= 0x5A; ++key) {
            if (IsKeyJustPressed(key)) {
                m_sCurrentInput += static_cast<char>(key);
                UpdateDisplay();
            }
        }

        if (IsKeyJustPressed(VK_BACK) && !m_sCurrentInput.empty()) {
            m_sCurrentInput.pop_back();
            UpdateDisplay();
        }

        if (IsKeyJustPressed(VK_RETURN) && !m_sCurrentInput.empty()) {
           // CHud::SetHelpMessage(L"Sending to ChatGPT...", true, false);
            std::string response = SendToNodeServer(m_sCurrentInput);
            DisplayResponse(response);
            m_eState = STATE_TALKING;
            m_uiLastPressTime = CTimer::m_snTimeInMilliseconds;
        }
    }

    void HandleTalking() {
        MakePedFacePlayer(m_pInteractingPed, FindPlayerPed());
        m_pInteractingPed->SetIdle();

        if (CTimer::m_snTimeInMilliseconds - m_uiLastPressTime > 3000) {
            Reset();
        }
    }

    void MakePedFacePlayer(CPed* m_pInteractingPed, CPlayerPed* player) {
        if (!m_pInteractingPed || !player) return;

        CVector pedPos = m_pInteractingPed->GetPosition();
        CVector playerPos = player->GetPosition();

        // Calculate delta between player and ped
        float deltaX = playerPos.x - pedPos.x;
        float deltaY = playerPos.y - pedPos.y;

        // Compute the angle in radians from the ped to the player
        float angleRad = atan2f(deltaY, deltaX);

        // Normalize the angle to [0, 2*PI] range
        if (angleRad < 0.0f) {
            angleRad += 2.0f * 3.14159265f;
        }

        // Adjust the angle to match GTA VC's coordinate system (clockwise from the north)
        float headingRad = 1.5707963f - angleRad; // PI/2 - angleRad

        // Normalize angle to [0, 2PI]
        if (headingRad < 0.0f) headingRad += 2.0f * 3.14159265f;
        if (headingRad >= 2.0f * 3.14159265f) headingRad -= 2.0f * 3.14159265f;

        // Apply the calculated heading to the ped (in radians)
        m_pInteractingPed->m_fRotationCur = headingRad;

        // Log the data to a file for debugging
    /*    std::ofstream log("log.txt", std::ios::app); // 'app' to append
        if (log.is_open()) {
            log << "=== Ped Facing Player ===\n";
            log << "Ped Position:    x=" << pedPos.x << ", y=" << pedPos.y << ", z=" << pedPos.z << "\n";
            log << "Player Position: x=" << playerPos.x << ", y=" << playerPos.y << ", z=" << playerPos.z << "\n";
            log << "Delta:           x=" << deltaX << ", y=" << deltaY << "\n";
            log << "Angle (rad):     " << angleRad << "\n";
            log << "Heading (rad):   " << headingRad << "\n";
            log << "Heading (deg):   " << headingRad * (180.0f / 3.14159265f) << "\n";
            log << "===========================\n\n";
            log.close();
        }*/

        // Set the heading in degrees for the ped
        m_pInteractingPed->SetHeading(headingRad * (180.0f / 3.14159265f)); // Convert to degrees
    }


    void UpdateDisplay() {
        std::wstring display = L"Typing: " + StringToWString(m_sCurrentInput);
        CHud::SetHelpMessage(display.c_str(), true, false);
    }

    void DisplayResponse(const std::string& response) {
        std::wstring wresponse = StringToWString(response);
        wchar_t* buffer = new wchar_t[wresponse.size() + 1];
        wcscpy_s(buffer, wresponse.size() + 1, wresponse.c_str());
        CMessages::AddMessage(buffer, 3000, 1);
        delete[] buffer;
    }

    bool IsKeyJustPressed(int vkey) {
        bool current = (GetAsyncKeyState(vkey) & 0x8000) != 0;
        bool previous = m_keyStates[vkey];
        m_keyStates[vkey] = current;
        return current && !previous;
    }

    bool KeyPressed(int key) {
        bool currentState = (GetAsyncKeyState(key) & 0x8000) != 0;
        bool result = false;
        if (key == 'E') {
            result = currentState && !m_bLastEState;
            m_bLastEState = currentState;
        }
        else if (key == 'Y') {
            result = currentState && !m_bLastYState;
            m_bLastYState = currentState;
        }
        return result;
    }

    CPed* FindNearestPed(CPlayerPed* player) {
        CPed* closest = nullptr;
        float minDist = 3.0f;
        CVector playerPos = player->GetPosition();

        CPool<CPed, CPlayerPed>* pool = CPools::ms_pPedPool;
        for (int i = 0; i < pool->m_nSize; ++i) {
            if (CPed* ped = pool->GetAt(i)) {
                if (ped != player && ped->m_fHealth > 0.0f) {
                    float dist = (playerPos - ped->GetPosition()).Magnitude();
                    if (dist < minDist) {
                        minDist = dist;
                        closest = ped;
                    }
                }
            }
        }
        return closest;
    }

    bool IsPedValid() {
        return m_pInteractingPed &&
            m_pInteractingPed->m_fHealth > 0.0f &&
            (FindPlayerPed()->GetPosition() - m_pInteractingPed->GetPosition()).Magnitude() < 4.0f;
    }

    void Reset() {
        m_pInteractingPed = nullptr;
        m_eState = STATE_IDLE;
        CHud::SetHelpMessage(L"", false, false);
    }
} pedInteraction;