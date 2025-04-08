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
		// Print the lobby name to the screen for debugging purposes
		
		LobbyName = InLobbyName;
		
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Server: Setting lobby name to local IP address to ") + LobbyName);
		OnRep_LobbyName(); // Call the replication function manually, since we're on the server
	}
}

FString ALobbyGameState::GetLobbyName() const
{
	return LobbyName;
}

void ALobbyGameState::OnRep_LobbyName()
{
	// Can update the lobby UI here if needed in the future
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Lobby name replicated: ") + LobbyName);
	UE_LOG(LogTemp, Log, TEXT("Lobby name replicated: %s"), *LobbyName);
	OnLobbyNameChangedDelegate.Broadcast();
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, LobbyName);
}


// void ALobbyGameState::OnPlayerListChanged()
// {
// 	UE_LOG(LogTemp, Log, TEXT("LobbyGameState: Player list changed! Current players: %d"), PlayerArray.Num());
// 	OnPlayerListChangedDelegate.Broadcast();
// }
//
//
// void ALobbyGameState::CheckAllPlayersReady()
// {
// 	if (!HasAuthority())
// 	{
// 		return; // Only the server should check if all players are ready
// 	}
//
// 	// Check if all players are ready
// 	bool bAllPlayersReady = true;
// 	for (const APlayerState* PlayerState : PlayerArray)
// 	{
// 		const ALobbyPlayerState* LobbyPlayerState{Cast<ALobbyPlayerState>(PlayerState)};
// 		if (!LobbyPlayerState || !LobbyPlayerState->bIsReady)
// 		{
// 			bAllPlayersReady = false;
// 			break;
// 		}
// 	}
//
// 	if (bAllPlayersReady)
// 	{
// 		// Start the game
// 		UE_LOG(LogTemp, Log, TEXT("All players are ready! Starting game..."));
//
// 		if (ALobbyGameMode* GM{Cast<ALobbyGameMode>(AuthorityGameMode)})
// 		{
// 			GM->StartGame();
// 		}
// 	}
// }
