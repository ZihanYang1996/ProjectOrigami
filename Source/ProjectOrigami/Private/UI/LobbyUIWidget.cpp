// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUIWidget.h"

#include "LANLobbySubsystem.h"
#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "UI/PlayerListItemObject.h"

void ULobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the delegate for lobby name changes
	if (ALobbyGameState* GameState{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GameState->OnLobbyNameChangedDelegate.AddDynamic(this, &ULobbyUIWidget::OnLobbyNameChanged);
	}
	
	// Bind the delegate for player list changes
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChangedDelegate.AddDynamic(this, &ULobbyUIWidget::OnPlayerListChanged);
	}

	// Bind the button click event
	if (Button_Ready)
	{
		Button_Ready->OnClicked.AddDynamic(this, &ULobbyUIWidget::OnReadyClicked);
	}
}

void ULobbyUIWidget::NativeDestruct()
{
	// Unbind the delegate for player list changes
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChangedDelegate.RemoveDynamic(this, &ULobbyUIWidget::OnPlayerListChanged);
	}

	Super::NativeDestruct();
}

void ULobbyUIWidget::OnLobbyNameChanged()
{
	// Set the lobby name text block
	if (TextBlock_LobbyName)
	{
		if (ALobbyGameState* LobbyGameState{GetWorld()->GetGameState<ALobbyGameState>()})
		{
			TextBlock_LobbyName->SetText(FText::FromString(LobbyGameState->GetLobbyName()));
			// Print the lobby name to the screen for debugging purposes
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue,
			                                 TEXT("Lobby Name getted: ") + LobbyGameState->GetLobbyName());
		}
	}
}

void ULobbyUIWidget::OnPlayerListChanged()
{
	// Check if the ListView is valid
	if (!ListView_PlayerList)
	{
		return;
	}

	// Clear the list first
	ListView_PlayerList->ClearListItems();

	// Get the game state
	ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()};
	if (!GS)
	{
		return;
	}

	TArray<APlayerState*> Players{GS->PlayerArray};

	for (APlayerState* PS : Players)
	{
		if (ALobbyPlayerState* LobbyPS{Cast<ALobbyPlayerState>(PS)})
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, 
			                                 TEXT("Player Name: ") + LobbyPS->GetCustomPlayerName());
			UPlayerListItemObject* Item{NewObject<UPlayerListItemObject>(this)};
			Item->Init(LobbyPS->GetCustomPlayerName(), LobbyPS->GetReadyState());
			ListView_PlayerList->AddItem(Item);
		}
	}
}


void ULobbyUIWidget::OnReadyClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Ready button clicked"));
	
	// Get the player controller of the owning player (local player)
	APlayerController* PC{GetOwningPlayer()};
	if (!PC)
	{
		return;
	}

	ALobbyPlayerState* PS{PC->GetPlayerState<ALobbyPlayerState>()};

	if (!PS)
	{
		return;
	}

	PS->ToggleReady();
}
