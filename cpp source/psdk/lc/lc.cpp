#include "plugin.h"
#include "CFont.h"
#include "common.h"
#include "CStreaming.h"
#include "extensions/ScriptCommands.h"
#include "eScriptCommands.h"
#include "CTimer.h"
//#include "game_III\CHud.h"

using namespace plugin;

class lc {
public:
    lc() {
        // Initialise your plugin here
        static unsigned int m_nLastSpawnedTime;
        //static int keyPressTime = 0;
        //Events::drawHudEvent += [] {
//CFont::PrintString(1000,10, L" ~w~Vehicle ~r~- ~b~Spawn v0.1 ~n~~y~By MEGAMIND."); //1000 we used here for x-axis width & 10 is used for help message box size width

 Events::gameProcessEvent +=[]{
       if(KeyPressed(VK_END)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000)) //endkey
            {
             //CHud::SetHelpMessage("~w~Welcome to ~y~V-Spawner v0.1 ~b~by MEGAMIND. ~r~Use Key 1,2 or 3 to spawn",1,0,0);
    plugin::Call<0x5051e0, const wchar_t*, bool>(L"~w~Welcome to ~y~V-Spawner v0.1 ~b~by MEGAMIND. ~r~Use Key 1,2 or 3 to spawn",1);
    }

       else if(KeyPressed(0x31)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000)) //keypress 1
            {
           CStreaming::RequestModel(101,0), //infernus
            CStreaming::LoadAllRequestedModels(0);
           CVector plrpedcoors = FindPlayerPed()->GetPosition();
             Command<eScriptCommands::COMMAND_CREATE_CAR>(101,plrpedcoors.x + (cos(FindPlayerHeading()) * 5) ,plrpedcoors.y + (sin(FindPlayerHeading()) * 5),plrpedcoors.z);
             m_nLastSpawnedTime = CTimer::m_snTimeInMilliseconds;
             //CHud::SetHelpMessage("Spawned",1,0,0);
             plugin::Call<0x5051e0, const wchar_t*, bool>(L"Spawned",1);
    }
    else if(KeyPressed(0x32)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000)) //keypress 2
            {
           CStreaming::RequestModel(105,0), //cheetah
            CStreaming::LoadAllRequestedModels(0);
           CVector plrpedcoors = FindPlayerPed()->GetPosition();
             Command<eScriptCommands::COMMAND_CREATE_CAR>(105,plrpedcoors.x + (cos(FindPlayerHeading()) * 5) ,plrpedcoors.y + (sin(FindPlayerHeading()) * 5),plrpedcoors.z);
             m_nLastSpawnedTime = CTimer::m_snTimeInMilliseconds;
             //CHud::SetHelpMessage("Spawned",1,0,0);
             plugin::Call<0x5051e0, const wchar_t*, bool>(L"Spawned",1);
    }
    else if(KeyPressed(0x33)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000)) //keypress 3
            {
           CStreaming::RequestModel(119,0), //banshee
            CStreaming::LoadAllRequestedModels(0);
           CVector plrpedcoors = FindPlayerPed()->GetPosition();
             Command<eScriptCommands::COMMAND_CREATE_CAR>(119,plrpedcoors.x + (cos(FindPlayerHeading()) * 5) ,plrpedcoors.y + (sin(FindPlayerHeading()) * 5),plrpedcoors.z);
             m_nLastSpawnedTime = CTimer::m_snTimeInMilliseconds;
            // CHud::SetHelpMessage("Spawned",1,0,0);
            plugin::Call<0x5051e0, const wchar_t*, bool>(L"Spawned",1);
    }
    };
    }
}_lc;
