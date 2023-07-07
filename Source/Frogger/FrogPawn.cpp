// Fill out your copyright notice in the Description page of Project Settings.



#include "FrogPawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FroggerPlayerController.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AFrogPawn::AFrogPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Direction = None;
	
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
	if (const auto Player = Cast<AFroggerPlayerController>(GetController()))
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

	if (bMoving && Direction != None)
	{
		FroggerController->LaunchFrog(HorizontalRange, TimeToLand, Direction);
		//LaunchFrog();
		Direction = None;
	}
	
}

void AFrogPawn::RoundLocation() const
{
	const auto Location = GetActorLocation();

	const auto RoundedX = round(Location.X);
	const auto RoundedY = round(Location.Y);

	const auto RemainderX = static_cast<int>(abs(RoundedX)) % 100;
	const auto RemainderY = static_cast<int>(abs(RoundedY)) % 100;

	double NewX, NewY;
	
	if(RemainderX > 50)
	{
		NewX = Location.X < 0 ? -(abs(RoundedX) - RemainderX + 100) : RoundedX - RemainderX + 100;
	}
	else
	{
		NewX = Location.X < 0 ? -(abs(RoundedX) - RemainderX) : RoundedX - RemainderX;
	}

	if(RemainderY > 50)
	{
		NewY = Location.Y < 0 ? -(abs(RoundedY) - RemainderY + 100) : RoundedY - RemainderY + 100;
	}
	else
	{
		NewY = Location.Y < 0 ? -(abs(RoundedY) - RemainderY) : RoundedY - RemainderY;
	}

	GetRootComponent()->SetWorldLocation(FVector(NewX,NewY,Location.Z));
}

void AFrogPawn::LaunchFrog()
{
	const long double Mult = sqrt(HorizontalRange/TimeToLand * abs(GetWorld()->GetGravityZ()));

	FVector U;

	switch (Direction)
	{
	case Down:
		U = FVector(-cos(45), 0, sin(45)) * Mult;
		break;
	case Up:
		U = FVector(cos(45), 0, sin(45)) * Mult;
		break;
	case Right:
		U = FVector(0, cos(45), sin(45)) * Mult;
		break;
	case Left:
		U = FVector(0, -cos(45), sin(45)) * Mult;
		break;
	default:
		break;
	}

	LaunchCharacter(U, false, false);
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

void AFrogPawn::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	UE_LOG(LogTemp,Warning,TEXT("Landed"));
	
	bMoving = false;
	GetMovementComponent()->Velocity = FVector(0,0,0);	
	
	RoundLocation();
}

void AFrogPawn::BeginMove(const EDir& NewDirection)
{
	if(bMoving)
	{
		return;
	}
	
	Direction = NewDirection;
	bMoving = true;
}


void AFrogPawn::MoveUp()
{
	BeginMove(Up);
}

void AFrogPawn::MoveDown()
{
	BeginMove(Down);
}

void AFrogPawn::MoveRight()
{
	BeginMove(Right);
}

void AFrogPawn::MoveLeft()
{
	BeginMove(Left);
}


