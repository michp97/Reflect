// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CompleteQuest.h"
#include "Particles/ParticleSystemComponent.h"
#include <string>
#include "DrawDebugHelpers.h"
#include "LightSensor.h"
#include "Materials/MaterialInterface.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "LightEmiter.generated.h"


UCLASS()
class CPPPROJECT_API ALightEmiter : public AActor, public ICompleteQuest
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ALightEmiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float castDistance = 2000;

	UFUNCTION(BlueprintCallable)
		ALightSensor* CastLight(FVector CastOrigin, FVector CastDirection, float CDistance) const;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* laserParticle ;
		UParticleSystemComponent* ParticleComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FLinearColor laserColor=FLinearColor::Blue;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Mirror;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Sensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UParticleSystemComponent*> PartArray;

};
