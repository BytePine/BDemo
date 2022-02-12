// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/UISubsystem.h"
#include "BFrameSettings.h"
#include "Blueprint/BaseWidget.h"
#include "DataTable/UITableRow.h"

UUISubsystem::UUISubsystem()
	:UWorldSubsystem()
	,UITable(nullptr)
	,DefaultUITable(nullptr)
{
	
}

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!UITable)
	{
		const FSoftObjectPath* UITableObjectPath = &GetDefault<UBFrameSettings>()->UITable;
		if (UITableObjectPath && UITableObjectPath->IsValid())
		{
			UITable = Cast<UDataTable>(UITableObjectPath->TryLoad());
		}
	}

	if (!DefaultUITable)
	{
		const FSoftObjectPath* DefaultUITableObjectPath = &GetDefault<UBFrameSettings>()->DefaultUITable;
		if (DefaultUITableObjectPath && DefaultUITableObjectPath->IsValid())
		{
			DefaultUITable = Cast<UDataTable>(DefaultUITableObjectPath->TryLoad());
		}
	}
	
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	ClearAll();
}

void UUISubsystem::OpenUI(FName UIName, FString Params)
{
	OpenUINoStack(UIName, Params);
}

void UUISubsystem::OpenUINoStack(FName UIName, FString Params)
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

void UUISubsystem::SetDefault(FName DefaultName)
{
	if (!IsValid(DefaultUITable))
	{
		return;
	}
	
	TSet<FName> DefaultSet;
	TArray<FName> UIArray;

	FName NextDefault;
	do
	{
		FString ContextString;
		FDefaultUITableRow* DefaultUITableRow = DefaultUITable->FindRow<FDefaultUITableRow>(DefaultName, ContextString);
		if (DefaultUITableRow)
		{
			if (DefaultSet.Contains(DefaultUITable->RowStructName))
			{
				NextDefault = FName();
			}
			else
			{
				DefaultSet.Add(DefaultUITable->RowStructName);
				NextDefault = DefaultUITableRow->Parent;

				for (FName UIName : DefaultUITableRow->UINameArray)
				{
					UIArray.AddUnique(UIName);
				}
			}
		}
		else
		{
			NextDefault = FName();
		}
	}
	while (!NextDefault.IsNone());

	for (int i = UIArray.Num() - 1; i >= 0; --i)
	{
		OpenUINoStack(UIArray[i], FString());
	}
}

void UUISubsystem::ClearAll()
{
	for (const auto Tuple : WidgetMap)
	{
		Tuple.Value->NativeClose();
	}

	WidgetMap.Empty();
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
