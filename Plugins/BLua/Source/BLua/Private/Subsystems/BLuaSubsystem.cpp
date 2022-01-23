// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/BLuaSubsystem.h"
#include "BLuaDeveloper.h"
#include "lua.hpp"
#include "BLuaLib.h"

void UBLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FBLuaDeveloper::Log(TEXT("Initialize"));
}

void UBLuaSubsystem::Deinitialize()
{
	DestroyState();

	OnLuaStateCreated.Clear();
	
	Super::Deinitialize();

	FBLuaDeveloper::Log(TEXT("Deinitialize"));
}

void UBLuaSubsystem::CreateState()
{
	DestroyState();
	
	L = luaL_newstate();
	check(L);

	luaL_openlibs(L);

	luaL_openBLibs(L);

	OnLuaStateCreated.Broadcast(L);
	
	FBLuaDeveloper::Log(TEXT("CreateState"));
}

void UBLuaSubsystem::DestroyState()
{
	if (L)
	{
		lua_close(L);
		L = nullptr;
		
		FBLuaDeveloper::Log(TEXT("DestroyState"));
	}
}
