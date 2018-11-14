#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

BOOL CALLBACK GetVCMPTitle(HWND win, LPARAM args);
VOID GetVCMPTitleWithUniqueID();
HWND handle;
char titleVCMP[80];

int main()
{
	GetVCMPTitleWithUniqueID();
	cout << "The VCMP Window Title With Unique Key." << endl;
	cout << titleVCMP;
	_getch();
    return 0;
}
VOID GetVCMPTitleWithUniqueID()
{
	EnumWindows(GetVCMPTitle, NULL);
}

BOOL CALLBACK GetVCMPTitle(HWND win, LPARAM args)
{
	char title_vcmp[31] = "Vice City Multiplayer (GTA:VC)";
	char win_title[80];
	GetWindowTextA(win, win_title, sizeof(win_title));

	for (int i = 0; i < 30; i++) {
		if (title_vcmp[i] != win_title[i])
            return true;
	}

	for (int i = 0; i < 80; i++) {
		titleVCMP[i] = win_title[i];
	}


	return true;
getch();
}
