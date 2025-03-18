// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LobbySessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionCreatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionFoundSignature, const TArray<FOnlineSessionSearchResult>&, SessionResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionJoinedSignature);

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
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionToJoin);

private:
	// Callbacks
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// Subsystem State
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	// Store search results
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;

	IOnlineSessionPtr GetSessionInterfaceHelper(const FString& Context) const;

public:
	// Delegates for Blueprints
	UPROPERTY(BlueprintAssignable)
	FOnSessionCreatedSignature OnSessionCreated;

	UPROPERTY(BlueprintAssignable)
	FOnSessionFoundSignature OnSessionFound;

	UPROPERTY(BlueprintAssignable)
	FOnSessionJoinedSignature OnSessionJoined;
};
