// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSensor.h"

// Sets default values
ALightSensor::ALightSensor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Signature = GetName().Mid(0, 1);

	ConstructorHelpers::FObjectFinder< UStaticMesh> MeshRef(TEXT("StaticMesh'/Game/Objects/Sensor.Sensor'"));
	ConstructorHelpers::FObjectFinder< UMaterial> EMatRef(TEXT("Material'/Game/Objects/Materials/sensor-enabled.sensor-enabled'"));
	ConstructorHelpers::FObjectFinder< UMaterial> DMatRef(TEXT("Material'/Game/Objects/Materials/sensor.sensor'"));
	ConstructorHelpers::FObjectFinder< UMaterialInstance> DynMatRef(TEXT("MaterialInstanceConstant'/Game/Objects/Materials/SensorInstance.SensorInstance'"));

	SensorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SensorMesh Component"));

	EnabledSensorMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Enabled Mat"));
	DisabledSensorMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Disabled Mat"));

	EnabledSensorMaterial = EMatRef.Object;
	DisabledSensorMaterial = DMatRef.Object;

	DynMat = DynMatRef.Object;
	SetRootComponent(SensorMeshComp);

	SensorMeshComp->SetStaticMesh(MeshRef.Object);
	SensorMeshComp->SetMaterial(0, DynMatRef.Object);
	SensorMeshComp->SetMobility(EComponentMobility::Static);

	//Enabled = false;
}

// Called when the game starts or when spawned
void ALightSensor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALightSensor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Enabled == true )
	{
		AcppProjectGameModeBase* gameMode = Cast<AcppProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		ICompleteQuest* Interface = Cast<ICompleteQuest>(gameMode);
		Interface->Execute_CompleteTask(gameMode, GetName(), Enabled);
	}
	Enable(false);
}


void ALightSensor::Enable(bool State)
{
	Enabled = State;

	if (State)
	{
		UMaterialInstanceDynamic* A;
		//DynMat = UMaterialInstanceDynamic::Create(EnabledSensorMaterial, SensorMeshComp);
		A = SensorMeshComp->CreateDynamicMaterialInstance(0, EnabledSensorMaterial);
		A->SetVectorParameterValue(TEXT("EmisiveColor"), rayColor);
		//SensorMeshComp->SetMaterial(0, DynMat);
	}
	else
	{
		UMaterialInstanceDynamic* B;
		B = SensorMeshComp->CreateDynamicMaterialInstance(0, DisabledSensorMaterial);
		B->SetVectorParameterValue(TEXT("EmisiveColor"), rayColor);
		//DynMat = UMaterialInstanceDynamic::Create(DisabledSensorMaterial, SensorMeshComp);
		//SensorMeshComp->SetMaterial(0, DynMat);
	}

}

/*
void ALightSensor::OState_Implementation(bool state)
{
	if (state)
		this->SensorMesh->SetMaterial(0, EnabledSensorMaterial);
	else
		this->SensorMesh->SetMaterial(0, DisabledSensorMaterial);
}
*/






