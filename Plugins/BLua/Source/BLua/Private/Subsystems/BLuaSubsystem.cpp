// Copyright BytePine Games, Inc. All Rights Reserved.


#include "Subsystems/BLuaSubsystem.h"
#include "lua.hpp"

void UBLuaSubsystem::CreateState()
{
	if (L != nullptr)
	{
		L = lua_newstate(nullptr, nullptr);
	}
}
