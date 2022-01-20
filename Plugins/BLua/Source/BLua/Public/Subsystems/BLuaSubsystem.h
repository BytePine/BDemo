// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BLuaSubsystem.generated.h"

struct lua_State;

/**
 * 
 */
UCLASS()
class BLUA_API UBLuaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateState();
	
private:
	lua_State* L;
};
