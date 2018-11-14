#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;
DWORD pid;

int main()
{
    HWND hwnd = FindWindowA(NULL, ("Vice City Multiplayer (GTA:VC)"));
    GetWindowThreadProcessId(hwnd, &pid);
    if(hwnd)
    {
        system ( "color 9" );
        cout << "Aimbot Execution Started..!";
        cout << pid << endl;
        system("vcmpaimbot.exe");
        }
    else
    {
        system ( "color b" );
       cout << "Aimbot Execution Cannot be Started..!\n Please run vcmp";
    }

  getch();
    return 0;
}
