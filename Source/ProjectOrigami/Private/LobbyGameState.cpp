// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameState.h"

#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"

void ALobbyGameState::OnPlayerListChanged()
{
	UE_LOG(LogTemp, Log, TEXT("LobbyGameState: Player list changed! Current players: %d"), PlayerArray.Num());
	OnPlayerListChangedDelegate.Broadcast();
}


void ALobbyGameState::CheckAllPlayersReady()
{
	if (!HasAuthority())
	{
		return; // Only the server should check if all players are ready
	}

	// Check if all players are ready
	bool bAllPlayersReady = true;
	for (const APlayerState* PlayerState : PlayerArray)
	{
		const ALobbyPlayerState* LobbyPlayerState{Cast<ALobbyPlayerState>(PlayerState)};
		if (!LobbyPlayerState || !LobbyPlayerState->bIsReady)
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
