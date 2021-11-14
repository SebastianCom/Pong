// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"



// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//PlayerBox Set up -> Player box is are root and our collision square. Player sprite is our visual
	PlayerBoxComponent = CreateDefaultSubobject<UBoxComponent>("PlayerBox");
	PlayerBoxComponent->SetBoxExtent(FVector(10, 25, 50));
	PlayerBoxComponent->SetSimulatePhysics(true);
	PlayerBoxComponent->SetEnableGravity(false);
	PlayerBoxComponent->SetCollisionProfileName("BlockAllDynamic");
	PlayerBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerBoxComponent->SetNotifyRigidBodyCollision(true);
	PlayerBoxComponent->SetLinearDamping(5);

	//Make sure it follows pong movement rules of only up and down
	PlayerBoxComponent->GetBodyInstance()->bLockRotation = true;
	PlayerBoxComponent->GetBodyInstance()->bLockXRotation = true;
	PlayerBoxComponent->GetBodyInstance()->bLockYRotation = true;
	PlayerBoxComponent->GetBodyInstance()->bLockZRotation = true;
	PlayerBoxComponent->GetBodyInstance()->bLockYTranslation = true;
	PlayerBoxComponent->GetBodyInstance()->bLockXTranslation = true;
	
	//Debugging ---------TURN OFF ON RELEASE--------
	//PlayerBoxComponent->SetHiddenInGame(false);
	//PlayerBoxComponent->SetVisibility(true);
	
	SetRootComponent(PlayerBoxComponent);

	//Spring Arm Set up - This is what keeps the camera still
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Attachment Arm");
	SpringArm->SetupAttachment(PlayerBoxComponent);
	SpringArm->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f));
	SpringArm->SetAbsolute(true, true, true);
	SpringArm->bIsCameraFixed = true;

	//Camera Set up - how we see the game
	GameCamera = CreateDefaultSubobject<UCameraComponent>("GameCamera");
	GameCamera->SetupAttachment(SpringArm);
	GameCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	GameCamera->SetOrthoWidth(2500.0f);
	GameCamera->bUsePawnControlRotation = false;

	//The visual for our box - a nice shade of aqua that constrasts the enemies color for both main types of color blindness (Colors have bee proofed)
	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	PlayerSprite->SetupAttachment(PlayerBoxComponent);
	PlayerSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayerSprite->SetRelativeRotation(FQuat(FVector(0,0,1), 1.5708f));
	PlayerSprite->SetRelativeLocation(FVector(0.0f, 0.0f, -2.0f));
	PlayerSprite->SetRelativeScale3D(FVector(5.0f, 4.0f, 4.0f));

	//Posses the player 
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	////Unused but worked - Made my own mesh and mat. Honestly ive been so busy my brain is a mess and i did not even consider making a simple sprite until today
	//PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	//UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Cube"));
	//PlayerMesh->SetStaticMesh(Cube);
	//PlayerMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/BasicShapeMaterial"));
	//PlayerMesh->SetMaterial(0, PlayerMaterial);
	//PlayerMesh->SetupAttachment(PlayerBoxComponent);
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	
	if (MovementUp != 0)
	{
		NewLocation = GetActorLocation() + (GetActorUpVector() * MovementUp * (DeltaTime * 500));
	}
	if (MovementDown != 0)
	{
		NewLocation = GetActorLocation() + (GetActorUpVector() * MovementDown * (DeltaTime* 500));
	}

	SetActorLocation(NewLocation);
}

void APlayerPaddle::MoveUp(float value)
{
	MovementUp = value;

}

void APlayerPaddle::MoveDown(float value)
{
	MovementDown = value;

}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

