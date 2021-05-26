// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBeam.h"

// Sets default values
ALightBeam::ALightBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserBeam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserBeamMesh"));

}

// Called when the game starts or when spawned
void ALightBeam::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ALightBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocationAndRotation(Location, Rotation, false, 0, ETeleportType::None);
	Rotation = Rotation + Rotation;
}

void ALightBeam::GoLaserMesh(FVector Begin, FVector End) const
{
	FQuat rot = End.ToOrientationQuat();

	//SetActorLocationAndRotation(Location, Rotation, false, 0, ETeleportType::None);
}

