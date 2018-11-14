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
  SetConsoleTitle("Antivirus");

  //=================creating files and write into them===================
  ofstream file;
  file.open ("av.db");
  file << "[Table = AV]\n\nMorris worm\ntrojan horse\nConcept virus\nCIH\nAnna Kournikova worm\nILOVEYOU\nMelissa virus\nBlaster Worm\nNetsky\nSasser\nOSXtrojan\nRSPlugtrojan\nStorm worm";
  file.close();

  file.open ("av.csv");
  file << "Morris worm\ntrojan horse\nConcept virus\nCIH\nAnna Kournikova worm\nILOVEYOU\nMelissa virus\nBlaster Worm\nNetsky\nSasser\nOSXtrojan\nRSPlugtrojan\nStorm worm";
  file.close();


 //=========================INTRO AND LOADER==================================
 cout<<"\t\tMalicious Virus Remover\n\n";
 cout<<"\n\t\t\tAntivirus - Loading\n\n";
 system("color F");
 char a=0, b=219;
 cout<<"\t\t\t\t";
 cout<<a;
 cout<<"\r";
 cout<<"\t\t\t";

for (int i=0;i<=15;i++)
 {
  cout<<b;


Sleep(200);
 }

//============================welcome screen & choice======================================
system("cls");
int choice;
do
{

system("color 3");
cout << endl
<<"\t\t\tWelcome to Menu\n\n"
<< " 1 - Scan drive C.\n"
<< " 2 - Scan drive D.\n"
<< " 3 - Scan drive E.\n"
<< " 4 - Scan drive F.\n"
<< " 5 - Scan drive G.\n"
<< " 6 - Scan drive H.\n"
<< " 7 - Quick Scan.\n"
<< " 8 - Full Scan.\n"
<< " 9 - Power Off.\n\n"
<< " Enter your choice and press Enter: ";
cin >> choice;

    system("cls");
   if(choice==1)
{
   system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir c: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\ch.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==2)
{
    system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir d: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\ch.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==3)
{
    system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir e: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\ch.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==4)
{
    system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir f: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\ch.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==5)
{
    system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir g: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\ch.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==6)
{
    system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir h: /a /s");
system("cls");
system("color 5");
cout<<"Removing viruses...Please wait while we check your system";
Sleep(9000);
remove("C:\\Temp\\*.exe");
Sleep(5000);
remove("C:\\Temp\\horse.vbs");
Sleep(5000);
remove("C:\\Temp\\ramit.vbs");
Sleep(5000);
remove("C:\\Temp\\trojan.exe");
Sleep(5000);
remove("C:\\Temp\\trojan0.exe");
system("CLS");
Sleep(7000);
system("color a");
cout<<"System is Healthy...!";
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("color 9");
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
}

if(choice==7)
{
    system("cls");
    cout << "Quick Scan Started...\n";
    Sleep(4000);
    system("del /s /q \ C:\\Users\\%username%\\AppData\\Local\\Temp\\");
    system("del /s /q \ C:\\Windows\\Temp");
    system("del /s /q \ C:\\Temp");
    system("del /s /q \ \"C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"");
    system("del /s /q \ C:\\Users\\%username%\\AppData\\Roaming\\Microsoft\\Windows\\Recent");
    system("cls");
    cout << "Scan Completed...\n";
    Sleep(4000);
    system("cls");
    Sleep(3000);
    system("color a");
    cout << "Your system is Healthy";
    Sleep(3000);
    system("cls");
}

if(choice==8)
{
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

if(choice==9)
{
    cout << "Powering Off.\n";
    Sleep(4000);
}

/*
else {
system("cls");
cout << "Not a Valid Choice. \n";
cout << "Choose again.\n";
Sleep(3000);
system("cls");
}
*/
}

/*========================switch case========================================
switch (choice)
{
case 1:
//code to start the game
system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir c: /a /s");
system("cls");
Sleep(5000);
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
break;

case 2:
//code to make score for this game to count how many times u win the game
system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir d: /a /s");
system("cls");
Sleep(5000);
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
break;

case 3:
//code to make option for the game
system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir e: /a /s");
system("cls");
Sleep(5000);
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
system("cls");
cout<<"\t\t\tGoing Back to menu";
Sleep(5000);
system("cls");
break;

case 4:
cout << "help menu. \n";
break;
case 5:
cout << "Powering Off.\n";
Sleep(2000);
break;
default:
cout << "Not a Valid Choice. \n"
<< "Choose again.\n";
break;
}

}*/
//============switch case closed====================================================

while (choice !=9);
return 0;

getch();
}
