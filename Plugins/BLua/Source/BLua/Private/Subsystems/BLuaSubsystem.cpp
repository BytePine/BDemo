// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/BLuaSubsystem.h"

#include "BLua.h"
#include "lua.hpp"

void UBLuaSubsystem::CreateState()
{
	if (!L)
	{
		L = lua_newstate(nullptr, nullptr);
		check(L);

		luaL_openlibs(L);
		
	}

	UE_LOG(LogBLua, Log, TEXT("CreateState"));
}
