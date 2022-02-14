// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/LevelSubsystem.h"
#include "Subsystems/UISubsystem.h"
#include "DataTable/LevelTableRow.h"
#include "BFrameSettings.h"
#include "Kismet/GameplayStatics.h"

ULevelSubsystem::ULevelSubsystem()	
	:Super()
	,LevelTable(nullptr)
{
	
}

void ULevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!IsValid(LevelTable))
	{
		const FSoftObjectPath* LevelTableObjectPath = &GetDefault<UBFrameSettings>()->LevelTable;
		if (LevelTableObjectPath && LevelTableObjectPath->IsValid())
		{
			LevelTable = Cast<UDataTable>(LevelTableObjectPath->TryLoad());
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("ULevelSubsystem::Initialize"));
	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &ULevelSubsystem::OnLevelAddedToWorld);
}

void ULevelSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelSubsystem::OpenLevel(FName LevelName)
{
	if (!IsValid(LevelTable))
	{
		return;
	}

	const FString ContextString;
	const FLevelTableRow* LevelTableRow = LevelTable->FindRow<FLevelTableRow>(LevelName, ContextString);
	if (LevelTableRow)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelTableRow->Level);
	}
}

void ULevelSubsystem::OnLevelAddedToWorld(ULevel* Level, UWorld* World)
{
	UE_LOG(LogTemp, Log, TEXT("ULevelSubsystem::OnPostWorldInit %s %s"), *Level->GetName(), *World->GetName());
}
