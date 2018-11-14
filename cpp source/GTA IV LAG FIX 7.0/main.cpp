// GTA IV LAGFIX PATCH BY MEGAMIND

    #include <stdio.h>
    #include <string.h>
    #include <windows.h>
    #include <iostream>

    using namespace std;
    int main()
    {
         SetConsoleTitle("GTA-IV LAG FIX v7.0 BY: MEGAMIND");
           short choice;
cout<<"\n\t\tGTA-IV\n"<<endl;
cout<<"\t1. Launch Windowed Mode\n"<<endl;
cout<<"\t2. Launch Normal Mode\n"<<endl;
cout<<"\t3. Launch CitizenFX (needs all files of CitizenFx \n\tto be installed on game directory)\n"<<endl;
cout<<"\t4. Launch CitizenFX from CitizenMP-IV\n"<<endl;
cout<<"\tYour choice:"<<endl;
cin >> choice;
switch (choice)
{
    case 1:
         system("start LaunchGTAIV.exe -windowed 1 -height 400 -width 600 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
    case 2:
         system("start LaunchGTAIV.exe -height 400 -width 600 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        case 3:
         system("start Launcher.exe");
        break;
        case 4:
         system("start CitizenMP-IV\\Launcher.exe ");
        break;
        default:
         cout << "Invalid option";
}
          Sleep(4000);
      }
