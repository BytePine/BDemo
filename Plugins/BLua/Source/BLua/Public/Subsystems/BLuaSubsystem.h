// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BLuaSubsystem.generated.h"

struct lua_State;

DECLARE_MULTICAST_DELEGATE_OneParam(FLuaStateDelegate, lua_State*);

/**
 * 
 */
UCLASS()
class BLUA_API UBLuaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void CreateState();

	UFUNCTION(BlueprintCallable)
	void DestroyState();

public:
	void AddSearcher(int (*Searcher)(lua_State *), int Index);
	
public:
	FLuaStateDelegate OnLuaStateCreated;
	
private:
	lua_State* L;
};
