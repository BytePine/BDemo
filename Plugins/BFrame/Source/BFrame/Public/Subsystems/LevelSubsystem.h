// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelSubsystem.generated.h"

class UDataTable;

/**
 * 关卡系统
 */
UCLASS()
class BFRAME_API ULevelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	ULevelSubsystem();
	
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void OpenLevel(FName LevelName);
	
protected:
	/**
	 * @brief 关卡表
	 */
	UPROPERTY(BlueprintReadOnly)
	UDataTable* LevelTable;
};
