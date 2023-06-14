// Fill out your copyright notice in the Description page of Project Settings.



#include "FrogPawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FroggerPlayerController.h"
#include "VectorTypes.h"

// Sets default values
AFrogPawn::AFrogPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bInitialized = false;
	bMoving = false;
}

// Called when the game starts or when spawned
void AFrogPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AFrogPawn::LateInitialize()
{
	if (auto Player = Cast<AFroggerPlayerController>(GetController()))
	{
		FroggerController = Player;
		bInitialized = true;
	}
}

// Called every frame
void AFrogPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bInitialized)
	{
		LateInitialize();
		return;
	}

	if (bMoving)
	{
		//MoveCustom(DeltaTime);
		//MoveCharacter(DeltaTime);
		LaunchFrog();
	}
}

void AFrogPawn::LaunchFrog()
{
	long double mult = 0;

	FVector U;

	mult = sqrt(100 * abs(GetWorld()->GetGravityZ()));

	switch (Direction)
	{
	case Down:
		U = FVector(-cos(45), 0, sin(45)) * mult;
		break;
	case Up:
		U = FVector(cos(45), 0, sin(45)) * mult;
		break;
	case Right:
		U = FVector(0, cos(45), sin(45)) * mult;
		break;
	case Left:
		U = FVector(0, -cos(45), sin(45)) * mult;
		break;
	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("ACharacter::LaunchCharacter '%s' (%f,%f,%f)"), *GetName(), U.X, U.Y, U.Z);

	LaunchCharacter(U, false, false);
	bMoving = false;
}

void AFrogPawn::MoveCustom(float DeltaTime)
{
	if (bMoving)
	{
		auto Alpha = FGenericPlatformMath::Min(TimePassed * 100 / TimeToMove, 100.0);
		auto MoveTick = UE::Geometry::Lerp(StartPosition, Destination, Alpha) - GetActorLocation();
		AddActorWorldOffset(MoveTick);
		FroggerController->Server_Move(MoveTick, this);
		//SetActorLocation(MoveTick);
		TimePassed += DeltaTime;

		if (Alpha == 100.0)
		{
			bMoving = false;
			OnMoveFinished();
		}
	}



}

// Called to bind functionality to input
void AFrogPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveUpInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveUp);
		EnhancedInputComponent->BindAction(MoveDownInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveDown);
		EnhancedInputComponent->BindAction(MoveLeftInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveLeft);
		EnhancedInputComponent->BindAction(MoveRightInputAction, ETriggerEvent::Started, this, &AFrogPawn::MoveRight);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast failed!"));
	}
}

void AFrogPawn::BeginMove(const FVector& NewDirection)
{
	if(bMoving)
	{
		return;
	}
	StartPosition = GetActorLocation();
	Destination = StartPosition + NewDirection * MovementUnit;
	bMoving = true;
	TimePassed = 0;
}


void AFrogPawn::MoveUp()
{
	Direction = Up;
	BeginMove(FVector(1,0,0));
}

void AFrogPawn::MoveDown()
{
	Direction = Down;

	BeginMove(FVector(-1,0,0));
}

void AFrogPawn::MoveRight()
{
	Direction = Right;

	BeginMove(FVector(0,1,0));
}

void AFrogPawn::MoveLeft()
{
	Direction = Left;
	BeginMove(FVector(0,-1,0));
}


