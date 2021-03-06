// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BallSphereComponent;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Custom")
		class UPaperSpriteComponent* BallSprite;

	UPROPERTY(VisibleAnywhere, Category = "Game Camera")
		class UProjectileMovementComponent* BallMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)
		AActor* MiddleOfField;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class UPrimitiveComponent* GetPhysicsComponent();

	void ResetVelocity();
	void CheckIfStuckAndFix();
	void HandleHorizontalAndVertical();
	void SecureXAxis();

private:
	
	bool HitToggle = false;
	FVector PreviousNormal = (FVector(0.0f,0.0f,0.0f));
	FVector NormalOnHit = (FVector(0.0f,0.0f,0.0f));
	FVector PreviousLocation = (FVector(0.0f, 0.0f, 0.0f));
	bool TickToggle = false;
	float StartTimer = 3.0f;
	bool Started = false;
};
