// Copyright BytePine Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UnLuaExtendSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, meta=(DisplayName="UnLua Extend"))
class UNLUAEXTEND_API UUnLuaExtendSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override;
};
