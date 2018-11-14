#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
int main()
{

int choice;
bool gameOn = true;
using namespace std;
int barle = 50;
int barl = 20;
int files = 20;
 system("color e");
  printf("\t\t\tStarting Setup Please Wait...\n");
   for (int i = 0; i < barle; i++)
   {
      Sleep(100);
      cout << ":";

   }
   cout << "\n Setup Started..!\n\n\n";

   //cout << "\n Configuring..!\n\n\n";


   //cout << "\n Configuring..!\n";

while (gameOn != false){
        system ( "color 09" );
cout << "\n\n\n\t\t\tHACK BY MEGAMIND\n\n";
cout << " 1 - Download Patch....(IMPORTANT !).\n\n";
cout << " 2 - Download Files....(IMPORTANT !).\n\n";
cout << " 3 - Re-Install Setup .\n\n";
cout << " 4 - Quit Setup.\n\n";
//cout << " 3 - Quit.\n\n";
cout << " Enter your choice: ";

cin >> choice;

switch (choice)
{
case 1:
     cout << "Fetching Patch From Master Server...\n";
   for (int i = 0; i < barl; i++)
   {
      Sleep(800);
      cout << ":";

   }
   system("start http://www.mediafire.com/file/862g668xbgkz1pb/patch.zip");
break;
case 2:
     system("color b");
   cout << "\n\nDownloading Necessary Files...\n";
   for (int i = 0; i < files; i++)
   {
      Sleep(500);
      cout << ":";
   }
   system("start http://www.mediafire.com/file/hdp8k8694kzl8tp/models.zip");
   break;
case 3:
    system("color c");
     cout << "\n\nRe-Installing Setup...\n";
    system("game.exe");
    break;
case 4:
    system ( "color d" );
    cout<<"Quit Setup!\n";
gameOn = false;
break;
default:
    system ( "color 05" );
cout << "Not a Valid Choice. \n";
cout << "Choose again.\n";
cin >> choice;
break;
}

}
return 0;
}
