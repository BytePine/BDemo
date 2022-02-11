// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UISubsystem.generated.h"

class UBaseWidget;

/**
 * UI管理
 */
UCLASS()
class BFRAME_API UUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

public:
	/**
	 * @brief 打开UI
	 * @param UIName UI名字
	 * @param Params 打开参数
	 */
	UFUNCTION(BlueprintCallable)
	void OpenUI(FName UIName, FString Params);
	
	/**
	 * @brief 关闭UI
	 * @param UIName UI名字
	 */
	UFUNCTION(BlueprintCallable)
	void CloseUI(FName UIName);

	/**
	 * @brief 是否正在打开
	 * @param UIName UI名字
	 * @return 是否正在打开
	 */
	UFUNCTION(BlueprintPure)
	bool IsOpening(FName UIName) const;
	
protected:
	UPROPERTY()
	TMap<FName, UBaseWidget*> UIMap;

	UPROPERTY()
	TArray<FName> UIStack;
};
