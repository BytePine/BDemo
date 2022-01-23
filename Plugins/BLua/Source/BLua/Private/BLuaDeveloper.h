// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

BLUA_API DECLARE_LOG_CATEGORY_EXTERN(LogBLuaDeveloper, Log, All);

struct lua_State;

class FBLuaDeveloper
{
public:
	static void Log(FString String);
	static void Warning(FString String);
	static void Error(FString String);
	
	static void PrintStack(lua_State* L);
};