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

void ALobbyGameMode::StartGame()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Starting game..."));
		// Get the game state and set the lobby name to "Starting game..."
		if (ALobbyGameState* GameState{GetGameState<ALobbyGameState>()})
		{
			GameState->SetLobbyName(TEXT("Starting game..."));
		}
		
		// Start the game by server traveling to the game map
		GetWorld()->ServerTravel(GameMapName + TravelOption);
	}
}
