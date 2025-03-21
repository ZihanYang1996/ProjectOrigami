// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"

#include "Net/UnrealNetwork.h"

void ALobbyPlayerState::SetReadyState(bool bNewIsReady)
{
	if (HasAuthority())
	{
		bIsReady = bNewIsReady;
		OnRep_bIsReady();  // RepNotify function needs to be called manually on the server
	}
}

void ALobbyPlayerState::OnRep_bIsReady()
{
	
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, bIsReady);
}