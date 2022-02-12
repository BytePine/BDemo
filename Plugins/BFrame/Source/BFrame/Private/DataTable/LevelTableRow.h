// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelTableRow.generated.h"

/**
 * 关卡表结构
 */
USTRUCT()
struct FLevelTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	/**
	 * @brief 关卡
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level;
	
	/**
	 * @brief 默认UI
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName DefaultUI;
};
