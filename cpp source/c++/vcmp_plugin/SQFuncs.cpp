#include <stdlib.h>
#include <stdio.h>
#include "SQFuncs.h"
#include <cstdio>

extern PluginFuncs* VCMP;
extern HSQAPI sq;

_SQUIRRELDEF(SQ_hello) {
    SQInteger iArgCount = sq->gettop(v);
    if (iArgCount == 1) {
        printf("Hello World!\n");
    }
    return 0;
}

_SQUIRRELDEF(SQ_AddNumbers) {
	SQInteger iArgCount = sq->gettop(v);
	if (iArgCount == 3) {
		SQInteger a;
		sq->getinteger(v, 2, &a);//actor id
        SQInteger b;
		sq->getinteger(v, 3, &b);//angle
        int c = a + b;
		sq->pushinteger(v, c);
		//we are returning a value. so return 1
		return 1;
		
    }
    else printf("Format: AddNumbers( 30, 40 );\n");
	sq->pushbool(v, SQFalse);
	return 1;
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
	RegisterSquirrelFunc(v, SQ_hello, "hello", 0, 0);
	RegisterSquirrelFunc(v, SQ_AddNumbers, "AddNumbers", 0, 0);

}