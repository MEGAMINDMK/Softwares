#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    SetConsoleTitle("Discord Bot");
    system("color c");
    cout << "\t\t\t\tStarting Bot...!" << endl;
    Sleep(3000);
    system("CLS");
    Sleep(2000);
    system("color a");
    cout << "\t\t\t\tBot Started" << endl;
    Sleep(1000);
    system("CLS");
    Sleep(1000);
    system("color 7");
    system("discord-irc --config /DISCORD_BOT/Config.json");
    getch();
    return 0;
}
