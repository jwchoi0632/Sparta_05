// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

UCLASS()
class SPARATAPRJ01_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FVector2D StartLocation;

	FVector ConvertVector2DToVector3D(FVector2D Vector2D);
	FVector2D ConvertVector3DToVector2D(FVector Vector3D);
	int32 Step();
	int32 CreateEvent();
	float Distance(FVector2D First, FVector2D Second);
	void PrintLogOfActorLocation();
	void Move();
};
