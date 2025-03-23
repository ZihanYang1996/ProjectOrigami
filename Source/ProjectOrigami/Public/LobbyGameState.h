// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

// Declare a delegate the player list changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerListChangedSignature);

UCLASS()
class PROJECTORIGAMI_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// The PlayerArray is an array of all PlayerStates, auyomatically maintained on both server and clients
	const TArray<TObjectPtr<APlayerState>>& GetPlayers() const { return PlayerArray; }

	// Call this whenever a player's ready status changes
	void CheckAllPlayersReady();

	UFUNCTION()
	void OnPlayerListChanged();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerListChangedSignature OnPlayerListChangedDelegate;
};
