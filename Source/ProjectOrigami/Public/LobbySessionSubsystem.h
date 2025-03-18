// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LobbySessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionCreatedSignature);

UCLASS()
class PROJECTORIGAMI_API ULobbySessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Lifecycle
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Session management
	void CreateSession(int32 NumPublicConnections);
	void DestroySession();

private:
	// Callbacks
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	// Subsystem State
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

public:
	// Delegates for Blueprints
	UPROPERTY(BlueprintAssignable)
	FOnSessionCreatedSignature OnSessionCreated;
};
