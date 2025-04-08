// Fill out your copyright notice in the Description page of Project Settings.


#include "LANLobbySubsystem.h"

#include "LobbyGameState.h"
#include "LobbyPlayerState.h"
#include "SocketSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ULANLobbySubsystem::HostLobby()
{
	UWorld* World{GetWorld()};
	if (World)
	{
		// Get the local IP address and set it as the lobby name on this subsystem so it's persistent
		LobbyName = GetLocalIPAddress();

		// ServerTravel to the lobby map
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hosting LAN Lobby!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Lobby Name: ") + LobbyName);
		World->ServerTravel(LobbyMapName + TravelOption);
	}
}

void ULANLobbySubsystem::JoinLobby(const FString& IPAddress, const FString& Port)
{
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
	if (PlayerController)
	{
		FString FullAddress{IPAddress + ":" + Port};
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Joining LAN Lobby!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Full Address: ") + FullAddress);

		PlayerController->ClientTravel(FullAddress, ETravelType::TRAVEL_Absolute);
	}
}

FString ULANLobbySubsystem::GetLocalIPAddress() const
{
	// Get the local IP address
	bool bCanBindAll{false};
	TSharedRef<FInternetAddr> Addr{
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll)
	};

	if (Addr->IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("Local IP Address: ") + Addr->ToString(false));
		return Addr->ToString(false);
	}
	return FString(TEXT("Unknown"));
}

void ULANLobbySubsystem::SetLocalPlayerName(const FString& Name)
{
	LocalPlayerName = Name;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Local Player Name set to: ") + LocalPlayerName);
}

FString ULANLobbySubsystem::GetLocalPlayerName() const
{
	return LocalPlayerName;
}

void ULANLobbySubsystem::ServerApplyPlayerName_Implementation()
{
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
	if (PlayerController)
	{
		ALobbyPlayerState* PlayerState{PlayerController->GetPlayerState<ALobbyPlayerState>()};
		if (PlayerState)
		{
			PlayerState->SetPlayerName(LocalPlayerName);
		}
	}
}
