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

void UBLuaSubsystem::AddSearcher(int(* Searcher)(lua_State*), int Index)
{
	// if #package.searchers 
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "searchers");
	lua_remove(L, -2);
	if(!lua_istable(L, -1))
	{
		UE_LOG(LogBLuaDeveloper, Warning, TEXT("Invalid package.serachers!"));
		return;
	}

	const uint32 Len = lua_rawlen(L, -1);
	Index = Index < 0 ? (int)(Len + Index + 2) : Index;
	for (int e = (int)Len + 1; e > Index; e--)
	{
		lua_rawgeti(L, -1, e - 1);
		lua_rawseti(L, -2, e);
	}
    
	lua_pushcfunction(L, Searcher);
	lua_rawseti(L, -2, Index);
	lua_pop(L, 1);
}
