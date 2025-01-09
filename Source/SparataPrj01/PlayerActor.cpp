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
	//�� ���Ͱ� �����Ǹ� �α׿� Spawn Player Actor �� ��� ��.
	StartLocation = FVector2D::ZeroVector;
	//������ �������� 2���� ������ Zero, �� (0,0)���� �ʱ�ȭ.
	SetActorLocation(ConvertVector2DToVector3D(StartLocation));
	//�ʱ�ȭ�� ���� ���� ������ Location�� �Ҵ�
	PrintLogOfActorLocation();
	//������ ��ġ ������ ���
	Move();
	//10���� ���ǰ� �� ���������� ��ɵ��� �����ϴ� Move() �Լ� ȣ��
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APlayerActor::ConvertVector2DToVector3D(FVector2D Vector2D)
{
	//���Ƿ� ���� �Լ�. 2D ���Ϳ��� 3D�� ��ȯ
	return FVector(Vector2D, 0);
}

FVector2D APlayerActor::ConvertVector3DToVector2D(FVector Vector3D)
{
	//���Ƿ� ���� �Լ�. 3D ���Ϳ��� 2D�� ��ȯ
	return FVector2D(Vector3D.X, Vector3D.Y);
}

int32 APlayerActor::Step()
{
	//�� �̵� ������ ������ Step() �Լ�. 0 Ȥ�� 1�� �����ϰ� ��ȯ�Ѵ�
	return FMath::RandRange(0, 1);
}

int32 APlayerActor::CreateEvent()
{
	//�̺�Ʈ�� �߻��� ������ �Ǵ��ϱ� ���� ���� ���� ��ȯ�ϴ� �Լ�. 1~100�� ���� �߿� �ϳ��� �����ϰ� ��ȯ
	return FMath::RandRange(1, 100);
}

float APlayerActor::Distance(FVector2D First, FVector2D Second)
{
	//���� ��ġ�� �̵� ��ġ ������ �Ÿ��� ������ִ� �Լ�.
	float Result = FMath::Sqrt(FMath::Pow(First.X - Second.X, 2) + FMath::Pow(First.Y - Second.Y, 2));
	UE_LOG(LogTemp, Warning, TEXT("Step Distance : %f"), Result);
	return Result;
}

void APlayerActor::PrintLogOfActorLocation()
{
	//������ ���� ��ġ�� ����ϴ� �Լ�
	UE_LOG(LogTemp, Warning, TEXT("Player Actor Position = (%f, %f)"), (float)GetActorLocation().X, (float)GetActorLocation().Y);
}

void APlayerActor::Move()
{
	float TotalMoveDistance = 0.0f;
	int32 EventTriggerCount = 0;
	//10ȸ�� �ݺ� ������ ��ģ �Ŀ� �� �̵� �Ÿ��� �̺�Ʈ �߻� Ƚ���� ����ϱ� ���� ����

	for (int i = 0; i < 10; i++)
	{
		int32 StepX = Step();
		int32 StepY = Step();
		//Step() �Լ��� ���� �̵��� 2���� ������ ����
		UE_LOG(LogTemp, Warning, TEXT("Next Step : (%d, %d)"), StepX, StepY);

		FVector2D CurrentLocation = ConvertVector3DToVector2D(GetActorLocation());
		FVector2D NextLocation = FVector2D(StepX, StepY) + CurrentLocation;
		//���� ��ġ�� �̵��� ��ġ. �̵��� ��ġ�� Step�� ���� ���� ���� ���� ��ġ�� ���Ͽ� ����
		TotalMoveDistance += Distance(CurrentLocation, NextLocation);
		//�� ���Ǹ��� �� ���� ������ �Ÿ��� ���Ͽ� �� �̵��Ÿ��� ����
		int32 EventValue = CreateEvent();
		//CreateEvent()�� ���� ������ ���� ����
		if (EventValue <= 50)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create Event!!"));
			EventTriggerCount++;
			//1~50 �� ���� �޾Ҵٸ� �̺�Ʈ�� �߻�, �� �̺�Ʈ �߻� Ƚ���� 1 �߰�����
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail to create event"));
			// 51~100�� ���� �޾Ҵٸ� �̺�Ʈ �߻� ����
		}

		SetActorLocation(ConvertVector2DToVector3D(NextLocation));
		PrintLogOfActorLocation();
		//������ ��ġ�� �ռ� ���� ���� ��ġ�� �̵� ��Ų �� ��ġ ������ ���
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Move Distance : %f, Event trigger Count : %d"), TotalMoveDistance, EventTriggerCount);
	//10ȸ �ݺ��� ���� �� �� �̵� �Ÿ��� �̺�Ʈ �߻� Ƚ���� ���
}

