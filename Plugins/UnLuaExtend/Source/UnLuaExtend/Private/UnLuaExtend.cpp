// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnLuaExtend.h"
#include "UnLuaDelegates.h"
#include "LuaCore.h"
#include "UnLuaBase.h"
#include "UnLuaExtendSettings.h"
#include "LuaLog.h"

#define LOCTEXT_NAMESPACE "FUnLuaExtendModule"

void FUnLuaExtendModule::StartupModule()
{
	FUnLuaDelegates::OnLuaStateCreated.AddLambda([&](lua_State* L)
	{
		RegisterPackages(L);

		RegisterLog(L);
			
		RequireMainModule(L);
	});
}

void FUnLuaExtendModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void RegisterPackages(lua_State* L)
{
	const FString ExtendPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + TEXT("UnLuaExtend/Content/ScriptExtend")) + TEXT("/?.lua");
	AddPackagePath(L, TCHAR_TO_UTF8(*ExtendPath));
	
	UUnLuaExtendSettings* Settings = UUnLuaExtendSettings::Get();
	if (!Settings)
		return;	

	for (FString Path : Settings->LuaPackagePath)
	{
		Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + Path) + TEXT("/?.lua");
		AddPackagePath(L, TCHAR_TO_UTF8(*Path));
	}
}

void RequireMainModule(lua_State* L)
{
	UUnLuaExtendSettings* Settings = UUnLuaExtendSettings::Get();
	if (!Settings)
		return;	

	FString MainModule = Settings->MainModule;
	if (!MainModule.EndsWith(TEXT(".lua")))
	{
		MainModule += TEXT(".lua");
	}
	
	UnLua::RunFile(L, MainModule);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnLuaExtendModule, UnLuaExtend)