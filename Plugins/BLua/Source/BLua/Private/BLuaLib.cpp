// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaLib.h"
#include "lua.hpp"

#include "Libs/BLuaLog.h"
#include "Libs/BLuaFile.h"

void luaL_OpenBLibs(lua_State* L)
{
	luaL_OpenBLogs(L);
	luaL_OpenBFile(L);
}