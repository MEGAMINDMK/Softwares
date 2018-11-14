#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
using namespace std;
int barl = 21;
int main()
{
SetConsoleTitle("VC-COOP Registery");
 system("color 0e");
   cout << "Loading...\n\n";
   for (int i = 0; i < barl; i++)
   {
      Sleep(100);
      //cout << ":";
   }
   cout << "Loaded";
   printf("\nPress Yes after the register box appears");
   printf("\n\n BY: MEGAMIND\n\n");
   system("coop.reg");
   system("color a");
   cout << "Starting..\n\n";
   for (int i = 0; i < barl; i++)
   {
      Sleep(100);
     // cout << ":";
   }
   cout << "Started";
   system("brwsr-exec-load.exe");
   printf("\n\n Kindly execute this string in your browser\n\n");
   system("color f");
   printf("vccoop:host=localhost;port=23546;autoconnect;");
   getch();
    return 0;
}
