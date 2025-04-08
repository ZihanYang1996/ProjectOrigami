// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinLobbyWidget.h"

#include "LANLobbySubsystem.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"

void UJoinLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind the delegate that when the text changes in the EditableTextBox_ServerIP
	if (EditableTextBox_ServerIP)
	{
		EditableTextBox_ServerIP->OnTextChanged.AddDynamic(this, &UJoinLobbyWidget::OnServerIPChanged);
	}

	if (Button_JoinLobby)
	{
		Button_JoinLobby->OnClicked.AddDynamic(this, &UJoinLobbyWidget::JoinLobby);
	}
}


void UJoinLobbyWidget::JoinLobby()
{
	if (ULANLobbySubsystem* Subsystem{GetGameInstance()->GetSubsystem<ULANLobbySubsystem>()})
	{
		Subsystem->JoinLobby(CachedServerIP);
	}
}


void UJoinLobbyWidget::OnServerIPChanged(const FText& Text)
{
	// Handle the server IP change here
	UE_LOG(LogTemp, Log, TEXT("Server IP changed to: %s"), *Text.ToString());
	CachedServerIP = Text.ToString();
}