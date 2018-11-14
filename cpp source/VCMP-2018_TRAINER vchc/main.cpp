/* Changes the title of a specified window */

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

BOOL CALLBACK GetVCMPTitle(HWND win, LPARAM args);
VOID GetVCMPTitleWithUniqueID();

char titleVCMP[80];

main()
{
HWND handle;
handle = FindWindow(NULL, "GTA: Vice City Hard Corps");
if(handle == NULL)
{
    system("color b");
cout << "\n\n\n\t\t\tPlease run GTA: Vice City Hard Corps.\n";
//system("pause");
Sleep(1000);
getch();
return 0;
}
SetWindowText(handle, "GTA: vice city");
   system("color e");
cout << "\n\n\n\t\t\tTRAINER STARTED BY MEGAMIND";
system("start 2012Trainer.exe");
getch();
return 0;
}

