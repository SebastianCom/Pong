// Fill out your copyright notice in the Description page of Project Settings.


#include "AiPaddle.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AAiPaddle::AAiPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//AiBox Set up -> Player box is are root and our collision square. Ai sprite is our visual
	AiBoxComponent = CreateDefaultSubobject<UBoxComponent>("PlayerBox");
	AiBoxComponent->SetBoxExtent(FVector(10, 25, 50));
	AiBoxComponent->SetSimulatePhysics(true);
	AiBoxComponent->SetEnableGravity(false);
	AiBoxComponent->SetCollisionProfileName("BlockAllDynamic");
	AiBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AiBoxComponent->SetNotifyRigidBodyCollision(true);
	AiBoxComponent->SetLinearDamping(5);

	//Make sure it follows pong movement rules of only up and down
	AiBoxComponent->GetBodyInstance()->bLockRotation = true;
	AiBoxComponent->GetBodyInstance()->bLockXRotation = true;
	AiBoxComponent->GetBodyInstance()->bLockYRotation = true;
	AiBoxComponent->GetBodyInstance()->bLockZRotation = true;
	AiBoxComponent->GetBodyInstance()->bLockYTranslation = true;
	AiBoxComponent->GetBodyInstance()->bLockXTranslation = true;

	//Debugging ---------TURN OFF ON RELEASE--------
	AiBoxComponent->SetHiddenInGame(false);
	AiBoxComponent->SetVisibility(true);

	SetRootComponent(AiBoxComponent);

	AiSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ai Sprite Component"));
	AiSprite->SetupAttachment(AiBoxComponent);
	AiSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AiSprite->SetRelativeRotation(FQuat(FVector(0, 0, 1), 1.5708f));
	AiSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -2.0f));
	AiSprite->SetRelativeScale3D(FVector(5.0f, 4.0f, 4.0f));

}

// Called when the game starts or when spawned
void AAiPaddle::BeginPlay()
{
	Super::BeginPlay();
	CurrentPoint = BallPoint;
}

// Called every frame
void AAiPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CurrentPoint != nullptr)
	{
		//DECLARE a variable called Delta of type FVector, and Assign it to the result of:  GetActorLocation() - CurrentPatrolPoint->GetActorLocation()
		FVector Delta = GetActorLocation() - CurrentPoint->GetActorLocation();
		CurrentPoint = BallPoint;
		//CALL SetActorLocation() passing in : FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 600.f)
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPoint->GetActorLocation(), DeltaTime, 1000.f));
	}
}

// Called to bind functionality to input
void AAiPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

