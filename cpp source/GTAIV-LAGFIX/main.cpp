#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleTitle("GTA-IV LAG FIX BY: MEGAMIND");
    system("start LaunchGTAIV.exe -availablevidmem 30.0 -framelimit 0 -norestrictions -nomemrestrict -fullspecaudio");
    Sleep(4000);
    return 0;
}
