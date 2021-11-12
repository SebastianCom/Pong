// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallSphereComponent = CreateDefaultSubobject<USphereComponent>("BallSphere");
	BallSphereComponent->SetSphereRadius(18);

	//BallSphereComponent->SetSimulatePhysics(true);
	//BallSphereComponent->SetEnableGravity(false);
	BallSphereComponent->SetCollisionProfileName("BlockAllDynamic");
	BallSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BallSphereComponent->SetNotifyRigidBodyCollision(true);
	BallSphereComponent->GetBodyInstance()->bLockRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockXRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockYRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockZRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockXTranslation = true;
	BallSphereComponent->SetHiddenInGame(false);
	BallSphereComponent->SetVisibility(true);
	SetRootComponent(BallSphereComponent);

	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ball Sprite Component"));
	BallSprite->SetupAttachment(BallSphereComponent);
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallSprite->SetRelativeRotation(FQuat(FVector(0, 0, 1), 1.5708f));
	BallSprite->SetRelativeScale3D(FVector(.35f, 1.0f, .35f));



	BallMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BallMovement");
	BallMovement->bShouldBounce = true;
	BallMovement->bInterpMovement = true;
	//BallMovement->AddForce(FVector(0, 0, 0));
	BallMovement->bInitialVelocityInLocalSpace = true;
	BallMovement->InitialSpeed = 250;
	BallMovement->MaxSpeed = 5000;
	BallMovement->Bounciness = 1.35f;
	BallMovement->LimitVelocity(FVector(0.0f, 50000, 50000));
	BallMovement->Velocity = FVector(0, -1000, 400);
	BallMovement->ProjectileGravityScale = 0.0f;
	PreviousNormal = BallMovement->PreviousHitNormal;
	//BallMovement->BounceVelocityStopSimulatingThreshold = 1000.0f;
	//BallMovement->PhysicsLockedAxisSettingChanged();


	//BallMovement->SetUpdatedComponent(BallSphereComponent);





}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Purple, FString::Printf(TEXT("Ball Velocity: %f, %f"), BallMovement->Velocity.Y, BallMovement->Velocity.Z));
		GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Blue, FString::Printf(TEXT("Previous Nomral: %f, %f, %f"), BallMovement->PreviousHitNormal.X, BallMovement->PreviousHitNormal.Y, BallMovement->PreviousHitNormal.Z));
		//bool bInWorld = BallMovement->CheckStillInWorld();
		//GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red, bInWorld ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false")));
	}


	//Triggers if the ball is starting to become horizontal or vertical. Once rest of the game is set up come back here to add velocity to fix this;
	//top left is positive positive 
	//Should have rolled my own physics 
	if (PreviousNormal != BallMovement->PreviousHitNormal)
	{
		HitToggle = true;
		NormalOnHit = BallMovement->PreviousHitNormal;
	}
	if (HitToggle == true)
	{
		if (NormalOnHit.Y == -PreviousNormal.Y && PreviousNormal.Y != 0)//Horrizontal good
		{
			GEngine->AddOnScreenDebugMessage(8, 5.0f, FColor::Blue, FString::Printf(TEXT("Has Become Horizontal")));
			if (BallMovement->Velocity.Z >= 0)
			{
				BallMovement->Velocity.Z += 100.0f;
			}
			else if (BallMovement->Velocity.Z < 0)
			{
				BallMovement->Velocity.Z -= 100.0f;
			}
		}
		else if (NormalOnHit.Z == -PreviousNormal.Z && PreviousNormal.Z != 0)//Resets speed but works for now. allows for a completable game everytime and that is what matter right now
		{
			GEngine->AddOnScreenDebugMessage(8, 5.0f, FColor::Red, FString::Printf(TEXT("Has Become Vertical")));
			if (BallMovement->Velocity.Y >= 0)
			{
				BallMovement->Velocity.Z = 500.0f;
				BallMovement->Velocity.Y = 1000.0f;
			}
			else if (BallMovement->Velocity.Y < 0)
			{
				BallMovement->Velocity.Z = -500.0f;
				BallMovement->Velocity.Y = -1000.0f;
			}
		}
		HitToggle = false;
		PreviousNormal = BallMovement->PreviousHitNormal;
	}
	

	if (BallMovement->Velocity.X != 0.0f)
	{
		
		GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Red, FString::Printf(TEXT("Ball X axis is Fucked")));
		
		float y = BallMovement->Velocity.Y;
		float z = BallMovement->Velocity.Z;
		BallMovement->Velocity = FVector(0.0, y, z);
		float y2 = GetActorLocation().Y;
		float z2 = GetActorLocation().Z;
		SetActorLocation(FVector(0.0f, y2, z2), false, nullptr, ETeleportType::TeleportPhysics);
	}
	if (BallMovement->Velocity.X == 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Green, FString::Printf(TEXT("Ball X axis is Good")));
	}


}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(BallSphereComponent);
}

