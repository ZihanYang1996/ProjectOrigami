// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrigamiPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartBlowingWind();

	UFUNCTION()
	void StopBlowingWind();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* BlowWindButton;

	AOrigamiPlayerController* PlayerController;
};
