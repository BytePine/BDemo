// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UITableRow.generated.h"

class UBaseWidget;

UENUM()
enum class EHierarchy : uint8
{
	Background,
	Static,
	Dynamic,
	Tips,
	Top,
};

/**
 * UI表结构
 */
USTRUCT()
struct FUITableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString DefaultParam;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UBaseWidget> Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EHierarchy Hierarchy;
};
