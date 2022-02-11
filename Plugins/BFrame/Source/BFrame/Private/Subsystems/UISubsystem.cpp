// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/UISubsystem.h"
#include "BFrameSettings.h"
#include "Blueprint/BaseWidget.h"
#include "DataTable/UITableRow.h"

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const FSoftObjectPath* UITableObjectPth = &GetDefault<UBFrameSettings>()->UITable;
	if (UITableObjectPth && UITableObjectPth->IsValid())
	{
		UITable = Cast<UDataTable>(UITableObjectPth->TryLoad());
	}
	
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UUISubsystem::OpenUI(FName UIName, FString Params)
{
	const FUITableRow* UITableRow = GetUITableRow(UIName);
	if (!UITableRow)
	{
		return;
	}

	UBaseWidget* Widget = nullptr;
	
	if (WidgetMap.Contains(UIName))
	{
		Widget = WidgetMap[UIName];
	}
	else
	{
		const UClass* WidgetClass = UITableRow->Widget.LoadSynchronous();
		if (WidgetClass->IsValidLowLevel())
		{
			Widget = NewObject<UBaseWidget>(this, WidgetClass, UIName);
			Widget->AddToViewport(static_cast<int32>(UITableRow->Hierarchy));
			
			WidgetMap.Add(UIName, Widget);
		}
	}

	if (Widget)
	{
		Widget->NativeOpen(LinkParams(UITableRow->DefaultParam, Params));
	}
}

void UUISubsystem::CloseUI(FName UIName)
{
	if (!WidgetMap.Contains(UIName))
	{
		return;
	}

	UBaseWidget* Widget = WidgetMap[UIName];
	Widget->NativeClose();

	WidgetMap.Remove(UIName);
}

bool UUISubsystem::IsOpening(FName UIName) const
{
	return WidgetMap.Contains(UIName);
}

FString UUISubsystem::LinkParams(FString ParamsBefore, FString ParamsAfter)
{
	if (ParamsBefore.IsEmpty())
	{
		return ParamsAfter;
	}

	if (ParamsAfter.IsEmpty())
	{
		return ParamsBefore;
	}
	
	return FString::Printf(TEXT("%s|%s"), *ParamsBefore, *ParamsAfter);
}

FUITableRow* UUISubsystem::GetUITableRow(FName UIName) const
{
	if (!UITable->IsValidLowLevel())
	{
		return nullptr;
	}

	const FString ContentString;
	FUITableRow* UITableRow = UITable->FindRow<FUITableRow>(UIName, ContentString);
	return UITableRow;
}
