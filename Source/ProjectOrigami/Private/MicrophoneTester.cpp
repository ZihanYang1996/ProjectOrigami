// Fill out your copyright notice in the Description page of Project Settings.


#include "MicrophoneTester.h"


// Sets default values
AMicrophoneTester::AMicrophoneTester()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMicrophoneTester::BeginPlay()
{
	Super::BeginPlay();

	StartAudioCapture();
}

// Called every frame
void AMicrophoneTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentVolume = GetMicVolume();
	OnMicrophoneVolumeUpdated.Broadcast(CurrentVolume);
#
}

