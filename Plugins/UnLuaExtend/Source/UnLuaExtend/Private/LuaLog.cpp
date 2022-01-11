// Copyright Tencent Games, Inc. All Rights Reserved.

#include "LuaLog.h"
#include "UnLua.h"

int32 Global_Log(lua_State *L)
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

	UE_LOG(LogUnLua, Log, TEXT("%s"), *StrLog);

	return 0;
}

int32 Global_Warning(lua_State *L)
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

	UE_LOG(LogUnLua, Warning, TEXT("%s"), *StrLog);
	
	return 0;
}

int32 Global_Error(lua_State *L)
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

	UE_LOG(LogUnLua, Error, TEXT("%s"), *StrLog);

	return 0;
}

void RegisterLog(lua_State *L)
{
	lua_register(L, "Log", Global_Log);
	lua_register(L, "UEPrint", Global_Log);
	lua_register(L, "Warning", Global_Warning);
	lua_register(L, "Error", Global_Error);
}