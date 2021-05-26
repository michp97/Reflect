// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightBeam.generated.h"

UCLASS()
class CPPPROJECT_API ALightBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void GoLaserMesh(FVector Begin, FVector End) const;

	UPROPERTY(EditAnywhere)
		FVector Location;

	UPROPERTY(EditAnywhere)
		FQuat Rotation;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LaserBeam;

};
