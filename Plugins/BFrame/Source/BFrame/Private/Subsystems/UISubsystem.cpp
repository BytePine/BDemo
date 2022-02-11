// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "Subsystems/UISubsystem.h"

void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UUISubsystem::OpenUI(FName UIName, FString Params)
{
	
}

void UUISubsystem::CloseUI(FName UIName)
{
	
}

bool UUISubsystem::IsOpening(FName UIName) const
{
	return UIMap.Contains(UIName);
}
