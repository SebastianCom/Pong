// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerController.h"
#include "PlayerPaddle.h"


void AUEPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    MyPawn = Cast<APlayerPaddle>(aPawn);
   // GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::Possess: - " + aPawn->GetName());
}


void AUEPlayerController::OnUnPossess()
{

    Super::OnUnPossess();
}

void AUEPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent != nullptr)
    {
        InputComponent->BindAxis("MoveUp", this, &AUEPlayerController::MoveUp);
        InputComponent->BindAxis("MoveDown", this, &AUEPlayerController::MoveDown);

    }
}

void AUEPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{
}

void AUEPlayerController::MoveUp(float value)
{
    if (MyPawn)
    {
        MyPawn->MoveUp(value);
    }
        
}

void AUEPlayerController::MoveDown(float value)
{
    if (MyPawn)
    {
        MyPawn->MoveDown(value);
    }

}
