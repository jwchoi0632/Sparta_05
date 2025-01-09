// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Spawn Player Actor"));
	//이 액터가 생성되면 로그에 Spawn Player Actor 가 출력 됨.
	StartLocation = FVector2D::ZeroVector;
	//액터의 시작점을 2차원 백터의 Zero, 즉 (0,0)으로 초기화.
	SetActorLocation(ConvertVector2DToVector3D(StartLocation));
	//초기화한 백터 값을 액터의 Location에 할당
	PrintLogOfActorLocation();
	//액터의 위치 정보를 출력
	Move();
	//10번의 스탭과 그 과정에서의 기능들을 수행하는 Move() 함수 호출
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APlayerActor::ConvertVector2DToVector3D(FVector2D Vector2D)
{
	//임의로 만든 함수. 2D 백터에서 3D로 변환
	return FVector(Vector2D, 0);
}

FVector2D APlayerActor::ConvertVector3DToVector2D(FVector Vector3D)
{
	//임의로 만든 함수. 3D 백터에서 2D로 변환
	return FVector2D(Vector3D.X, Vector3D.Y);
}

int32 APlayerActor::Step()
{
	//매 이동 방향을 정해줄 Step() 함수. 0 혹은 1을 랜덤하게 반환한다
	return FMath::RandRange(0, 1);
}

int32 APlayerActor::CreateEvent()
{
	//이벤트가 발생할 것인지 판단하기 위한 랜덤 값을 반환하는 함수. 1~100의 숫자 중에 하나를 랜덤하게 반환
	return FMath::RandRange(1, 100);
}

float APlayerActor::Distance(FVector2D First, FVector2D Second)
{
	//시작 위치와 이동 위치 사이의 거리를 계산해주는 함수.
	float Result = FMath::Sqrt(FMath::Pow(First.X - Second.X, 2) + FMath::Pow(First.Y - Second.Y, 2));
	UE_LOG(LogTemp, Warning, TEXT("Step Distance : %f"), Result);
	return Result;
}

void APlayerActor::PrintLogOfActorLocation()
{
	//액터의 현재 위치를 출력하는 함수
	UE_LOG(LogTemp, Warning, TEXT("Player Actor Position = (%f, %f)"), (float)GetActorLocation().X, (float)GetActorLocation().Y);
}

void APlayerActor::Move()
{
	float TotalMoveDistance = 0.0f;
	int32 EventTriggerCount = 0;
	//10회의 반복 스탭을 마친 후에 총 이동 거리와 이벤트 발생 횟수를 출력하기 위한 변수

	for (int i = 0; i < 10; i++)
	{
		int32 StepX = Step();
		int32 StepY = Step();
		//Step() 함수를 통해 이동할 2차원 방향을 받음
		UE_LOG(LogTemp, Warning, TEXT("Next Step : (%d, %d)"), StepX, StepY);

		FVector2D CurrentLocation = ConvertVector3DToVector2D(GetActorLocation());
		FVector2D NextLocation = FVector2D(StepX, StepY) + CurrentLocation;
		//현재 위치와 이동할 위치. 이동할 위치는 Step을 통해 얻은 값에 현재 위치를 더하여 구함
		TotalMoveDistance += Distance(CurrentLocation, NextLocation);
		//매 스탭마다 두 벡터 사이의 거리를 구하여 총 이동거리에 더함
		int32 EventValue = CreateEvent();
		//CreateEvent()를 통해 랜덤한 값을 받음
		if (EventValue <= 50)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create Event!!"));
			EventTriggerCount++;
			//1~50 의 값을 받았다면 이벤트를 발생, 총 이벤트 발생 횟수를 1 추가해줌
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail to create event"));
			// 51~100의 값을 받았다면 이벤트 발생 실패
		}

		SetActorLocation(ConvertVector2DToVector3D(NextLocation));
		PrintLogOfActorLocation();
		//액터의 위치를 앞서 구한 다음 위치로 이동 시킨 후 위치 정보를 출력
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Move Distance : %f, Event trigger Count : %d"), TotalMoveDistance, EventTriggerCount);
	//10회 반복이 끝난 후 총 이동 거리와 이벤트 발생 횟수를 출력
}

