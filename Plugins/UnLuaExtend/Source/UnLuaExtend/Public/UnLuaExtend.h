// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct lua_State;

class FUnLuaExtendModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UNLUAEXTEND_API void RegisterPackages(lua_State* L);
UNLUAEXTEND_API void RequireMainModule(lua_State* L);