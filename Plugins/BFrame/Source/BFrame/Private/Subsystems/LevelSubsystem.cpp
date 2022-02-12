// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/LevelSubsystem.h"
#include "Subsystems/UISubsystem.h"

void ULevelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Collection.InitializeDependency(UUISubsystem::StaticClass());
}

void ULevelSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
