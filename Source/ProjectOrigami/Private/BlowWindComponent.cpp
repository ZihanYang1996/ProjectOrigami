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
void UBlowWindComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
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

	// Prepare for the line trace
	FVector TraceEnd{WindSourceLocation + WindDirection * WindDistance};

	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape{FCollisionShape::MakeSphere(WindRadius)};

	// Perform the line trace, the ECC_GameTraceChannel1 is a custom trace channel: WindTrace
	bool bHit{
		// TODO: Maybe will change to sweep single
		GetWorld()->SweepMultiByChannel(HitResults, WindSourceLocation, TraceEnd, FQuat::Identity,
		                                ECollisionChannel::ECC_GameTraceChannel1, CollisionShape)
	};

	// Early return if no hit
	if (!bHit)
	{
		return;
	}

	for (const FHitResult& Hit : HitResults)
	{
		// Draw the debug sphere at the hit impact point
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, WindRadius, 12, FColor::Red, false, 5.f);

		UPrimitiveComponent* HitComponent{Hit.GetComponent()};
		if (HitComponent && HitComponent->IsSimulatingPhysics())
		{
			// Calculate the distance from the wind source to the hit component
			double Distance{FVector::Dist(WindSourceLocation, Hit.ImpactPoint)};
			// Apply Inverse Square Falloff to the wind strength
			double DistanceFactor{1.0f / (1.0f + Distance * Distance * WindFalloffIntensity)};
			double FinalWindStrength{WindStrength * WindStrengthMultiplier * DistanceFactor};
			// Apply the wind force to the hit component
			// TODO: May combine both AddForce and AddForceAtLocation to get better results
			// HitComponent->AddForce(WindDirection * FinalWindStrength);
			HitComponent->AddForceAtLocation(WindDirection * FinalWindStrength, Hit.ImpactPoint);
			if (GEngine)
			{
				// Print "Pusing Object" to the screen
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				                                 FString::Printf(
					                                 TEXT("Pushing Object with force: %f"), FinalWindStrength));
			}
		}
	}
}
