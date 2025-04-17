// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTORIGAMI_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALobbyGameMode();

	// Called when everyone is ready
	UFUNCTION(BlueprintCallable)
	void StartGame();


	FString GameMapName{TEXT("/Game/Maps/DefaultMap")};
	FString TravelOption{TEXT("?listen")};

protected:
	virtual void BeginPlay() override;
};
