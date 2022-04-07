// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "UI/UISubsystem.h"
#include "UI/BaseWidget.h"
#include "UI/UITableRow.h"
#include "BFrameSettings.h"

UUISubsystem::UUISubsystem()
	:UWorldSubsystem()
	,UITable(nullptr)
	,DefaultUITable(nullptr)
{
	
}

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!GetWorld()->IsGameWorld())
	{
		return;
	}
	
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
	
	WorldInitializedActorsHandle = FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UUISubsystem::OnWorldInitializedActors);
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();

	if (!GetWorld()->IsGameWorld())
	{
		return;
	}
	
	FWorldDelegates::OnWorldInitializedActors.Remove(WorldInitializedActorsHandle);
	
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

	ClearAll();
	
	TSet<FName> DefaultSet;
	TArray<FName> UIArray;

	FName NextDefault = DefaultName;
	do
	{
		FString ContextString;
		FDefaultUITableRow* DefaultUITableRow = DefaultUITable->FindRow<FDefaultUITableRow>(NextDefault, ContextString);
		if (DefaultUITableRow)
		{
			if (DefaultSet.Contains(NextDefault))
			{
				NextDefault = FName();
			}
			else
			{
				DefaultSet.Add(NextDefault);
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

void UUISubsystem::OnWorldInitializedActors(const UWorld::FActorsInitializedParams& OnActorInitParams)
{
	SetDefault(OnActorInitParams.World->GetFName());
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
