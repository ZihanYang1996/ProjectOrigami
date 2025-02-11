#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleAudioCaptureBridge.h"
#include "MicrophoneTester.generated.h"



class UAudioCaptureComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMicrophoneVolumeUpdated, float, NewVolume);

UCLASS()
class PROJECTORIGAMI_API AMicrophoneTester : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMicrophoneTester();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentVolume{};

	UPROPERTY(BlueprintAssignable)
	FOnMicrophoneVolumeUpdated OnMicrophoneVolumeUpdated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;
};
