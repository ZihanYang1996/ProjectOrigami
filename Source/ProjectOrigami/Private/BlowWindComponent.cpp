// Fill out your copyright notice in the Description page of Project Settings.


#include "BlowWindComponent.h"

// Sets default values for this component's properties
UBlowWindComponent::UBlowWindComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlowWindComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlowWindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBlowWindComponent::ApplyWindForce(float WindStrength, FVector WindSourceLocation, FVector WindDirection)
{
	if (GEngine)
	{
		// Print the wind strength and direction to the screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
										 FString::Printf(
											 TEXT("Wind Strength: %f; Wind Source Location: %s; Wind Direction %s"),
											 WindStrength, *WindSourceLocation.ToString(), *WindDirection.ToString()));
	}	
}

