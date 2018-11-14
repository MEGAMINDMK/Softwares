#include "plugin.h"
#include "CStreaming.h"
#include "extensions/ScriptCommands.h"
#include "eScriptCommands.h"
#include "common.h"
#include "CTimer.h"
using namespace plugin;

class vc {
public:
    vc(){
        static unsigned int m_nLastSpawnedTime;
        Events::gameProcessEvent +=[]{
            if(KeyPressed(VK_NUMPAD2)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000))
            {
           CStreaming::RequestModel(130,0),
            CStreaming::LoadAllRequestedModels(0);
           CVector plrpedcoors = FindPlayerPed()->GetPosition();
             Command<eScriptCommands::COMMAND_CREATE_CAR>(130,plrpedcoors.x,plrpedcoors.y,plrpedcoors.z);
             m_nLastSpawnedTime = CTimer::m_snTimeInMilliseconds;
    }
        };
    }
} _vc;
unsigned int m_nLastSpawnedTime = 0;
