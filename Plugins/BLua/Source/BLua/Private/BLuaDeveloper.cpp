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

	int32 top = lua_gettop(L);
	PrintString += FString::FormatAsNumber(top);
	
	UE_LOG(LogBLuaDeveloper, Log, TEXT("%s"), *PrintString);
}
