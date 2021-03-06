// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BFrameSettings.generated.h"

/**
 * BFrame设置
 */
UCLASS(Config=Game, defaultconfig, meta=(DisplayName=BFrame))
class BFRAME_API UBFrameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBFrameSettings(const FObjectInitializer& ObjectInitializer)
		:Super(ObjectInitializer)
	{
		
	}
	
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override
	{
		return TEXT("Plugins");
	}

public:
	/**
	 * @brief UI表
	 */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowedClasses="DataTable"))
	FSoftObjectPath UITable;

	/**
	 * @brief 默认UI表
	 */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="UI", meta=(AllowedClasses="DataTable"))
	FSoftObjectPath DefaultUITable;
	
	/**
	 * @brief 关卡表
	 */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Level", meta=(AllowedClasses="DataTable"))
	FSoftObjectPath LevelTable;
};
