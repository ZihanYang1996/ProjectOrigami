// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUIWidget.h"

#include "LANLobbySubsystem.h"
#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "UI/PlayerListItemObject.h"

void ULobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ALobbyGameState* GameState{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GameState->OnLobbyNameChangedDelegate.AddDynamic(this, &ULobbyUIWidget::OnLobbyNameChanged);
		OnLobbyNameChanged(); // Call it once to set the initial value
	}
		
	
	// Bind the delegate for player list changes
	// if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	// {
	// 	GS->OnPlayerListChangedDelegate.AddDynamic(this, &ULobbyUIWidget::OnPlayerListChanged);
	// }
	//
	// RefreshPlayerList();
}

void ULobbyUIWidget::NativeDestruct()
{
	// Unbind the delegate for player list changes
	// if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	// {
	// 	GS->OnPlayerListChangedDelegate.RemoveAll(this);
	// }

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
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Lobby Name getted: ") + LobbyGameState->GetLobbyName());
		}
	}
}

// void ULobbyUIWidget::OnPlayerListChanged()
// {
// 	RefreshPlayerList();
// }
//
// void ULobbyUIWidget::RefreshPlayerList()
// {
// 	// Check if the ListView is valid
// 	if (!ListView_PlayerList)
// 	{
// 		return;
// 	}
//
// 	// Clear the list first
// 	ListView_PlayerList->ClearListItems();
//
// 	// Get the game state
// 	ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()};
// 	if (!GS)
// 	{
// 		return;
// 	}
//
// 	TArray<APlayerState*> Players{GS->GetPlayers()};
//
// 	for (APlayerState* PS : Players)
// 	{
// 		if (PS)
// 		{
// 			UPlayerListItemObject* PSWrapper{NewObject<UPlayerListItemObject>(this)};
// 			PSWrapper->PlayerState = PS;
// 			ListView_PlayerList->AddItem(PSWrapper);
// 		}
// 	}
// }
//
// void ULobbyUIWidget::OnReadyClicked()
// {
// 	UE_LOG(LogTemp, Log, TEXT("Ready button clicked"));
// 	
// 	// Get the player controller of the owning player (local player)
// 	APlayerController* PC{GetOwningPlayer()};
// 	if (!PC)
// 	{
// 		return;
// 	}
//
// 	ALobbyPlayerState* PS{PC->GetPlayerState<ALobbyPlayerState>()};
//
// 	if (!PS)
// 	{
// 		return;
// 	}
//
// 	PS->ServerToggleReady();
// 	RefreshPlayerList();
// }
