#include "SQConsts.h"
#include <cstdio>


extern HSQAPI sq;

SQInteger RegisterSquirrelConst(HSQUIRRELVM v, const SQChar* cname, SQInteger cvalue) {
	sq->pushconsttable(v);
	sq->pushstring(v, cname, -1);
	sq->pushinteger(v, cvalue);
	sq->newslot(v, -3, SQFalse);
	sq->pop(v, 1);

	return 0;
}

void RegisterConsts(HSQUIRRELVM v) {
	//RegisterSquirrelConst(v, "GEOIP_CHARSET_ISO_8859_1", 0);
}