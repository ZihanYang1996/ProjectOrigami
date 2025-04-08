// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WelcomeMenuWidget.h"

#include "LANLobbySubsystem.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI/JoinLobbyWidget.h"

void UWelcomeMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_PlayerName)
	{
		EditableTextBox_PlayerName->OnTextChanged.AddDynamic(this, &UWelcomeMenuWidget::OnPlayerNameChanged);
	}

	if (Button_CreateLobby)
	{
		Button_CreateLobby->OnClicked.AddDynamic(this, &UWelcomeMenuWidget::OnCreateLobbyClicked);
	}
	
	if (Button_JoinLobby)
	{
		Button_JoinLobby->OnClicked.AddDynamic(this, &UWelcomeMenuWidget::OnJoinLobbyClicked);
	}
}

void UWelcomeMenuWidget::OnPlayerNameChanged(const FText& Text)
{
	CachedPlayerName = Text.ToString();
}

void UWelcomeMenuWidget::OnCreateLobbyClicked()
{
	if (ULANLobbySubsystem* Subsystem = GetGameInstance()->GetSubsystem<ULANLobbySubsystem>())
	{
		Subsystem->SetLocalPlayerName(CachedPlayerName);
		Subsystem->HostLobby(); // will also server travel

		// Below is the code for testing purposes
		// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hosting LAN Game");
		// UE_LOG(LogTemp, Warning, TEXT("Hosting LAN Game"));
		// // Implement the logic to host a LAN game
		// GetWorld()->ServerTravel("/Game/Maps/LobbyMenu?listen");
	}
}
// Handles only the part of setting the player name, the UI will be handled by Blueprint
void UWelcomeMenuWidget::OnJoinLobbyClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Join Lobby clicked!"));	
	if (ULANLobbySubsystem* Subsystem = GetGameInstance()->GetSubsystem<ULANLobbySubsystem>())
	{
		Subsystem->SetLocalPlayerName(CachedPlayerName);
	}

	// Below is the code for testing purposes
	// APlayerController* PC{GetGameInstance()->GetFirstLocalPlayerController()};
	// if (PC)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Joining LAN Game!!!!");
	// 	UE_LOG(LogTemp, Warning, TEXT("Joining LAN Game"));
	// 	PC->ClientTravel("192.168.2.65", ETravelType::TRAVEL_Absolute);
	// }
}