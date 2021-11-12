// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddle.generated.h"


UCLASS()
class PONG_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* PlayerBoxComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Custom")
		class UPaperSpriteComponent* PlayerSprite;

	UPROPERTY(VisibleAnywhere, Category = "Game Camera")
		class UCameraComponent* GameCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class USpringArmComponent* SpringArm;




	////unused but worked - see cpp definition for details 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	//	class UStaticMeshComponent* PlayerMesh;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	//	class UMaterial* PlayerMaterial;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveUp(float value);
	void MoveDown(float value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float MovementUp;
	float MovementDown;
};
