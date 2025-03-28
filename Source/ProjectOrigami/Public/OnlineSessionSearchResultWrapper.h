// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "UObject/NoExportTypes.h"
#include "OnlineSessionSearchResultWrapper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UOnlineSessionSearchResultWrapper : public UObject
{
	GENERATED_BODY()

public:
	FOnlineSessionSearchResult SearchResult;
};
