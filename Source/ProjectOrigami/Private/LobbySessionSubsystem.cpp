// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbySessionSubsystem.h"

#include "OnlineSessionSearchResultWrapper.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Online/OnlineSessionNames.h"

void ULobbySessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("Lobby Session Subsystem Initialized"));
}

void ULobbySessionSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UE_LOG(LogTemp, Log, TEXT("Lobby Session Subsystem Deinitialized"));

	// Optional: Clear any delegates if needed
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("Deinitialize"))};
	if (SessionInterface.IsValid())
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	}
}

void ULobbySessionSubsystem::CreateSession(int32 NumPublicConnections)
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("CreateSession"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Destroy the session if it already exists
	if (SessionInterface->GetNamedSession(NAME_GameSession))
	{
		UE_LOG(LogTemp, Log, TEXT("CreateSession: Existing session found, destroying it..."));
		DestroySession();
	}

	// Define session settings
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true; // LAN mode enabled
	SessionSettings.NumPublicConnections = NumPublicConnections; // Max players
	SessionSettings.bShouldAdvertise = true; // Advertise the session
	SessionSettings.bUsesPresence = false; // Not needed for LAN, it's for "invites" or "friends only" stuff
	SessionSettings.bAllowJoinInProgress = false; // Don't allow joining after the game has started

	// Bind delegate for session creation complete
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(
		this, &ULobbySessionSubsystem::OnCreateSessionComplete);
	OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
		OnCreateSessionCompleteDelegate);

	bool bSuccess{SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings)};

	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("CreateSession: Session creation successful!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CreateSession: Failed to create session!"));
	}
}

void ULobbySessionSubsystem::DestroySession()
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("DestroySession"))};

	if (!SessionInterface.IsValid())
	{
		return;
	}

	bool bSuccess = SessionInterface->DestroySession(NAME_GameSession);

	if (!bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("DestroySession: Failed to destroy session!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("DestroySession: Session destruction initiated."));
	}
}

void ULobbySessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnCreateSessionComplete: Session %s creation complete! Success: %s"),
	       *SessionName.ToString(), bWasSuccessful ? TEXT("tre") : TEXT("false"));

	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("OnCreateSessionComplete"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session successfully created! Broadcasting event."));
		OnSessionCreated.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session!"));
	}
}

void ULobbySessionSubsystem::FindSessions(int32 MaxSearchResults)
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("FindSessions"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Define session search settings (LAN search only)
	OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());
	OnlineSessionSearch->MaxSearchResults = MaxSearchResults;
	OnlineSessionSearch->bIsLanQuery = true; // LAN search

	UE_LOG(LogTemp, Log, TEXT("FindSessions: Starting session search..."));

	// Bind delegate for session search complete
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(
		this, &ULobbySessionSubsystem::OnFindSessionsComplete);
	OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
		OnFindSessionsCompleteDelegate);

	// Search for sessions
	// Use 0 for LAN, need to use *LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId() for online
	bool bSuccess{SessionInterface->FindSessions(0, OnlineSessionSearch.ToSharedRef())};

	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("FindSessions: Failed to start session search!"));
	}
}

void ULobbySessionSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("OnFindSessionsComplete"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Clear the delegate
	SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("OnFindSessionsComplete: Found %d sessions!"),
		       OnlineSessionSearch->SearchResults.Num());
		TArray<UOnlineSessionSearchResultWrapper*> SearchResults;
		for (const FOnlineSessionSearchResult& Result : OnlineSessionSearch->SearchResults)
		{
			UOnlineSessionSearchResultWrapper* Wrapper{NewObject<UOnlineSessionSearchResultWrapper>(this)};
			Wrapper->SearchResult = Result;
			SearchResults.Add(Wrapper);	
		}
		OnSessionFound.Broadcast(SearchResults);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete: Session search failed or returned no results."));
		OnSessionFound.Broadcast(TArray<UOnlineSessionSearchResultWrapper*>());
	}
}

void ULobbySessionSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionToJoin)
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("JoinSession"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Bind delegate for session join complete
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(
		this, &ULobbySessionSubsystem::OnJoinSessionComplete);
	OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
		OnJoinSessionCompleteDelegate);

	// Join the session
	// Use 0 for LAN, need to use *LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId() for online
	bool bSuccess{SessionInterface->JoinSession(0, NAME_GameSession, SessionToJoin)};

	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("JoinSession: Failed to join session!"));
	}
}


void ULobbySessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSessionPtr SessionInterface{GetSessionInterfaceHelper(TEXT("OnJoinSessionComplete"))};
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Clear the delegate
	SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

	FString ConnectInfo;
	if (SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectInfo))
	{
		UE_LOG(LogTemp, Log, TEXT("OnJoinSessionComplete: Connecting to %s"), *ConnectInfo);
		
		// Travel to the host level/map
		APlayerController* PlayerController{GetWorld()->GetFirstPlayerController()};
		if (PlayerController)
		{
			PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
		}
		// Broadcast event
		OnSessionJoined.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnJoinSessionComplete: Failed to join session %s!"), *SessionName.ToString());
	}
}



IOnlineSessionPtr ULobbySessionSubsystem::GetSessionInterfaceHelper(const FString& Context) const
{
	IOnlineSubsystem* OnlineSubsystem{Online::GetSubsystem(GetWorld())};

	if (!OnlineSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: OnlineSubsystem not found!"), *Context);
		return nullptr;
	}

	IOnlineSessionPtr SessionInterface{OnlineSubsystem->GetSessionInterface()};
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: SessionInterface not valid!"), *Context);
		return nullptr;
	}

	return SessionInterface;
}
