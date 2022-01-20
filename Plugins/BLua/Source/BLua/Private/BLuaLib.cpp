// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaLib.h"
#include "lua.hpp"

#include "Libs/BLuaLog.h"

BLUA_API void luaL_openBLibs(lua_State* L)
{
	luaL_openBLogs(L);
}