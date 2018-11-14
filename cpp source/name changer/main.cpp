/* Changes the title of a specified window */

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

main()
{
char windname[50];
char newname[50];
system("color a");
cout << "\t\tWINDOWS TITLE CHANGER 2018 BY: MEGAMIND\n\n";
cout << "Please enter the Title of the Window you wish to change:\n ";
cin.getline(windname, 50, '\n');
HWND handle;
handle = FindWindow(NULL, windname);
if(handle == NULL)
{
    system("color b");
cout << "\n\n Sorry, the window could not be found.";
return 0;
}
system("color c");
cout << "\n\nwhat would you like to change the title to?:\n ";
cin.getline(newname, 50, '\n');
SetWindowText(handle, newname);
system("color d");
cout << "\n\nThe Window Title was changed!";
getch();
return 0;
}

