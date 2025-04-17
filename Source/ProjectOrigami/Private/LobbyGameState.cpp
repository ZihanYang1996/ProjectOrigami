// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameState.h"

#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

ALobbyGameState::ALobbyGameState()
{
	SetReplicates(true);
}

void ALobbyGameState::SetLobbyName(const FString& InLobbyName)
{
	if (HasAuthority())
	{
		LobbyName = InLobbyName;

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red,
		                                 TEXT("Server: Setting lobby name to local IP address to ") + LobbyName);
		OnRep_LobbyName(); // Call the replication function manually, since we're on the server
	}
}

FString ALobbyGameState::GetLobbyName() const
{
	return LobbyName;
}

void ALobbyGameState::OnRep_LobbyName()
{
	if (!HasAuthority())
	{
		// Print the lobby name on the client for debugging purposes
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Client: Lobby name replicated: ") + LobbyName);
	}
	// Update the UI or perform any other actions needed when the lobby name changes
	OnLobbyNameChangedDelegate.Broadcast();
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, LobbyName);
}


void ALobbyGameState::OnPlayerListChanged()
{
	UE_LOG(LogTemp, Log, TEXT("LobbyGameState: Player list changed! Current players: %d"), PlayerArray.Num());
	// Broadcast the player list changed event (mainly for UI updates)
	OnPlayerListChangedDelegate.Broadcast();

	// Check if all players are ready
	CheckAllPlayersReady();
}


void ALobbyGameState::CheckAllPlayersReady()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Checking if all players are ready..."));
	if (!HasAuthority())
	{
		return; // Only the server should check if all players are ready
	}

	// Check if all players are ready
	bool bAllPlayersReady = true;
	for (const APlayerState* PlayerState : PlayerArray)
	{
		const ALobbyPlayerState* LobbyPlayerState{Cast<ALobbyPlayerState>(PlayerState)};
		if (!LobbyPlayerState || !LobbyPlayerState->GetReadyState())
		{
			bAllPlayersReady = false;
			break;
		}
	}

	if (bAllPlayersReady)
	{
		// Start the game
		UE_LOG(LogTemp, Log, TEXT("All players are ready! Starting game..."));

		if (ALobbyGameMode* GM{Cast<ALobbyGameMode>(AuthorityGameMode)})
		{
			GM->StartGame();
		}
	}
}
