#include <cstdio>
#include <windows.h>
#include <iostream>
int main() {
 using namespace std;

 //int barle = 3;



    cout<<"Removing viruses...Please wait while we check your system";
    /*for (int i = 0; i < barle; i++)
   {
      Sleep(5000);
      cout << ".";

   }*/
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
    return 0;
}
