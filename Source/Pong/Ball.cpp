// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallSphereComponent = CreateDefaultSubobject<USphereComponent>("BallSphere");
	BallSphereComponent->SetSphereRadius(18);
	BallSphereComponent->SetCollisionProfileName("BlockAllDynamic");
	BallSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BallSphereComponent->SetNotifyRigidBodyCollision(true);
	BallSphereComponent->GetBodyInstance()->bLockRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockXRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockYRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockZRotation = true;
	BallSphereComponent->GetBodyInstance()->bLockXTranslation = true;
	SetRootComponent(BallSphereComponent);

	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ball Sprite Component"));
	BallSprite->SetupAttachment(BallSphereComponent);
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BallSprite->SetRelativeRotation(FQuat(FVector(0, 0, 1), 1.5708f));
	BallSprite->SetRelativeScale3D(FVector(.35f, 1.0f, .35f));



	BallMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BallMovement");
	BallMovement->bShouldBounce = true;
	BallMovement->bInterpMovement = true;
	BallMovement->bInitialVelocityInLocalSpace = true;
	BallMovement->InitialSpeed = 250;
	BallMovement->MaxSpeed = 5000;
	BallMovement->Bounciness = 1.4f;
	BallMovement->LimitVelocity(FVector(0.0f, 50000, 50000));
	BallMovement->Velocity = FVector(0, -1000, 400);
	BallMovement->ProjectileGravityScale = 0.0f;
	PreviousNormal = BallMovement->PreviousHitNormal;





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
	}

	HandleHorizontalAndVertical();
	SecureXAxis();
	CheckIfStuckAndFix();
	
}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(BallSphereComponent);
}


//------------------- My Clean Up Functions ---------------------------------------//

void ABall::ResetVelocity() //Name says it all
{
	//I dont want legit random starts because well chaos. 
	//Fully random starts leave to much to have change on every reset; Getting a different angle EVERYtime would be create unlimitted posibilities for error.
	//This shoots the ball into one of the 4 corners at a speed i like.
	//This speed is lower than the intial speed of the game because i found that after a goal i needed an extra second to refocus.
	//Might be a me thing might be a human brain thing 

	FVector VelocityOption1 = FVector(0.0f, -200, 80);
	FVector VelocityOption2 = FVector(0.0f, 200, 80);
	FVector VelocityOption3 = FVector(0.0f, 200, -80);
	FVector VelocityOption4 = FVector(0.0f, -200, -80);
	FMath MathFunctionality;
	int RandomInt = MathFunctionality.RandRange(1, 4);
	BallMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);
	if (RandomInt == 1)
		BallMovement->Velocity = VelocityOption1;
	if (RandomInt == 2)
		BallMovement->Velocity = VelocityOption2;
	if (RandomInt == 3)
		BallMovement->Velocity = VelocityOption3;
	if (RandomInt == 4)
		BallMovement->Velocity = VelocityOption4;

	
}

void ABall::CheckIfStuckAndFix()
//The ai likes the spuish the ball into the top and botom. 
//He likes to play catch more than pong lol. This should stop his habbit.
{
	if (TickToggle == false)
	{
		PreviousLocation = GetActorLocation();
		TickToggle = true;
	}
	else if (TickToggle == true)
	{
		if (PreviousLocation == GetActorLocation())
		{
			ResetVelocity();
			TeleportTo(MiddleOfField->GetActorLocation(), FRotator::ZeroRotator);
			BallMovement->AddForce(FVector(0.0f, 50.0f, 50.0f));
		}
		TickToggle = false;
	}
}

void ABall::HandleHorizontalAndVertical()
{
	//Triggers if the ball is starting to become horizontal or vertical.
	//top left is positive positive 
	//Should have done my own physics 

	if (PreviousNormal != BallMovement->PreviousHitNormal)
	{
		HitToggle = true;
		NormalOnHit = BallMovement->PreviousHitNormal;
	}
	if (HitToggle == true)
	{
		//New horizontal and vertical handling is a little long but it does not increase the velocity drastically like the other
		//The angles it fixes too are no longer as drastic either. Most bounces that get triggered here come out
		//as you would expect them. Some bounce a little odd but they are fringe cases. This works well for now.

		if (NormalOnHit.Y == -PreviousNormal.Y && PreviousNormal.Y != 0)//Horrizontal good
		{
			GEngine->AddOnScreenDebugMessage(8, 5.0f, FColor::Blue, FString::Printf(TEXT("Has Become Horizontal")));
			
			if (BallMovement->Velocity.Z >= 0)
			{
				if (BallMovement->Velocity.Y >= 0)
				{
					BallMovement->Velocity.Y -= 100;
				}
				else
				{
					BallMovement->Velocity.Y += 100;
				}
				BallMovement->Velocity.Z += 100.0f;
			}
			else if (BallMovement->Velocity.Z < 0)
			{
				if (BallMovement->Velocity.Y >= 0)
				{
					BallMovement->Velocity.Y -= 100;
				}
				else
				{
					BallMovement->Velocity.Y += 100;
				}
				BallMovement->Velocity.Z -= 100.0f;
			}
		}
		else if (NormalOnHit.Z == -PreviousNormal.Z && PreviousNormal.Z != 0)//Optimized but not perfect
		{
			GEngine->AddOnScreenDebugMessage(8, 5.0f, FColor::Red, FString::Printf(TEXT("Has Become Vertical")));
			
			if (BallMovement->Velocity.Y >= 0)
			{
				if (BallMovement->Velocity.Z >= 0)
				{
					BallMovement->Velocity.Z -= 100;
				}
				else
				{
					BallMovement->Velocity.Z += 100;
				}
				BallMovement->Velocity.Y += 100.0f;
			}
			else if (BallMovement->Velocity.Y < 0)
			{
				if (BallMovement->Velocity.Z >= 0)
				{
					BallMovement->Velocity.Z -= 100;
				}
				else
				{
					BallMovement->Velocity.Z += 100;
				}
				BallMovement->Velocity.Y -= 100.0f;
			}
			
			
			//This worked but added too much speed and only have allowed for 1 vertical bounce per exchange.
			//This was the old function;
			//if (BallMovement->Velocity.Y >= 0)
			//{
			//	BallMovement->Velocity.Z = 500.0f;
			//	BallMovement->Velocity.Y = 1000.0f;
			//}
			//else if (BallMovement->Velocity.Y < 0)
			//{
			//	BallMovement->Velocity.Z = -500.0f;
			//	BallMovement->Velocity.Y = -1000.0f;
			//}
		}
		HitToggle = false;
		PreviousNormal = BallMovement->PreviousHitNormal;
	}



}

void ABall::SecureXAxis()//Keeps the ball on the X axis so far works decent
{
	if (BallMovement->Velocity.X != 0.0f)
	{

		GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Red, FString::Printf(TEXT("Ball X axis is not aligned")));

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

