// Fill out your copyright notice in the Description page of Project Settings.


#include "TopBox.h"
#include "Components/BoxComponent.h"


// Sets default values
ATopBox::ATopBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TopBoxComponent = CreateDefaultSubobject<UBoxComponent>("TopBox");
	TopBoxComponent->SetBoxExtent(FVector(1, 1500, 20));
	TopBoxComponent->SetCollisionProfileName("BLockAllDynamic");
	TopBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TopBoxComponent->SetNotifyRigidBodyCollision(true);
	TopBoxComponent->SetHiddenInGame(false);
	TopBoxComponent->SetVisibility(true);
	SetRootComponent(TopBoxComponent);



}

// Called when the game starts or when spawned
void ATopBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

