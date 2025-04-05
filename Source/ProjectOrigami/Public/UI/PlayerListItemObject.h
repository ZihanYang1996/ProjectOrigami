// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerListItemObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UPlayerListItemObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	APlayerState* PlayerState;
};
