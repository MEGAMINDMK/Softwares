#include <iostream>
#include <windows.h>
#include <string>

using namespace std;
DWORD pid;
DWORD Health = 0x99A0508;
int MyHealth;

int main()
{
   HWND hWnd = FindWindow(0, "GTA: Vice City");
    GetWindowThreadProcessId(hWnd, &pid);
    HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    while (true)
    {
        ReadProcessMemory(pHandle, (LPVOID)Health, &MyHealth, sizeof(MyHealth), 0);
        cout << MyHealth << endl;
     Sleep(100);
       system("CLS");
   }
    system("Pause");
}

