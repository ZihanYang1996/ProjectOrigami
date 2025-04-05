// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WelcomeMenuWidget.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UWelcomeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerNameChanged(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void OnCreateLobbyClicked();

	UFUNCTION(BlueprintCallable)
	void OnJoinLobbyClicked();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditableTextBox_PlayerName;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CreateLobby;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_JoinLobby;

	FString CachedPlayerName;
	
};
