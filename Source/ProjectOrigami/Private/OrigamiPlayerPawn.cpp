// Fill out your copyright notice in the Description page of Project Settings.


#include "OrigamiPlayerPawn.h"

#include "BlowWindComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"

// Sets default values
AOrigamiPlayerPawn::AOrigamiPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Enable the pawn to rotate with the controller
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	BlowWindComponent = CreateDefaultSubobject<UBlowWindComponent>(TEXT("BlowWindComponent"));
}

// Called when the game starts or when spawned
void AOrigamiPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOrigamiPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AOrigamiPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AOrigamiPlayerPawn::Move(const FInputActionValue& Value, float MovementSpeed)
{
	// Get the movement vector from the input action value
	FVector2D MovementVector{Value.Get<FVector2D>()};
	// Calculate the delta location
	FVector DeltaLocation{GetActorForwardVector() * MovementVector.Y + GetActorRightVector() * MovementVector.X};
	// Get delta time to make the movement frame rate independent
	float DeltaTime{GetWorld()->GetDeltaSeconds()};
	// Move the pawn
	AddActorWorldOffset(DeltaLocation * MovementSpeed * DeltaTime, true);
}

void AOrigamiPlayerPawn::BlowWind(float WindStrength, FVector WindSourceLocation, FVector WindDirection)
{
	BlowWindComponent->ApplyWindForce(WindStrength, WindSourceLocation, WindDirection);
}
