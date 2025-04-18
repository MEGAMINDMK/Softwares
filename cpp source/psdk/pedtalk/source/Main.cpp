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
#include <fstream> // For logging
#include <cmath>   // For atan2, etc.
using namespace plugin;

class PedInteraction {
    enum eInteractionState {
        STATE_IDLE,
        STATE_PROMPTED,
        STATE_TALKING
    };

    CPed* m_pInteractingPed;
    eInteractionState m_eState;
    unsigned int m_uiLastPressTime;
    bool m_bLastEState;
    bool m_bLastYState;

public:
    PedInteraction()
        : m_pInteractingPed(nullptr),
        m_eState(STATE_IDLE),
        m_uiLastPressTime(0),
        m_bLastEState(false),
        m_bLastYState(false)
    {
        Events::gameProcessEvent += [this] {
            ProcessInteraction();
            };
    }

private:
    void ProcessInteraction() {
        CPlayerPed* player = FindPlayerPed();
        if (!player || player->m_fHealth <= 0.0f)
            return;

        switch (m_eState) {
        case STATE_IDLE:
            HandleIdleState(player);
            break;
        case STATE_PROMPTED:
            HandlePromptedState();
            break;
        case STATE_TALKING:
            HandleTalkingState();
            break;
        }
    }

    void HandleIdleState(CPlayerPed* player) {
        if (KeyPressed('E')) {
            CPed* ped = FindNearestPed(player);
            if (ped) {
                m_pInteractingPed = ped;
                CHud::SetHelpMessage(L"Press ~y~Y~w~ to talk", true, false);
                m_eState = STATE_PROMPTED;
                m_uiLastPressTime = CTimer::m_snTimeInMilliseconds;
            }
        }
    }

    void HandlePromptedState() {
        if (!IsPedStillValid()) {
            ResetInteraction();
            return;
        }

        if (KeyPressed('Y')) {
            CHud::SetHelpMessage(L"Hello! What's up?", true, false);
            m_eState = STATE_TALKING;
            m_uiLastPressTime = CTimer::m_snTimeInMilliseconds;
        }
        else if (CTimer::m_snTimeInMilliseconds - m_uiLastPressTime > 5000) {
            ResetInteraction();
        }
    }


    void MakePedFacePlayer(CPed* ped, CPlayerPed* player) {
        if (!ped || !player) return;

        CVector pedPos = ped->GetPosition();
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
        ped->m_fRotationCur = headingRad;

        // Log the data to a file for debugging
        std::ofstream log("log.txt", std::ios::app); // 'app' to append
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
        }

        // Set the heading in degrees for the ped
        ped->SetHeading(headingRad * (180.0f / 3.14159265f)); // Convert to degrees
    }



    // Function to convert std::string to std::wstring
    std::wstring StringToWString(const std::string& str) {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), NULL, 0);
        std::vector<wchar_t> wstr(size_needed + 1);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), &wstr[0], size_needed);
        wstr[size_needed] = 0; // Null-terminate the wide string
        return std::wstring(&wstr[0]);
    }

    void DisplayMessage(const std::string& message, uint32_t duration) {
        std::wstring wmessage = StringToWString(message);
        wchar_t* writable_message = new wchar_t[wmessage.size() + 1];
        std::wcscpy(writable_message, wmessage.c_str());

        // Clear any existing messages
        CMessages::ClearMessages();

        // Display the new message
        CMessages::AddMessage(writable_message, duration, 1);

        delete[] writable_message;
    }

    void HandleTalkingState() {
        static uint32_t lastMessageTime = 0;

        if (m_pInteractingPed) {
            // Stop the ped's movement

            // Make the ped face the player
            MakePedFacePlayer(m_pInteractingPed, FindPlayerPed());
            m_pInteractingPed->SetIdle();
            // Display the ped's response as a message if 3 seconds have passed
            if (CTimer::m_snTimeInMilliseconds - lastMessageTime > 3000) {
                DisplayMessage("Hello there!", 3000);
                lastMessageTime = CTimer::m_snTimeInMilliseconds;
            }
        }

        // End interaction after 3 seconds
        if (CTimer::m_snTimeInMilliseconds - m_uiLastPressTime > 3000) {
            ResetInteraction();
        }
    }





    CPed* FindNearestPed(CPlayerPed* player) {
        CPed* closestPed = nullptr;
        float fMinDistance = 3.0f;
        CVector playerPos = player->GetPosition();

        CPool<CPed, CPlayerPed>* pPedPool = CPools::ms_pPedPool;
        for (int i = 0; i < pPedPool->m_nSize; i++) {
            if (CPed* ped = pPedPool->GetAt(i)) {
                if (ped != player && ped->m_fHealth > 0.0f) {
                    CVector pedPos = ped->GetPosition();
                    float fDistance = (playerPos - pedPos).Magnitude();
                    if (fDistance < fMinDistance) {
                        fMinDistance = fDistance;
                        closestPed = ped;
                    }
                }
            }
        }
        return closestPed;
    }

    bool IsPedStillValid() {
        return m_pInteractingPed &&
            m_pInteractingPed->m_fHealth > 0.0f &&
            (FindPlayerPed()->GetPosition() - m_pInteractingPed->GetPosition()).Magnitude() < 4.0f;
    }

    void ResetInteraction() {
        m_pInteractingPed = nullptr;
        m_eState = STATE_IDLE;
        CHud::SetHelpMessage(L"", false, false);
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
} pedInteraction;
