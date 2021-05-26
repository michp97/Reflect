#include "MouseGrabPawn.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseGrabPawn.h"

// Sets default values
AMouseGrabPawn::AMouseGrabPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMouseGrabPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMouseGrabPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMouseGrabPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMouseGrabPawn::Grab()
{

}


