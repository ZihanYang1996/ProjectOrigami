// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyUIWidget.h"

#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "Components/ListView.h"
#include "UI/PlayerListItemObject.h"

void ULobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the delegate for player list changes
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChangedDelegate.AddDynamic(this, &ULobbyUIWidget::OnPlayerListChanged);
	}

	RefreshPlayerList();
}

void ULobbyUIWidget::NativeDestruct()
{
	// Unbind the delegate for player list changes
	if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
	{
		GS->OnPlayerListChangedDelegate.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void ULobbyUIWidget::OnPlayerListChanged()
{
	RefreshPlayerList();
}

void ULobbyUIWidget::RefreshPlayerList()
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

	TArray<APlayerState*> Players{GS->GetPlayers()};

	for (APlayerState* PS : Players)
	{
		if (PS)
		{
			UPlayerListItemObject* PSWrapper{NewObject<UPlayerListItemObject>(this)};
			PSWrapper->PlayerState = PS;
			ListView_PlayerList->AddItem(PSWrapper);
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

	PS->ServerToggleReady();
	RefreshPlayerList();
}
