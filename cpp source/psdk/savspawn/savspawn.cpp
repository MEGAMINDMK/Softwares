#include "plugin.h"
#include "game_sa\CCheat.h"
#include "game_sa\eModelID.h"
#include "game_sa\CHud.h"
#include "CFont.h"
#include "common.h"
#include "CTimer.h"
using namespace plugin;

class savspawn {
public:
    savspawn() {
        // Initialise your plugin here
        static unsigned int m_nLastSpawnedTime;
        Events::gameProcessEvent +=[]
        {
         if(KeyPressed(VK_END)&& CTimer::m_snTimeInMilliseconds > (m_nLastSpawnedTime + 1000))
            {
              //CFont::PrintString(100,100,"MEGAMIND");
			  CHud::SetHelpMessage("~w~Welcome to ~y~V-Spawner v0.1 ~g~by MEGAMIND. ~r~Use Key 1,2 or 3 to spawn",1,0,0);
			   m_nLastSpawnedTime = CTimer::m_snTimeInMilliseconds;
            }
            else if(KeyPressed(0x31))
            {
              CCheat::VehicleCheat(MODEL_INFERNUS);
			  CHud::SetHelpMessage("Spawned Infernus",1,0,0);
            }
            else if(KeyPressed(0x32))
            {
            CCheat::VehicleCheat(MODEL_BANSHEE);
			CHud::SetHelpMessage("Spawned Banshee",1,0,0);
            }
             else if(KeyPressed(0x33))
            {
            CCheat::VehicleCheat(MODEL_CHEETAH);
			CHud::SetHelpMessage("Spawned Cheetah",1,0,0);
            }
        };

    }
}_savspawn;
