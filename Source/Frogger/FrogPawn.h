// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "FrogPawn.generated.h"

UCLASS()
class FROGGER_API AFrogPawn : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveUpInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveDownInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveLeftInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveRightInputAction;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void BeginMove(const FVector& Direction);


public:

	// Sets default values for this pawn's properties
	AFrogPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//If in the middle of movement;
	UPROPERTY(BlueprintReadWrite)
	bool bMoving;

	UPROPERTY(BlueprintReadWrite)
	FVector StartPosition;
	
	UPROPERTY(BlueprintReadWrite)
	FVector Destination;

	UPROPERTY(EditAnywhere)
	int MovementUnit;

	UPROPERTY(EditAnywhere)
	double TimeToMove;
	
	double TimePassed;

	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveFinished();
	

};
