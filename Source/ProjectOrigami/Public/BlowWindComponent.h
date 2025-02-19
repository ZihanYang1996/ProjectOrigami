// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlowWindComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTORIGAMI_API UBlowWindComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlowWindComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyWindForce(float WindStrength, FVector WindSourceLocation, FVector WindDirection);

	// Define how far the wind can reach (To be tuned)
	UPROPERTY(EditAnywhere, Category="Wind")
	float WindDistance{1000.0f};

	// Define the radius of the wind (the radius of the sphere used for the line trace) (To be tuned)
	UPROPERTY(EditAnywhere, Category="Wind")
	float WindRadius{300.0f};

	// Define the wind strength multiplier (To be tuned)
	UPROPERTY(EditAnywhere, Category="Wind")
	float WindStrengthMultiplier{5000.0f};
	
	// Define the wind falloff intensity multiplier (To be tuned)
	UPROPERTY(EditAnywhere, Category="Wind")
	float WindFalloffIntensity{0.0001f};
	
private:
	APlayerController* PlayerController;
};
