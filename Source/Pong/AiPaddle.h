// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AiPaddle.generated.h"

UCLASS()
class PONG_API AAiPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAiPaddle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AiBoxComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AI")
		class UPaperSpriteComponent* AiSprite;

	UPROPERTY(EditInstanceOnly, Category = "AI")
		AActor* BallPoint;
	
	// The current point the actor is either moving to or standing at
	AActor* CurrentPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
