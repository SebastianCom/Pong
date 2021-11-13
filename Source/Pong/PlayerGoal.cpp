// Fill out your copyright notice in the Description page of Project Settings.

// ------------------ NOT USED IN END PRODUCT-------------------------------------------

#include "PlayerGoal.h"

// Sets default values
APlayerGoal::APlayerGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

