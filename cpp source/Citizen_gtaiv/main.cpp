#include <stdio.h>
    #include <string.h>
    #include <windows.h>
    #include <iostream>

    using namespace std;
    int main()
    {
        system("MODE 80,30");
         SetConsoleTitle("GTA-IV & CitizenFX FIX v8.0 BY: MEGAMIND");
           short choice;
cout<<"\n\t\tGTA-IV \t CitizenFX\n"<<endl;
cout<<"\t1. Launch GTA IV Windowed Mode\n"<<endl;
cout<<"\t2. Launch GTA IV Normal Mode\n"<<endl;
cout<<"\t3. Launch CitizenFX Launcher(needs all files of CitizenFx \n\tto be installed on game directory) Windowed Mode\n"<<endl;
cout<<"\t4. Launch CitizenFX Launcher(needs all files of CitizenFx \n\tto be installed on game directory) Normal Mode\n"<<endl;
cout<<"\t5. Launch CitizenFX Launcher from CitizenMP-IV Windowed Mode\n"<<endl;
cout<<"\t6. Launch CitizenFX Launcher from CitizenMP-IV Normal Mode\n"<<endl;
cout<<"\t7. Launch CitizenFX (needs all files of CitizenFx \n\tto be installed on game directory) Windowed Mode\n"<<endl;
cout<<"\t8. Launch CitizenFX (needs all files of CitizenFx \n\tto be installed on game directory) Normal Mode\n"<<endl;
cout<<"\t9. Launch CitizenFX from CitizenMP-IV Windowed Mode\n"<<endl;
cout<<"\t10. Launch CitizenFX from CitizenMP-IV Normal Mode\n"<<endl;
cout<<"\tYour choice:"<<endl;
cin >> choice;
switch (choice)
{
    case 1:
         system("start LaunchGTAIV.exe -windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
    case 2:
         system("start LaunchGTAIV.exe -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        case 3:
         system("start Launcher.exe -windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
		case 4:
         system("start Launcher.exe -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        case 5:
         system("start CitizenMP-IV\\Launcher.exe -windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
		 case 6:
         system("start CitizenMP-IV\\Launcher.exe -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        case 7:
         system("start CitizenFX.exe -windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
		 case 8:
         system("start CitizenFX.exe -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        case 9:
         system("start CitizenMP-IV\\CitizenFX.exe -windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
		case 10:
         system("start CitizenMP-IV\\CitizenFX.exe -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
        break;
        default:
         cout << "Invalid option";
}
          Sleep(4000);
      }
