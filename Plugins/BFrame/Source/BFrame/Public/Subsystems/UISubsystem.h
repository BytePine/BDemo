// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UISubsystem.generated.h"

class UBaseWidget;
class UDataTable;
struct FUITableRow;

/**
 * UI系统
 */
UCLASS()
class BFRAME_API UUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UUISubsystem();
	
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
	 * @brief 打开UI不入栈
	 * @param UIName UI名字
	 * @param Params 打卡参数
	 */
	UFUNCTION(BlueprintCallable)
	void OpenUINoStack(FName UIName, FString Params);
	
	/**
	 * @brief 关闭UI
	 * @param UIName UI名字
	 */
	UFUNCTION(BlueprintCallable)
	void CloseUI(FName UIName);

	/**
	 * @brief 设置默认
	 * @param DefaultName 默认名字
	 */
	UFUNCTION(BlueprintCallable)
	void SetDefault(FName DefaultName);
	
	/**
	 * @brief 清理所有UI
	 */
	UFUNCTION(BlueprintCallable)
	void ClearAll();
	
	/**
	 * @brief 是否正在打开
	 * @param UIName UI名字
	 * @return 是否正在打开
	 */
	UFUNCTION(BlueprintPure)
	bool IsOpening(FName UIName) const;

	/**
	 * @brief 连接参数
	 * @param ParamsBefore 前部参数
	 * @param ParamsAfter 后部参数
	 * @return 参数
	 */
	UFUNCTION(BlueprintPure)
	static FString LinkParams(FString ParamsBefore, FString ParamsAfter);

protected:
	virtual void OnWorldInitializedActors(const UWorld::FActorsInitializedParams& OnActorInitParams);
	
private:
	/**
	 * @brief 获取UI行数据
	 * @param UIName UI名字
	 * @return UI行数据
	 */
	FUITableRow* GetUITableRow(FName UIName) const;
	
protected:
	/**
	 * @brief UI表
	 */
	UPROPERTY(BlueprintReadOnly)
	UDataTable* UITable;

	/**
	 * @brief 默认UI表
	 */
	UPROPERTY(BlueprintReadOnly)
	UDataTable* DefaultUITable;
	
	/**
	 * @brief 控件字典
	 */
	UPROPERTY()
	TMap<FName, UBaseWidget*> WidgetMap;

	/**
	 * @brief 控件栈
	 */
	UPROPERTY()
	TArray<FName> WidgetStack;

private:
	FDelegateHandle WorldInitializedActorsHandle;
};
