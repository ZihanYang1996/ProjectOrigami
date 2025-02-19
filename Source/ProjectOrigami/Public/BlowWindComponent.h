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

	// Define how far the wind can reach
	UPROPERTY(EditAnywhere)
	float WindDistance{1000.0f};

	// Define the radius of the wind (the radius of the sphere used for the line trace)
	UPROPERTY(EditAnywhere)
	float WindRadius{300.0f};
	
private:
	APlayerController* PlayerController;
};
