// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaFile.h"
#include "BLuaDeveloper.h"
#include "lua.hpp"

int lua_BLoadFile(lua_State* L)
{
	FBLuaDeveloper::PrintStack(L);
	
	return 1;
}

BLUA_API void luaF_SetSearcher(lua_State* L)
{
	lua_getglobal(L, "package");
	
	lua_newtable(L);
	lua_pushcfunction(L, lua_BLoadFile);
	lua_rawseti(L, -2, -1);

	lua_setfield(L, -2, "searchers");
	
	lua_pop(L, 1);
}

void luaL_OpenBFile(lua_State* L)
{
	luaF_SetSearcher(L);
}