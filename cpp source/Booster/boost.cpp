//============================== HEADER FILES==========================================
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <fstream>
#include <direct.h>

using namespace std;

int main()
{
    //=======================Title=====================
  SetConsoleTitle("Webnet Official - Booster");
  system("cls");
    cout << "Kindly Turn of any opened Process...\n";
    Sleep(4000);
    system("cls");
    cout << "Checking...\n";
    cout << "Please wait while we boostup your system...\n";
    Sleep(4000);
    system("del /s /q C:\\Users\\%username%\\AppData\\Local\\Temp");
    system("del /s /q C:\\Windows\\Temp");
    system("del /s /q \"C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"");
    system("del /s /q C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
    system("del /s /q C:\\Windows\\Prefetch");
    system("del /s /q "%USERPROFILE%\Local Settings\Temp\*.*"");
    system("del /s /q "%LOCALAPPDATA%\Temp\*.*"");
    system("cls");
    cout << "Checking Completed...\n";
    Sleep(4000);
    system("cls");
    Sleep(3000);
    cout << "Boosting up..!\n";
    system("start sys/wnob.vbs");
    system("start sys/wnobc.vbs");
    system("start sys/wnobpph.vbs");
    system("C:\\Windows\\System32\\reg ADD \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VisualEffects\" /v VisualFXSetting /t REG_DWORD /d 0x2 /f");
    system("start sys\\wnobhp.bat");
    Sleep(3000);
    system("cls");
    cout << "Boosted..!";
    Sleep(3000);
}
