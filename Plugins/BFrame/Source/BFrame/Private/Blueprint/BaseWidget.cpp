// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Blueprint/BaseWidget.h"

UBaseWidget::UBaseWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	,Status(EWidgetStatus::None)
{
	
}

void UBaseWidget::NativeConstruct()
{
	Status = EWidgetStatus::Construct;
	
	Super::NativeConstruct();
}

void UBaseWidget::NativeDestruct()
{
	Status = EWidgetStatus::Destruct;
	
	Super::NativeDestruct();
}

void UBaseWidget::NativeOpen(FString Params)
{
	Status = EWidgetStatus::Open;
}

EWidgetStatus UBaseWidget::GetStatus() const
{
	return Status;
}
