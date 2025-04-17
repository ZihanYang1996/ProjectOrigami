// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"


UCLASS()
class PROJECTORIGAMI_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	bool GetReadyState() const { return bIsReady; }
	FString GetCustomPlayerName() const { return CustomPlayerName; }
	
	void SetCustomePlayerName(const FString& NewName);

	void ToggleReady();

	// Client calls this function to set the player name
	// Marked reliable to ensure the server gets the message
	UFUNCTION(Server, Reliable)
	void ServerSetCustomePlayerName(const FString& NewName);

	// Clinent calls this function to request the server to set the ready state
	// Marked reliable to ensure the server gets the message
	UFUNCTION(Server, Reliable)
	void ServerToggleReady();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing=OnRep_bIsReady)
	bool bIsReady{false};
	
	UPROPERTY(ReplicatedUsing=OnRep_CustomPlayerName)
	FString CustomPlayerName;
	
	UFUNCTION()
	void OnRep_CustomPlayerName();
	
	UFUNCTION()
	void OnRep_bIsReady();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
