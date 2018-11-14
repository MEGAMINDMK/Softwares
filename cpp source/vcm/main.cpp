#include <iostream>
#include <windows.h>

using namespace std;

void error(string errMsg);
long int readFromMem(DWORD address, LPCSTR windowName);
void writeToMem(DWORD address, LPCSTR windowName, long int newValue);

int main()
{
	system("color c");
	system("title Vice City Money Hack by MEGAMIND");

	DWORD address = 0x94ADC8;
	LPCSTR windowName = "GTA: Vice City";

	try
	{
		long int currentMoney = readFromMem(address, windowName);
		long int newAmount = 0;

		cout << "Vice City Money Hack by MEGAMIND" << endl;
		//cout << endl << "Current Money = " << currentMoney << endl;

		moneyError:
		cout << "Enter New Money Amount: ";
		cin >> newAmount;

		if (newAmount > 999999999 || newAmount < 0)
		{
			cout << endl << "MONEY AMOUNT CAN ONLY BE FROM 0 to 999,999,999 Try Again" << endl;
			goto moneyError;
		}

		else
		{
			writeToMem(address, windowName, newAmount);
			cout << "Success" << endl << endl;
		}

		system("pause");
	}

	catch (string erreMsg)
	{
		cout << erreMsg << endl;
	}

	return 0;
}

void error(string errMsg)
{
	throw errMsg;
}

long int readFromMem(DWORD address, LPCSTR windowName)
{
	long int value;
	HWND windowHandle = FindWindow(0, windowName);

	if (! windowHandle)
	{
		error("error, can't find window [Launch the Game]");
	}

	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

		if (! processHandle)
		{
			error("error, can't find process [Run this exe as Admin]");
		}

		else
		{
			int status = ReadProcessMemory(processHandle, (LPVOID) address, &value, sizeof(value), 0); //LPVOID = void *
			CloseHandle(processHandle);

			if (status > 0)
			{
				return value;
			}

			else
			{
				error("error, failed to read value [Run this exe as Admin]");
			}
		}
	}
}

void writeToMem(DWORD address, LPCSTR windowName, long int newValue)
{
	HWND windowHandle = FindWindow(0, windowName);

	if (! windowHandle)
	{
		error("error, can't find window [Run this exe as Admin]");
	}

	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

		if (! processHandle)
		{
			error("error, can't find process [Run this exe as Admin]");
		}

		else
		{
			int status = WriteProcessMemory(processHandle, (LPVOID) address, &newValue, (DWORD) sizeof(newValue), NULL);
			CloseHandle(processHandle);

			if (status < 0)
			{
				error("error, failed to write value [Run this exe as Admin]");
			}
		}
	}
}


