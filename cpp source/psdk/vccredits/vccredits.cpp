#include "plugin.h"
#include "CFont.h"
#include "common.h"
#include "CHud.h"
using namespace plugin;

class vccredits {
public:
    vccredits() {

Events::gameProcessEvent +=[]{

        CFont::PrintString(255,256, L"MY TEST!");
        };

    }
}_vccredits;
