//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    float healthValue = 0;
    DWORD* CPlayerPed_BaseAddr        = (DWORD*)0x94AD28;
    DWORD CPlayerPed_HealthOffset    = 0x358; //armour
    DWORD cBase = 0;

    HWND hWnd = FindWindowW(0, L"GTA: Vice City");
    if (hWnd == 0) {
        cerr << "Cannot find window." << endl;
    }
    else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
        if (!hProc) {
            cerr << "Cannot open process." << endl;
        }
        else {
            ReadProcessMemory(hProc, (PBYTE*)CPlayerPed_BaseAddr, &cBase, sizeof(DWORD), 0);
            //printf("CPlayerPed Ptr: 0x%0X\n", cBase);

            int isSuccessful = ReadProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
          //  printf("Armour: %f\n", healthValue);

            cout << "Please enter value for Armour: ";
            cin >> healthValue;

            isSuccessful = WriteProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
           // printf("Armour: %f\n", healthValue);
            if (isSuccessful > 0) {
               // clog << "Process memory written." << endl;
                 clog << "success." << endl;
            }
            else {
                cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }
    return 0;
}
