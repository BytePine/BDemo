// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UITableRow.generated.h"

class UBaseWidget;

UENUM()
enum class EHierarchy : uint8
{
	/**
	 * @brief 背景层
	 */
	Background,
	
	/**
	 * @brief 静态层
	 */
	Static,
	
	/**
	 * @brief 动态层
	 */
	Dynamic,
	
	/**
	 * @brief 提示层
	 */
	Tips,
	
	/**
	 * @brief 最高层
	 */
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
	/**
	 * @brief 默认参数
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString DefaultParam;
	
	/**
	 * @brief 控件
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<UBaseWidget> Widget;

	/**
	 * @brief 层级
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EHierarchy Hierarchy;
};
