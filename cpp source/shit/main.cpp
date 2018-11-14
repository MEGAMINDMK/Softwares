/* Changes the title of a specified window */

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

main()
{
    SetConsoleTitle("Miracle Box Ver 2.58 [Patch] BY: MEGAMIND");
HWND handle;
handle = FindWindow(NULL, "Miracle Box Ver 2.58");
if(handle == NULL)
{
    system("color b");
cout << "\n\n\n\t\t\tPlease run Miracle Box Ver 2.58\n\t\t\t in order to change effects\n";
//system("pause");
Sleep(1000);
getch();
return 0;
}
SetWindowText(handle, "All Mobile Tool");
   system("color e");
cout << "\n\n\n\t\t\tAll Mobile Tool STARTED BY MEGAMIND";
//system("start 2012Trainer.exe");
getch();
return 0;
}
