#include "SQMain.h"
#include "SQConsts.h"
#include "SQFuncs.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdarg.h>
#include <string>
#include <fstream>
#include <thread>
using namespace std;

PluginFuncs* VCMP;
HSQUIRRELVM v;
HSQAPI sq;
void OnSquirrelScriptLoad() {
	// See if we have any imports from Squirrel
	size_t size;
	int32_t sqId = VCMP->FindPlugin(const_cast<char*>("SQHost2"));
	const void** sqExports = VCMP->GetPluginExports(sqId, &size);

	// We do!
	if (sqExports != NULL && size > 0) {
		// Cast to a SquirrelImports structure
		SquirrelImports** sqDerefFuncs = (SquirrelImports**)sqExports;

		// Now let's change that to a SquirrelImports pointer
		SquirrelImports* sqFuncs = (SquirrelImports*)(*sqDerefFuncs);

		// Now we get the virtual machine
		if (sqFuncs) {
			// Get a pointer to the VM and API
			v = *(sqFuncs->GetSquirrelVM());
			sq = *(sqFuncs->GetSquirrelAPI());

			// Register functions
			RegisterFuncs(v);
			// Register constants
			RegisterConsts(v);
		}
	}
	else
		OutputError("Failed to attach to SQHost2.");
}

uint8_t OnPluginCommand(uint32_t type, const char* text) {
	switch (type) {
	case 0x7D6E22D8:
		OnSquirrelScriptLoad();
		break;
	default:
		break;
	}
	return 1;
}
size_t c = 0; 
size_t d = 0;
void foo()
{
	Sleep(5000);
	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
loop:
	GetConsoleScreenBufferInfo(
		hcons,
		&info
	);
	size_t a = info.dwCursorPosition.X ;
	size_t b = info.dwCursorPosition.Y;
	if(a==c && b==d)
	{
		Sleep(1000);
		goto loop;
	}
	size_t length = info.dwSize.X;
	COORD start;
	start.X = 0; start.Y = 0;
	CHAR_INFO* buffer = (CHAR_INFO*)
		malloc(sizeof(CHAR_INFO) * (size_t)info.dwSize.X * info.dwSize.Y);
	SMALL_RECT rect;
	rect.Top = d;
	rect.Left = 0;
	rect.Bottom = b;
	rect.Right = length-1;
	bool read = ReadConsoleOutput(
		hcons,
		buffer,
		info.dwSize,
		start,
		&rect);
	if (read != 0)
	{
		std::fstream myfile;
		myfile.open("logfile.txt",std::fstream::out|std::fstream::app);
		size_t total = (b - d) * length + a ;
		//printf("a,b,c,d is %d,%d,%d,%d\n", a, b, c, d);
		for (size_t i = c; i < total; i++)
		{
			myfile << buffer[i].Char.AsciiChar;
			if ((i + 1) %length  == 0)
			{
				myfile << std::endl;
			}
		}
		myfile.close();
		free(buffer);
		c = a; d = b;
	}
	else {
		printf("failure read\n");
		printf("%d", GetLastError());
	}
loopend:
	Sleep(2000);
	goto loop;
}

uint8_t OnServerInitialise()
{
	thread t1(&foo);
	t1.detach();
	return 1;
}
extern "C" unsigned int VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo) {
    VCMP = pluginFuncs;

	// Plugin information
	pluginInfo->pluginVersion = 0x110;
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;
	strcpy(pluginInfo->name, "squirrel_logfile");
	pluginCalls->OnPluginCommand = OnPluginCommand;
	pluginCalls->OnServerInitialise = OnServerInitialise;
	return 1;
}

