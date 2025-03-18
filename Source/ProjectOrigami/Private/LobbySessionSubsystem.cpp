// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbySessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"

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
	IOnlineSubsystem* OnlineSubsystem{Online::GetSubsystem(GetWorld())};

	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface{OnlineSubsystem->GetSessionInterface()};

		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		}
	}
}

void ULobbySessionSubsystem::CreateSession(int32 NumPublicConnections)
{
	IOnlineSubsystem* OnlineSubsystem{Online::GetSubsystem(GetWorld())};
	if (!OnlineSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateSession: Failed to get OnlineSubsystem!"));
		return;
	}

	IOnlineSessionPtr SessionInterface{OnlineSubsystem->GetSessionInterface()};
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("CreateSession: Failed to get SessionInterface!"));
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
	SessionSettings.bUsesPresence = false; // Not needed for LAN
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
	IOnlineSubsystem* Subsystem{Online::GetSubsystem(GetWorld())};

	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("DestroySession: OnlineSubsystem not found!"));
		return;
	}

	IOnlineSessionPtr SessionInterface{Subsystem->GetSessionInterface()};

	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("DestroySession: SessionInterface is not valid!"));
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

	IOnlineSubsystem* OnlineSubsystem{Online::GetSubsystem(GetWorld())};

	if (!OnlineSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("OnCreateSessionComplete: OnlineSubsystem not found!"));
		return;
	}

	IOnlineSessionPtr SessionInterface{OnlineSubsystem->GetSessionInterface()};
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("OnCreateSessionComplete: SessionInterface not valid!"));
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
