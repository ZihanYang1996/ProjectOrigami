// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing=OnRep_bIsReady)
	bool bIsReady{false};

	UFUNCTION(BlueprintCallable)
	void SetReadyState(bool bNewIsReady);

protected:
	UFUNCTION()
	void OnRep_bIsReady();
};
