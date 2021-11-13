// Fill out your copyright notice in the Description page of Project Settings.


#include "AiGoal.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Pong/Ball.h"
#include "Pong/PongGameModeBase.h"
#include "Pong/PongGameState.h"
#include "Pong/PongPlayerState.h"

// Sets default values
AAiGoal::AAiGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GoalBox = CreateDefaultSubobject<UBoxComponent>("GoalBox");
	GoalBox->SetBoxExtent(FVector(1, 20, 1000));
	GoalBox->SetSimulatePhysics(false);
	GoalBox->SetCollisionProfileName("OverlapAllDynamic");
	GoalBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GoalBox->OnComponentBeginOverlap.AddDynamic(this, &AAiGoal::BeginOverlap);
	GoalBox->OnComponentEndOverlap.AddDynamic(this, &AAiGoal::EndOverlap);

	SetRootComponent(GoalBox);

}

void AAiGoal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapping Actor = %s"), *OtherActor->GetName()));
		}

		//WEEK 7
		//ABall* ball = Cast<ABall>(OtherActor);
		if (OtherActor->IsA<ABall>())
		{
			//TODO reset ball velocity. May be better to make a function in ball
			OtherActor->TeleportTo(MiddleOfField->GetActorLocation(), FRotator::ZeroRotator);
			APongGameModeBase* gameMode = Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode());
			APongGameState* gameState = gameMode->GetGameState<APongGameState>();
			APongPlayerState* playerState = Cast<APongPlayerState>(gameState->PlayerArray[0]);

			playerState->NumberOfGoals++;
	
			if (goal == EGoal::AI)
				gameState->NumberOfPlayerGoals++;
			else
				gameState->NumberOfAiGoals++;

		}
	}
}

void AAiGoal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Ended"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%s has left the Trigger Volume"), *OtherActor->GetName()));
		}
	}
}

// Called when the game starts or when spawned
void AAiGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAiGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

