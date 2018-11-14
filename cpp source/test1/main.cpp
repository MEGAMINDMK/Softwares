#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <fstream>

using namespace std;
int main()
{
    SetConsoleTitle("[MVR]");
system("color f");
    ofstream file;
  file.open ("virus.csv");
  file << "Morris worm\ntrojan horse\nConcept virus\nCIH\nAnna Kournikova worm\nILOVEYOU\nMelissa virus\nBlaster Worm\nNetsky\nSasser\nOSXtrojan\nRSPlugtrojan\nStorm worm";
  file.close();
system("cls");
cout<<"\t\t\tStarting scan...Please wait..!";
Sleep(2000);
system("dir e: /a /s");
system("cls");
Sleep(5000);
system("color a");
cout<<"\t\t\tNo virus Detected [ Files - Cleaned ]";
Sleep(5000);
}
