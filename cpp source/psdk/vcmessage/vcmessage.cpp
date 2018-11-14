#include "plugin.h"
#include "game_vc\CHud.h"
using namespace plugin;

class vcmessage {
public:
    vcmessage() {
     Events::gameProcessEvent +=[]
        {
          if(KeyPressed(VK_NUMPAD1))
            {
			  CHud::SetHelpMessage("MEGAMIND",1,0,0);
            }
     };

    }
} _vcmessage;
