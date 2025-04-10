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
	FString LobbyMapName{TEXT("/Game/Maps/LobbyMenu")};

	FString TravelOption{TEXT("?listen")};

	UPROPERTY(BlueprintReadOnly)
	FString LocalPlayerName;

	UFUNCTION(BlueprintCallable)
	void HostLobby();

	// Default the port to 7777, since Unreal Engine uses this port by default
	// If you want to host lobby on a different port, you can set it in the DefaultEngine.ini
	UFUNCTION(BlueprintCallable)
	void JoinLobby(const FString& IPAddress, const FString& Port = TEXT("7777"));

	UFUNCTION(BlueprintCallable)
	void SetLocalPlayerName(const FString& Name);

	UFUNCTION(BlueprintCallable)
	FString GetLocalPlayerName() const;

	UFUNCTION(BlueprintCallable)
	FString GetLobbyName() const { return LobbyName; }

private:
	FString GetLocalIPAddress() const;

	FString LobbyName; // For now we use the IP on the server as the lobby name
};
