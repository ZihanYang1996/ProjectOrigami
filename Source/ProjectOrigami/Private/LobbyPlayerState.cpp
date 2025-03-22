// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"

#include "Net/UnrealNetwork.h"

void ALobbyPlayerState::SetReadyState(bool bNewIsReady)
{
	if (HasAuthority())
	{
		bIsReady = bNewIsReady;
		OnRep_bIsReady(); // RepNotify function needs to be called manually on the server
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
