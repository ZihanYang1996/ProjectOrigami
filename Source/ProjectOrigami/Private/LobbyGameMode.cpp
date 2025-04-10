// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "LANLobbySubsystem.h"
#include "LobbyGameState.h"
#include "LobbyPlayerState.h"

ALobbyGameMode::ALobbyGameMode()
{
	// Set the default pawn class to the player pawn
	GameStateClass = ALobbyGameState::StaticClass();
	PlayerStateClass = ALobbyPlayerState::StaticClass();
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Set the lobby name on the game state (replicated) from the subsystem (persistent)
	if (ULANLobbySubsystem* Subsystem{GetGameInstance()->GetSubsystem<ULANLobbySubsystem>()})
	{
		if (ALobbyGameState* GameState{GetGameState<ALobbyGameState>()})
		{
			GameState->SetLobbyName(Subsystem->GetLobbyName());
		}
	}
}


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// int32 NumPlayers{GameState->PlayerArray.Num()};
	// UE_LOG(LogTemp, Log, TEXT("Player Joined! Current Players: %d"), NumPlayers);

	// Broadcast the player list changed event
	// if (ALobbyGameState* GS{GetGameState<ALobbyGameState>()})
	// {
	// 	GS->OnPlayerListChanged();
	// }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// int32 NumPlayers{GameState->PlayerArray.Num()};
	// UE_LOG(LogTemp, Log, TEXT("Player Left! Current Players: %d"), NumPlayers);

	// Broadcast the player list changed event
	// if (ALobbyGameState* GS{GetGameState<ALobbyGameState>()})
	// {
	// 	GS->OnPlayerListChanged();
	// }
}

void ALobbyGameMode::StartGame()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Starting game..."));
		GetWorld()->ServerTravel("/Game/Maps/DefaultMap?listen");
	}
}
