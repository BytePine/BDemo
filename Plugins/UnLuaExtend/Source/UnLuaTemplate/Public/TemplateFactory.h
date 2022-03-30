// Copyright Byteyang Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TemplateFactory.generated.h"

/**
 * 
 */
UCLASS()
class UNLUATEMPLATE_API UTemplateFactory : public UObject
{
	GENERATED_BODY()

public:
	/** Deprecated constructor, ObjectInitializer is no longer needed but is supported for older classes. */
	UTemplateFactory(const FObjectInitializer& ObjectInitializer);
	
	void Produce();
};
