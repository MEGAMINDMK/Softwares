#include <stdlib.h>
#include <stdio.h>
#include "SQFuncs.h"
#include <cstdio>
#include <fstream>
extern PluginFuncs* VCMP;
extern HSQAPI sq;

_SQUIRRELDEF(SQ_export) {
    SQInteger iArgCount = sq->gettop(v);
    if (iArgCount == 1) {
        HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        
        GetConsoleScreenBufferInfo(
            hcons,
            &info
        );
        size_t y = info.dwCursorPosition.Y + 1;
        size_t x = info.dwSize.X;
        //printf("y is %lu and x is %lu\n", y, x);
        COORD start;
        start.X = 0; start.Y = 0;
        CHAR_INFO* buffer = (CHAR_INFO*)
            malloc(sizeof(CHAR_INFO)*(size_t)info.dwSize.X * info.dwSize.Y);
        //if (buffer == NULL)printf("malloc failed\n");
        //printf("size is %lu\n", sizeof(CHAR_INFO) * (size_t)info.dwSize.X * info.dwSize.Y);
        SMALL_RECT rect;
        rect.Top = 0;
        rect.Left = 0;
        rect.Bottom = y - 1;
        rect.Right = x - 1;
        bool read = ReadConsoleOutput(
            hcons,
            buffer,
            info.dwSize,
            start,
            &rect);
        if (read != 0)
        {
            //for (int i = 0; i < x * y; i++)printf("%c", buffer[i]);
            std::ofstream myfile;
            myfile.open("logfile.txt");

            for (int i = 0; i < x * y; i++)
            {
                myfile << buffer[i].Char.AsciiChar;
                if ((i + 1) % x == 0)
                {
                    myfile << std::endl;
                }
            }
            myfile.close();
            free(buffer);
        }
        else printf("failure read\n");

    }
    return 0;
}

SQInteger RegisterSquirrelFunc(HSQUIRRELVM v, SQFUNCTION f, const SQChar* fname, unsigned char ucParams, const SQChar* szParams) {
	char szNewParams[32];

	sq->pushroottable(v);
	sq->pushstring(v, fname, -1);
	sq->newclosure(v, f, 0); /* create a new function */

	if (ucParams > 0) {
		ucParams++; /* This is to compensate for the root table */
		sprintf(szNewParams, "t%s", szParams);
		sq->setparamscheck(v, ucParams, szNewParams); /* Add a param type check */
	}

	sq->setnativeclosurename(v, -1, fname);
	sq->newslot(v, -3, SQFalse);
	sq->pop(v, 1);

	return 0;
}

void RegisterFuncs(HSQUIRRELVM v) {
	RegisterSquirrelFunc(v, SQ_export, "export", 0, 0);
}