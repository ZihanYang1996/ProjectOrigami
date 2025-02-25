// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AppleAudioCaptureBridge.h"
#include "OrigamiPlayerController.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API AOrigamiPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* IA_Loook;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed{500.0f};

	UPROPERTY(EditAnywhere, Category="Movement")
	float LookSpeedX{50.0f};

	UPROPERTY(EditAnywhere, Category="Movement")
	float LookSpeedY{25.0f};

public:
	AOrigamiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	APawn* CurrentControlledPawn;

	bool bCanBlowWind{false};

public:
	UFUNCTION()
	void BlowWind();

	void StartBlowingWind();

	void StopBlowingWind();
};
