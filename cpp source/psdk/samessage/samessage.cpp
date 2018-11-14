/*
Plugin-SDK (Grand Theft Auto) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "plugin.h"
#include "CFont.h"
#include "common.h"

using namespace plugin;

class MessageDisplay {
public:
    MessageDisplay() {
        static int keyPressTime = 0;
        Events::drawHudEvent += [] {
        CFont::PrintString(256,256,"MEGAMIND");
    };
    }
} messagedisplay;
