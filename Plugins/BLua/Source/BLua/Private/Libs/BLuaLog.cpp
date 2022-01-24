// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaLog.h"
#include "lua.hpp"

DEFINE_LOG_CATEGORY(LogBLua);

int lua_BLog(lua_State* L)
{
	FString StrLog;
	const int32 NArgs = lua_gettop(L);
	for (int32 i = 1; i <= NArgs; ++i)
	{
		const char* arg = luaL_tolstring(L, i, nullptr);
		if (!arg)
		{
			arg = "";
		}
		StrLog += UTF8_TO_TCHAR(arg);
		StrLog += TEXT(" ");
	}

	UE_LOG(LogBLua, Log, TEXT("%s"), *StrLog);

	return 0;
}

int lua_BWarning(lua_State* L)
{
	FString StrLog;
	const int32 NArgs = lua_gettop(L);
	for (int32 i = 1; i <= NArgs; ++i)
	{
		const char* arg = luaL_tolstring(L, i, nullptr);
		if (!arg)
		{
			arg = "";
		}
		StrLog += UTF8_TO_TCHAR(arg);
		StrLog += TEXT(" ");
	}

	UE_LOG(LogBLua, Warning, TEXT("%s"), *StrLog);

	return 0;
}

int lua_BError(lua_State* L)
{
	FString StrLog;
	const int32 NArgs = lua_gettop(L);
	for (int32 i = 1; i <= NArgs; ++i)
	{
		const char* arg = luaL_tolstring(L, i, nullptr);
		if (!arg)
		{
			arg = "";
		}
		StrLog += UTF8_TO_TCHAR(arg);
		StrLog += TEXT(" ");
	}

	UE_LOG(LogBLua, Error, TEXT("%s"), *StrLog);

	return 0;
}

void luaL_OpenBLogs(lua_State* L)
{
	lua_register(L, "print", lua_BLog);
	lua_register(L, "Log", lua_BLog);
	lua_register(L, "Warning", lua_BWarning);
	lua_register(L, "Error", lua_BError);
}