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
	// Ready state that gets replicated to all clients
	UPROPERTY(ReplicatedUsing=OnRep_bIsReady)
	bool bIsReady{false};

	// Server-side function to set the ready state
	UFUNCTION(BlueprintCallable)
	void SetReadyState(bool bNewIsReady);

	// Clinent calls this function to request the server to set the ready state
	// Marked reliable to ensure the server gets the message
	UFUNCTION(Server, Reliable)
	void ServerSetReadyState(bool bNewIsReady);

protected:
	UFUNCTION()
	void OnRep_bIsReady();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
