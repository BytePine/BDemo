// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaFile.h"
#include "BLuaDeveloper.h"
#include "lua.hpp"

int lua_BLoadFile(lua_State* L)
{
	return 1;
}

void luaL_openBFile(lua_State* L)
{
	lua_pushinteger(L, 1);
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "serchers");
	
	FBLuaDeveloper::PrintStack(L);
}