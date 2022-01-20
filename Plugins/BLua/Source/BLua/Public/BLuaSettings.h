// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BLuaSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta=(DisplayName=BLua))
class BLUA_API UBLuaSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static UBLuaSettings* Get()
	{
		return GetMutableDefault<UBLuaSettings>();
	}

	UBLuaSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override
	{
		return TEXT("Plugins");
	}

public:
	UPROPERTY(Config, EditDefaultsOnly, meta=(RelativeToGameContentDir))
	FDirectoryPath ScriptDirectory;

	UPROPERTY(Config, EditDefaultsOnly, meta=(RelativeToGameContentDir))
	FString MainPath;
};
