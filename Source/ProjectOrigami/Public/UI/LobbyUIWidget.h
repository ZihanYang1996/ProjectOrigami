// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUIWidget.generated.h"

class UTextBlock;
class UListView;
/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API ULobbyUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Called when Ready button is clicked
	// UFUNCTION(BlueprintCallable)
	// void OnReadyClicked();

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_LobbyName;
	
	UPROPERTY(meta = (BindWidget))
	UListView* ListView_PlayerList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerEntryClass;

	UFUNCTION()
	void OnLobbyNameChanged();
public:
	// void OnPlayerListChanged();
	// void RefreshPlayerList();
};
