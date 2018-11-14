        #include <cstdlib>
        #include <iostream>
        #include <windows.h>
        #include <stdio.h>
        #include <conio.h>

        int newdata = 1000;



        void ShowError(DWORD dwErrorCode)
        {
        	TCHAR* lpMessageBuffer;

        	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TCHAR*)&lpMessageBuffer, 0, NULL);

        	MessageBox(HWND_DESKTOP, lpMessageBuffer, NULL, MB_OK | MB_ICONINFORMATION);

        	LocalFree(lpMessageBuffer);
        }

        int main()
        {
        	HWND hWnd = FindWindow(0, "GTA:vice city");
          	if(hWnd == 0)
        	{
        			ShowError(GetLastError());
          	}
        	else
        	{
        		DWORD ProcessID;
        		GetWindowThreadProcessId(hWnd, &ProcessID);
        		HANDLE handleprocess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, ProcessID);
        		if(!handleprocess)
        		{
        			ShowError(GetLastError());
        		}
        		else{
        			int hack = WriteProcessMemory(handleprocess, (LPVOID)0x4AC0DE, &newdata, (DWORD)sizeof(newdata), NULL);
        			if(hack > 0){
        				printf("success!");
        			}
        			else{
        				ShowError(GetLastError());
        			}
        		}
        		CloseHandle(handleprocess);

        	}

        	getchar();
          	return 0;
        }


