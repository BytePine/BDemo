// Copyright Byteyang Games, Inc. All Rights Reserved.


#include "BLuaSettings.h"

UBLuaSettings::UBLuaSettings(const FObjectInitializer& ObjectInitializer)
	:UDeveloperSettings(ObjectInitializer)
{
	ScriptDirectory.Path = TEXT("Script");
	MainPath = TEXT("Main.lua");
}
