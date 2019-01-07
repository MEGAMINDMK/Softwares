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
    Sleep(4000);
   system("cls");
    cout << "Checking Completed...\n";
    Sleep(4000);
    system("cls");
    Sleep(3000);
    cout << "Un Boosting..!\n";
    system("start sys/wnoubppb.vbs");
    system("reg ADD \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VisualEffects\" /v VisualFXSetting /t REG_DWORD /d 0x0 /f");
    system("wnobnp.bat");
    Sleep(3000);
    system("cls");
    cout << "Un Boosted..!";
    Sleep(3000);
}
