// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"

#include "LANLobbySubsystem.h"
#include "LobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// void ALobbyPlayerState::SetReadyState(bool bNewIsReady)
// {
// 	if (HasAuthority())
// 	{
// 		bIsReady = bNewIsReady;
// 		OnRep_bIsReady(); // RepNotify function needs to be called manually on the server
// 		
// 		if (ALobbyGameState* GS{GetWorld()->GetGameState<ALobbyGameState>()})
// 		{
// 			GS->OnPlayerListChanged();  // Broadcast the player list changed event (for UI)
// 			GS->CheckAllPlayersReady();  // Check if all players are ready
// 		}
// 	}
// }
//
// void ALobbyPlayerState::ServerToggleReady_Implementation()
// {
// 	SetReadyState(!bIsReady);
// }
//
// void ALobbyPlayerState::SetPlayerName(const FString& NewName)
// {
// 	if (HasAuthority())
// 	{
// 		PlayerName = NewName;
// 	}
// }
//
// void ALobbyPlayerState::OnRep_bIsReady()
// {
// 	// This will
// 	UE_LOG(LogTemp, Log, TEXT("%s is now %s!"), *GetPlayerName(), bIsReady ? TEXT("Ready") : TEXT("Not Ready"));
// }
//

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	// Set the player name to the local player's name
	APlayerController* PC{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
	if (IsOwnedBy(PC))
	{
		if (ULANLobbySubsystem* Subsystem{GetGameInstance()->GetSubsystem<ULANLobbySubsystem>()})
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,
											 TEXT("LobbyPlayerState::BeginPlay | Subsystem Name: ") + Subsystem->GetLocalPlayerName());
			SetPlayerName(Subsystem->GetLocalPlayerName());
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("I own this player state!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("I do not own this player state!"));
	}

}


void ALobbyPlayerState::SetPlayerName(const FString& NewName)
{
	if (HasAuthority())
	{
		PlayerName = NewName;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,TEXT("Server: Player name set to: ") + PlayerName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,TEXT("Client: Requesting to set player name to ") + NewName);
		ServerSetPlayerName(NewName);
	}
}


void ALobbyPlayerState::ServerSetPlayerName_Implementation(const FString& NewName)
{
	if (HasAuthority()) // To ensure the server is the one setting the name
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green,TEXT("Server: Server RPC invoked)"));
		SetPlayerName(NewName);
	}
}


void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, PlayerName);
}