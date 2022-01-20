// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/BLuaSubsystem.h"

#include "BLua.h"
#include "lua.hpp"
#include "BLuaLib.h"

void UBLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogBLuaDeveloper, Log, TEXT("Initialize"));
}

void UBLuaSubsystem::Deinitialize()
{
	DestroyState();

	OnLuaStateCreated.Clear();
	
	Super::Deinitialize();

	UE_LOG(LogBLuaDeveloper, Log, TEXT("Deinitialize"));
}

void UBLuaSubsystem::CreateState()
{
	DestroyState();
	
	L = luaL_newstate();
	check(L);

	luaL_openlibs(L);

	luaL_openBLibs(L);

	OnLuaStateCreated.Broadcast(L);
	
	UE_LOG(LogBLuaDeveloper, Log, TEXT("CreateState"));
}

void UBLuaSubsystem::DestroyState()
{
	if (L)
	{
		lua_close(L);
		L = nullptr;
		
		UE_LOG(LogBLuaDeveloper, Log, TEXT("DestroyState"));
	}
}
