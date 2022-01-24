// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/BLuaSubsystem.h"
#include "BLuaDeveloper.h"
#include "lua.hpp"
#include "BLuaLib.h"
#include "BLuaSettings.h"

void UBLuaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBLuaSubsystem::Deinitialize()
{
	DestroyState();

	OnLuaStateCreated.Clear();
	
	Super::Deinitialize();
}

void UBLuaSubsystem::CreateState()
{
	DestroyState();
	
	L = luaL_newstate();

	luaL_openlibs(L);
	luaL_OpenBLibs(L);

	OnLuaStateCreated.Broadcast(L);
	
	const UBLuaSettings* BLuaSettings = UBLuaSettings::Get();
	const FString PackagePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + BLuaSettings->ScriptDirectory.Path);
	AddPackagePath(PackagePath);
	Require(PackagePath + TEXT("/") + BLuaSettings->MainPath);
	
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

void UBLuaSubsystem::AddPackagePath(FString Path)
{
	if (Path.IsEmpty())
	{
		FBLuaDeveloper::Warning(TEXT("AddPackagePath Path Is Empty"));
		return;
	}
	
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path");
	char FinalPath[MAX_SPRINTF];
	FCStringAnsi::Sprintf(FinalPath, "%s;%s", lua_tostring(L, -1), TCHAR_TO_ANSI(*Path));
	lua_pushstring(L, FinalPath);
	lua_setfield(L, -3, "path");
	lua_pop(L, 2);
}

void UBLuaSubsystem::Require(FString Path)
{
	if (Path.IsEmpty())
	{
		FBLuaDeveloper::Warning(TEXT("Require Path Is Empty"));
		return;
	}
	TArray<uint8> FileArray;
	FFileHelper::LoadFileToArray(FileArray, *Path, FILEREAD_Silent);
	
	luaL_loadbuffer(L, reinterpret_cast<const char*>(FileArray.GetData()), FileArray.Num(), "Main");
	lua_call(L, 0, 0);
	
	FBLuaDeveloper::Log(FString::Printf(TEXT("Require Path:%s"), *Path));
}

lua_State* UBLuaSubsystem::GetLuaState() const
{
	return L;
}
