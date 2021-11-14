// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerController.h"
#include "PlayerPaddle.h"
#include "Kismet/KismetSystemLibrary.h"


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
        InputComponent->BindAxis("Escape", this, &AUEPlayerController::QuitGame);

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

void AUEPlayerController::QuitGame(float value)
{
    //This is to make the game close.
    //If i am honest i wanted to send the end result to a friend, he is not exactly computer savy and would not know to push alt-f4 to close the window.
    //At this point in the project i am getting decent at googling things for unreal haha.
    if (value != 0.0f)
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Type::Quit, false);
}

