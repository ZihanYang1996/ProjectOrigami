// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinLobbyWidget.generated.h"

class UButton;
class UEditableTextBox;
class UListView;
/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UJoinLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void JoinLobby();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnServerIPChanged(const FText& Text);
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditableTextBox_ServerIP;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_JoinLobby;

	UPROPERTY()
	FString CachedServerIP;
};
