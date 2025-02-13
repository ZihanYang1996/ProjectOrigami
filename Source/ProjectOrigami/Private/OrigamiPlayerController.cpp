// Fill out your copyright notice in the Description page of Project Settings.


#include "OrigamiPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OrigamiPlayerPawn.h"

void AOrigamiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CurrentControlledPawn = GetPawn();
}

void AOrigamiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if the Enhanced Input Local Player Subsystem is available and add the input mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// Check if the Input Component is of type Enhanced Input Component and bind actions to it
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the Move action to the Move function
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AOrigamiPlayerController::Move);

		// Bind the Look action to the Look function
		EnhancedInputComponent->BindAction(IA_Loook, ETriggerEvent::Triggered, this, &AOrigamiPlayerController::Look);
	}
}

void AOrigamiPlayerController::Move(const FInputActionValue& Value)
{
	if (AOrigamiPlayerPawn* ControlledPawn = Cast<AOrigamiPlayerPawn>(CurrentControlledPawn))
	{
		// Move the pawn
		ControlledPawn->Move(Value, MovementSpeed);
	}
}

void AOrigamiPlayerController::Look(const FInputActionValue& Value)
{
	if (AOrigamiPlayerPawn* ControlledPawn = Cast<AOrigamiPlayerPawn>(CurrentControlledPawn))
	{
		// Look around
		FVector2D LookInput{ Value.Get<FVector2D>() };
		AddYawInput(LookInput.X * LookSpeedX);
		AddPitchInput(LookInput.Y * LookSpeedY);
	}
}
