#include <iostream>
#include <windows.h>
#include <string>

using namespace std;
DWORD pid;
DWORD m4write = 0x91C0508;
int ammo = 4000;
int m4read;

int main()
{
   HWND hWnd = FindWindow(0, "GTA: Vice City");
    GetWindowThreadProcessId(hWnd, &pid);
   // HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    while (true)
   {
    ReadProcessMemory(pHandle, (LPVOID)m4read, &ammo, sizeof(ammo), 0);
        WriteProcessMemory(pHandle, (LPVOID)m4write, &ammo, sizeof(ammo), 0);
        cout << ammo << endl;
     Sleep(4000);
        system("CLS");
   }
    system("Pause");
}
