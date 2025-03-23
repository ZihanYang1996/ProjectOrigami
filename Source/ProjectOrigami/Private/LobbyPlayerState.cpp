// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"

#include "LobbyGameState.h"
#include "Net/UnrealNetwork.h"

void ALobbyPlayerState::SetReadyState(bool bNewIsReady)
{
	if (HasAuthority())
	{
		bIsReady = bNewIsReady;
		OnRep_bIsReady(); // RepNotify function needs to be called manually on the server
		
		if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
		{
			GS->OnPlayerListChanged();  // Broadcast the player list changed event (for UI)
			GS->CheckAllPlayersReady();  // Check if all players are ready
		}
	}
}

void ALobbyPlayerState::ServerSetReadyState_Implementation(bool bNewIsReady)
{
	SetReadyState(bNewIsReady);
}


void ALobbyPlayerState::OnRep_bIsReady()
{
	// This will
	UE_LOG(LogTemp, Log, TEXT("%s is now %s!"), *GetPlayerName(), bIsReady ? TEXT("Ready") : TEXT("Not Ready"));
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, bIsReady);
}
