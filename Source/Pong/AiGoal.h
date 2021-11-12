// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiGoal.generated.h"

UENUM(BlueprintType)
enum class EGoal : uint8 {
	Player = 0  UMETA(DisplayName = "LEFT"),
	AI = 1 UMETA(DisplayName = "RIGHT")
};



UCLASS()
class PONG_API AAiGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiGoal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UBoxComponent* GoalBox;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)
		TEnumAsByte<EGoal> goal;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)
		AActor* MiddleOfField;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
