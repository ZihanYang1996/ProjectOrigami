// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

// Declare a delegate the player list changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerListChangedSignature);

// Declare a delegate for when the lobby name changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyNameChangedSignature);


UCLASS()
class PROJECTORIGAMI_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALobbyGameState();

	UPROPERTY(ReplicatedUsing=OnRep_LobbyName, BlueprintReadOnly)
	FString LobbyName;

	void SetLobbyName(const FString& InLobbyName);

	FString GetLobbyName() const;

	FOnLobbyNameChangedSignature OnLobbyNameChangedDelegate;
	

	// // Call this whenever a player's ready status changes
	void CheckAllPlayersReady();

	UFUNCTION()
	void OnPlayerListChanged();
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerListChangedSignature OnPlayerListChangedDelegate;

protected:
	UFUNCTION()
	void OnRep_LobbyName();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
