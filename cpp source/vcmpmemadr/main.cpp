#include <iostream>
#include <windows.h>
#include <stdio.h>
HANDLE hHandle = GetModuleHandle("vcmp-game.dll");
using namespace std;

int main()
{
  if (hHandle == 0)
{
    LoadLibrary("vcmp-game.dll");
hHandle = GetModuleHandle("vcmp-game.dll");

}

printf(" loaded at base: 0x%x", hHandle);
}
