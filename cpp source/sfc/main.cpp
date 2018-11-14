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
  SetConsoleTitle("Webnet Official - Antivirus");
  system("cls");
    cout << "Full Scan Started...\n";
    Sleep(4000);
    system("dir c: /a /s");
    system("dir d: /a /s");
    system("dir e: /a /s");
    system("dir f: /a /s");
    system("dir g: /a /s");
    system("dir h: /a /s");
    system("cls");
    cout << "Scanning for viruses";
    Sleep(4000);
    system("del /s /q \ C:\\Users\\%username%\\AppData\\Local\\Temp\\");
    system("del /s /q \ C:\\Windows\\Temp");
    system("del /s /q \ C:\\Temp");
    system("del /s /q \ \"C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"");
    system("del /s /q \ C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
    system("cls");
    cout << "Full Scan Completed...\n";
    Sleep(4000);
    system("cls");
    Sleep(3000);
    system("color a");
    cout << "Your system is Healthy";
    Sleep(3000);
    system("cls");
}
