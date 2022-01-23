// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaLib.h"
#include "lua.hpp"

#include "Libs/BLuaLog.h"
#include "Libs/BLuaFile.h"

void luaL_openBLibs(lua_State* L)
{
	luaL_openBLogs(L);
	luaL_openBFile(L);
}