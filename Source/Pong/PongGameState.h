// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
public:

	APongGameState();

	UFUNCTION(BlueprintCallable, Category = "Goals")
		int GetNumberOfPlayerGoals();

	UFUNCTION(BlueprintCallable, Category = "Goals")
		int GetNumberOfAiGoals();
	
	UFUNCTION(BlueprintCallable, Category = "Goals")
		float GetStartTimer();

	int NumberOfPlayerGoals;
	int NumberOfAiGoals;
	float GSStartTimer;
};
