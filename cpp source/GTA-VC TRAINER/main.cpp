#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;
int main()
{
int ch;
cout<<"Enter 1. For Health\n";
cout<<"Enter 2. For Money\n";
cin>>ch;
switch(ch)
{
case  1:{
   //int newValue = 1000;
 float newValue = 1000.0;
 HWND hWnd = FindWindow(0, "GTA: Vice City");
if (hWnd == 0) {
 cerr << "Cannot find window." << endl;
    } else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
if (!hProc) {
            cerr << "Cannot open process." << endl;
        } else {
            int isSuccessful = WriteProcessMemory(hProc, (LPVOID)0x8DF03C0, &newValue, (DWORD)sizeof(newValue), NULL);
            if (isSuccessful > 0) {
                clog << "Process memory written." << endl;
            } else {
                cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }}
break;
case  2:
{
   int newValue = 9999;
 //float newValue = 1000.0;
 HWND hWnd = FindWindow(0, "GTA: Vice City");
if (hWnd == 0) {
 cerr << "Cannot find window." << endl;
    } else {
        DWORD pId;
        GetWindowThreadProcessId(hWnd, &pId);
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
if (!hProc) {
            cerr << "Cannot open process." << endl;
        } else {
            int isSuccessful = WriteProcessMemory(hProc, (LPVOID)0x94ADC8, &newValue, (DWORD)sizeof(newValue), NULL);
            if (isSuccessful > 0) {
                clog << "Process memory written." << endl;
            } else {
                cerr << "Cannot write process memory." << endl;
            }
            CloseHandle(hProc);
        }
    }}
break;
default:
cout<<"no cheat";
}
return 0;
}
