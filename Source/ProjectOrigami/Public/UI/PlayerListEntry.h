// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListEntry.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UPlayerListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_ReadyStatus;
};
