// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LANLobbySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API ULANLobbySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString LobbyName;  // For now we use the IP on the server as the lobby name

	UPROPERTY(EditAnywhere)
	FString LobbyMapName{TEXT("/Game/Maps/LobbyMenu")};

	UPROPERTY(EditAnywhere)
	FString TravelOption{TEXT("?listen")};

	UPROPERTY(BlueprintReadOnly)
	FString LocalPlayerName;
	
	UFUNCTION(BlueprintCallable)
	void HostLobby();

	UFUNCTION(BlueprintCallable)
	void JoinLobby(const FString& IPAddress, const FString& Port = TEXT("7777"));

	UFUNCTION(BlueprintCallable)
	void SetLocalPlayerName(const FString& Name);

	UFUNCTION(BlueprintCallable)
	FString GetLocalPlayerName() const;

	UFUNCTION(Server, Reliable)
	void ServerApplyPlayerName();
	

private:
	FString GetLocalIPAddress() const;
};
