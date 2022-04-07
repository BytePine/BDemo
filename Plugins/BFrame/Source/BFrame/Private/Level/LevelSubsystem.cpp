// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Level/LevelSubsystem.h"
#include "Level/LevelTableRow.h"
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

	if (!GetWorld()->IsGameWorld())
	{
		return;
	}
	
	if (!IsValid(LevelTable))
	{
		const FSoftObjectPath* LevelTableObjectPath = &GetDefault<UBFrameSettings>()->LevelTable;
		if (LevelTableObjectPath && LevelTableObjectPath->IsValid())
		{
			LevelTable = Cast<UDataTable>(LevelTableObjectPath->TryLoad());
		}
	}
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
