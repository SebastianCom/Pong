// Fill out your copyright notice in the Description page of Project Settings.

// ------------------ NOT USED IN END PRODUCT-------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

UCLASS()
class PONG_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

	UPROPERTY(VisibleAnywhere, Category = "Game Camera")
		class UCameraComponent* GameCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
