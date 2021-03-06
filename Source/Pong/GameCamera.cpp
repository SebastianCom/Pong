// Fill out your copyright notice in the Description page of Project Settings.

// ------------------ NOT USED IN END PRODUCT-------------------------------------------

#include "GameCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GameCamera = CreateDefaultSubobject<UCameraComponent>("GameCamera");
	GameCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	GameCamera->SetOrthoWidth(5000.0f);
	GameCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

