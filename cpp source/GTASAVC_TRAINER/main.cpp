#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;
int main()
{
    SetConsoleTitle("GTA San Andreas & Vice City ( Hack by MEGAMIND )");
    int op;
cout<<"\t\t\t==================================";
cout<<"\t\t\t\t\t\t\tEnter 1. For GTA SA\n";
cout<<"\t\t\t\tEnter 2. For GTA VC\n";
cout<<"\t\t\t==================================\n\n\n\n";
cout<<"\t\t\tEnter your Game choice : ";
cin>>op;
switch(op)
{
case  1:{
    system("cls");
    cout<<"GTA SA HACK STARTED";
int ch;
cout<<"\n\n\n\t\t\t\tEnter 1. For Health\n";
cout<<"\t\t\t\tEnter 2. For Armour\n";
cout<<"\t\t\t\tEnter 3. For Money\n";
cout<<"\n\n\n\t\t\tVisit http://gta-mrk.tk/ for more\n";
cout<<"\t\t\tEnter any option : ";
cin>>ch;
switch(ch)
{
case  1:{
float healthValue = 0;
    DWORD* CPlayerPed_BaseAddr        = (DWORD*)0xB6F5F0;
    DWORD CPlayerPed_HealthOffset    = 0x540;
    DWORD cBase = 0;

    HWND hWnd = FindWindowW(0, L"GTA: San Andreas");
    if (hWnd == 0) {
        cerr << "Run GTA SA." << endl;
    }
    else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
        if (!hProc) {
           // cerr << "Cannot open process." << endl;
        }
        else {
            ReadProcessMemory(hProc, (PBYTE*)CPlayerPed_BaseAddr, &cBase, sizeof(DWORD), 0);
           // printf("CPlayerPed Ptr: 0x%0X\n", cBase);

            int isSuccessful = ReadProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
          //  printf("Health: %f\n", healthValue);

            cout << "Please enter value for Health: ";
            cin >> healthValue;

            isSuccessful = WriteProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
           // printf("Health: %f\n", healthValue);
            if (isSuccessful > 0) {
                //clog << "Process memory written." << endl;
                 clog << "Gave you Bonus Health." << endl;
            }
            else {
               // cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }
}
break;
case  2:
{
float healthValue = 0;
    DWORD* CPlayerPed_BaseAddr        = (DWORD*)0xB6F5F0;
    DWORD CPlayerPed_HealthOffset    = 0x548; //armour
    DWORD cBase = 0;

    HWND hWnd = FindWindowW(0, L"GTA: San Andreas");
    if (hWnd == 0) {
        cerr << "Run GTA SA." << endl;
    }
    else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
        if (!hProc) {
            //cerr << "Cannot open process." << endl;
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
                 clog << "Gave you Armour." << endl;
            }
            else {
               // cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }
  }
break;

case 3:
{
int newValue = 9999999;
 //float newValue = 1000.0;
 HWND hWnd = FindWindow(0, "GTA: San Andreas");
if (hWnd == 0) {
 cerr << "Run GTA SA." << endl;
    } else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
if (!hProc) {
            cerr << "Cannot Send you Gift :(." << endl;
        } else {
            int isSuccessful = WriteProcessMemory(hProc, (LPVOID)0xB7CE50, &newValue, (DWORD)sizeof(newValue), NULL);
            if (isSuccessful > 0) {
                clog << "Sent you some Cash Prize." << endl;
            } else {
                cerr << "Error." << endl;
            }
            CloseHandle(hProc);
        }
    }
}
break;
default:{
cout<<"no cheat";
}
}
}
break;
case 2:{
    system("cls");
    cout<<"GTA VC HACK STARTED";
int choice;
cout<<"\n\n\n\t\t\t\tEnter 1. For Health\n";
cout<<"\t\t\t\tEnter 2. For Armour\n";
cout<<"\t\t\t\tEnter 3. For Money\n";
cout<<"\n\n\n\t\t\tVisit http://gta-mrk.tk/ for more\n";
cin>>choice;
switch(choice)
{
case  1:{
float healthValue = 0;
    DWORD* CPlayerPed_BaseAddr        = (DWORD*)0x94AD28;
    DWORD CPlayerPed_HealthOffset    = 0x354;
    DWORD cBase = 0;

    HWND hWnd = FindWindowW(0, L"GTA: Vice City");
    if (hWnd == 0) {
        cerr << "Run GTA VC." << endl;
    }
    else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
        if (!hProc) {
           // cerr << "Cannot open process." << endl;
        }
        else {
            ReadProcessMemory(hProc, (PBYTE*)CPlayerPed_BaseAddr, &cBase, sizeof(DWORD), 0);
           // printf("CPlayerPed Ptr: 0x%0X\n", cBase);

            int isSuccessful = ReadProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
          //  printf("Health: %f\n", healthValue);

            cout << "Please enter value for Health: ";
            cin >> healthValue;

            isSuccessful = WriteProcessMemory(hProc, (LPVOID)(cBase + CPlayerPed_HealthOffset), &healthValue, sizeof(healthValue), 0);
           // printf("Health: %f\n", healthValue);
            if (isSuccessful > 0) {
                //clog << "Process memory written." << endl;
                 clog << "Gave you Bonus Health." << endl;
            }
            else {
               // cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }
}
break;
case 2:
{
float healthValue = 0;
    DWORD* CPlayerPed_BaseAddr        = (DWORD*)0x94AD28;
    DWORD CPlayerPed_HealthOffset    = 0x358; //armour
    DWORD cBase = 0;

    HWND hWnd = FindWindowW(0, L"GTA: Vice City");
    if (hWnd == 0) {
        cerr << "Run GTA VC." << endl;
    }
    else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
        if (!hProc) {
            //cerr << "Cannot open process." << endl;
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
                 clog << "Gave you Armour." << endl;
            }
            else {
               // cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }
  }
break;

case 3:
{
int newValue = 9999999;
 //float newValue = 1000.0;
 HWND hWnd = FindWindow(0, "GTA: Vice City");
if (hWnd == 0) {
 cerr << "Run GTA VC." << endl;
    } else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
if (!hProc) {
            cerr << "Cannot Send you Gift :(." << endl;
        } else {
            int isSuccessful = WriteProcessMemory(hProc, (LPVOID)0x94ADC8, &newValue, (DWORD)sizeof(newValue), NULL);
            if (isSuccessful > 0) {
                clog << "Sent you some Cash Prize." << endl;
            } else {
                cerr << "Error." << endl;
            }
            CloseHandle(hProc);
        }
    }
}
break;
default:{
cout<<"no cheat";
}
}
break;
default:{
cout<<"no other game options there :(";
}
}
getch();
return 0;
}
}


