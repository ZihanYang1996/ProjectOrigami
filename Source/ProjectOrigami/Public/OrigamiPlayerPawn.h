// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrigamiPlayerPawn.generated.h"

class UCameraComponent;
struct FInputActionValue;

UCLASS()
class PROJECTORIGAMI_API AOrigamiPlayerPawn : public APawn
{
	GENERATED_BODY()


	UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	AOrigamiPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Move(const FInputActionValue& Value, float MovementSpeed);
};
