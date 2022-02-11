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
