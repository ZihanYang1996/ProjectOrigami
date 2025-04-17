// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"

#include "LANLobbySubsystem.h"
#include "LobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	// Set the player name to the local player's name
	APlayerController* PC{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
	if (IsOwnedBy(PC))
	{
		if (ULANLobbySubsystem* Subsystem{GetGameInstance()->GetSubsystem<ULANLobbySubsystem>()})
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
			                                 TEXT("LobbyPlayerState::BeginPlay | Subsystem Name: ") + Subsystem->
			                                 GetLocalPlayerName());
			SetCustomePlayerName(Subsystem->GetLocalPlayerName());
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("I own this player state!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("I do not own this player state!"));
	}
}

void ALobbyPlayerState::ToggleReady()
{
	if (HasAuthority())
	{
		bIsReady = !bIsReady;
		// Manually call the replication function
		OnRep_bIsReady();
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
		                                 TEXT("Server: Player ready status set to: ") + FString::Printf(
			                                 TEXT("%s"), bIsReady ? TEXT("Ready") : TEXT("Not Ready")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
		                                 TEXT("Client: Requesting to set player ready status to toggle"));
		ServerToggleReady();
	}
}


void ALobbyPlayerState::SetCustomePlayerName(const FString& NewName)
{
	if (HasAuthority())
	{
		CustomPlayerName = NewName;
		// Manually call the replication function
		OnRep_CustomPlayerName();

		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
		                                 TEXT("Server: Player name set to: ") + CustomPlayerName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
		                                 TEXT("Client: Requesting to set player name to ") + NewName);
		ServerSetCustomePlayerName(NewName);
	}
}

void ALobbyPlayerState::ServerToggleReady_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("Server: Server RPC invoked"));
		ToggleReady();
	}
}


void ALobbyPlayerState::ServerSetCustomePlayerName_Implementation(const FString& NewName)
{
	if (HasAuthority()) // To ensure the server is the one setting the name
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,TEXT("Server: Server RPC invoked)"));
		SetCustomePlayerName(NewName);
	}
}


void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, bIsReady);
	DOREPLIFETIME(ALobbyPlayerState, CustomPlayerName);
}

void ALobbyPlayerState::OnRep_bIsReady()
{
	// This will be automatically called on clients when bIsReady is updated
	// Notify the game state about the player list change
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChanged();
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange,
		                                 TEXT("Player ready status replicated: ") + FString::Printf(
			                                 TEXT("%s"), bIsReady ? TEXT("Ready") : TEXT("Not Ready")));
	}
}

void ALobbyPlayerState::OnRep_CustomPlayerName()
{
	// This will be automatically called on clients when CustomPlayerName is updated
	// Notify the game state about the player name change
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChanged();
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange,
		                                 TEXT("Player name replicated: ") + CustomPlayerName);
	}
}
