// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerListEntry.h"

#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "UI/PlayerListItemObject.h"

void UPlayerListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UPlayerListItemObject* Data = Cast<UPlayerListItemObject>(ListItemObject);
	
	// Check if the data is valid and has a valid player state
	if (!Data)
	{
		return;
	}
	
	// Set the player name
	if (TextBlock_PlayerName)
	{
		TextBlock_PlayerName->SetText(FText::FromString(Data->PlayerName));
	}
	
	// Set the ready status
	if (TextBlock_ReadyStatus)
	{
		TextBlock_ReadyStatus->SetText(Data->bIsReady ? FText::FromString(TEXT("Ready")) : FText::FromString(TEXT("Not Ready")));
	}
	
}
