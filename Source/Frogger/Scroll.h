// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scroll.generated.h"

UCLASS()
class FROGGER_API AScroll : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScroll();

	UPROPERTY(EditAnywhere)
	double ScrollSpeed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
