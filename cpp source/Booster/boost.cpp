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
    SetConsoleTitle(L"Webnet Official - Booster");
    system("cls");
    cout << "****************************************************\n";
    cout << "*        Webnet Official Optimizer v1.5            *\n";
    cout << "****************************************************\n";
    cout << "Kindly turn off any opened Process...\n";
    Sleep(2000);
    cout << "Kindly donot close the program at any circumstances...\n";
    Sleep(2000);
    cout << "The System will automatically reboot once your system is optimized...\n";
    Sleep(2000);
    cout << "You have 10 sec to make a descision between these seconds to terminate the program now by pressing\n";
    cout << "ctrl+c if you dont have time, else let the program execute after 10 sec...\n";
    Sleep(10000); 
    system("cls");
    cout << "Checking...\n";
    cout << "Please wait while we boostup your system...\n";
    Sleep(4000);
    system("del /s /q C:\\Users\\%username%\\AppData\\Local\\Temp");
    Sleep(4000);
    system("del /s /q C:\\Windows\\Temp");
    Sleep(4000);
    system("del /s /q \"C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"");
    Sleep(4000);
    system("del /s /q C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
    Sleep(4000);
    system("del /s /q C:\\Windows\\Prefetch");
    Sleep(4000);
    system("cls");
    system("ipconfig /FlushDNS");
    Sleep(4000);
	system("powercfg -h on");
    Sleep(4000);
	system("boost.reg");
    Sleep(4000);
    system("sfc /scannow");
    system("cls");
    Sleep(4000);
    system("cleanmgr /dc");
    Sleep(4000);
    //cleanmgr /verylowdisk -> without user prompt /d -> drive
    cout << "Checking Completed...\n";
    Sleep(4000);
    system("cls");
    Sleep(3000);
    cout << "Boosting up..!\n";
    //powerplan high
    system("wnobpph.vbs");
    Sleep(3000);
    //set visual effects to zero
    system("C:\\Windows\\System32\\reg ADD \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VisualEffects\" /v VisualFXSetting /t REG_DWORD /d 0x2 /f");
    Sleep(3000);
   // system("wnobhp.bat");
    system("speed.bat");
    Sleep(3000);
	system("powershell.exe Clear-RecycleBin -F");
    Sleep(4000);
    system("cls");
    system("rd /s %systemdrive%\\$Recycle.bin");
    Sleep(4000);
    system("del /s /q %systemdrive%\\$Recycle.bin");
    system("cls");
    Sleep(4000);
    system("cls");
    system("chkdsk /x /r");
    Sleep(3000);
    cout << "Boosted..!";
    Sleep(3000);
    system("shutdown /r -t 0");
}
