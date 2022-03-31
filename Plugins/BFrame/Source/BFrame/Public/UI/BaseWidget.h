// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

UENUM()
enum class EWidgetStatus
{
	None,
	Construct,
	Open,
	Close,
	Destruct
};

/**
 * 基础控件
 */
UCLASS()
class BFRAME_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBaseWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	
	virtual void NativeDestruct() override;
	
	virtual void NativeOpen(FString Params);

	virtual void NativeClose();

protected:
	/**
	 * @brief 打开事件
	 * @param Params 打开参数
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnOpen(const FString& Params);

	/**
	 * @brief 关闭事件
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnClose();
	
public:
	/**
	 * @brief 获取控件状态
	 * @return 控件状态
	 */
	UFUNCTION(BlueprintPure)
	EWidgetStatus GetStatus() const;
	
private:
	/**
	 * @brief 控件状态
	 */
	EWidgetStatus Status;
};
