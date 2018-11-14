#include "plugin.h"
#include "CFont.h"
#include "common.h"

using namespace plugin;

class vchud {
public:
    vchud() {
        // Initialise your plugin here
        static int keyPressTime = 0;
        Events::drawHudEvent += [] {
        CFont::PrintString(255,256, L" V-Spawn v0.1.");
    };
    }
}_vchud;

