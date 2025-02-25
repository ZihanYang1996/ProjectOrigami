// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerUI.h"

#include "OrigamiPlayerController.h"
#include "Components/Button.h"

void UPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (BlowWindButton)
	{
		BlowWindButton->OnPressed.AddDynamic(this, &UPlayerUI::StartBlowingWind);
		BlowWindButton->OnReleased.AddDynamic(this, &UPlayerUI::StopBlowingWind);
	}

	PlayerController = Cast<AOrigamiPlayerController>(GetOwningPlayer());
}

void UPlayerUI::StartBlowingWind()
{
	if (PlayerController)
	{
		PlayerController->StartBlowingWind();
	}
}

void UPlayerUI::StopBlowingWind()
{
	if (PlayerController)
	{
		PlayerController->StopBlowingWind();
	}
}
