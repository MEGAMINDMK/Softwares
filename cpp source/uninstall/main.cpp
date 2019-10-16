//Custome uninstaller
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	//Always check if the software is running in task manager
   system("taskkill /IM WebNet_Official.exe /F");
   //provide sometime to kill exe and wait for 2 sec
   Sleep(2000);
   //get to user path where that software is installed and remove it permanently
   system("cd /D C:\\Users\\%USERNAME%\\AppData\\Local\\WebNet_Official && rd /s /q .");
   //Note if the software came with a registery file then the registry wont be deleted only the software will get removed
}

