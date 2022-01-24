// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "BLuaDeveloper.h"
#include "lua.hpp"

DEFINE_LOG_CATEGORY(LogBLuaDeveloper);

void FBLuaDeveloper::Log(FString String)
{
	UE_LOG(LogBLuaDeveloper, Log, TEXT("%s"), *String);
}

void FBLuaDeveloper::Warning(FString String)
{
	UE_LOG(LogBLuaDeveloper, Warning, TEXT("%s"), *String);
}

void FBLuaDeveloper::Error(FString String)
{
	UE_LOG(LogBLuaDeveloper, Error, TEXT("%s"), *String);
}

void FBLuaDeveloper::PrintStack(lua_State* L)
{
	FString PrintString;
	
	const int32 Top = lua_gettop(L);
	PrintString += FString::Printf(TEXT("Top:%d\n"), Top);
	
	for (int32 i = Top; i > 0; i--)
	{
		if (lua_isnil(L, i))
		{
			PrintString += FString::Printf(TEXT("%d:nil\n"), i);
		}else if (lua_istable(L, i))
		{
			PrintString += FString::Printf(TEXT("%d:table\n"), i);
		}else if (lua_islightuserdata(L, i))
		{
			PrintString += FString::Printf(TEXT("%d:lightuserdata\n"), i);
		}else if (lua_isfunction(L, i))
		{
			PrintString += FString::Printf(TEXT("%d:function\n"), i);
		}
		else
		{
			PrintString += FString::Printf(TEXT("%d:%s\n"), i, UTF8_TO_TCHAR(lua_tostring(L, i)));
		}
	}
	
	UE_LOG(LogBLuaDeveloper, Log, TEXT("%s"), *PrintString);
}
