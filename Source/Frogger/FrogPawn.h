// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "FrogPawn.generated.h"

UENUM(BlueprintType)
enum EDir
{
	Down,
	Up,
	Right,
	Left,
	None
};

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
	void BeginMove(const EDir& NewDirection);
	void LateInitialize();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bCanMove;
	
	bool bInitialized;

public:

	UPROPERTY()
	class AFroggerPlayerController* FroggerController;
	
	// Sets default values for this pawn's properties
	AFrogPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called when character touches ground
	virtual void Landed(const FHitResult& Hit) override;
	
	EDir Direction;
	
	//Is character is in the middle of movement?
	UPROPERTY(BlueprintReadWrite)
	bool bMoving;
	
	UPROPERTY(EditAnywhere, Category = "Launch")
	float HorizontalRange;

	UPROPERTY(EditAnywhere, Category = "Launch")
	float TimeToLand;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* FrogMesh;

	void RoundLocation() const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveFinished();

	void LaunchFrog();
};
