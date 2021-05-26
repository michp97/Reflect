// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "cppProjectGameModeBase.h"
#include "CompleteQuest.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSensor.generated.h"

UCLASS()
class CPPPROJECT_API ALightSensor : public AActor, public ICompleteQuest
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightSensor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Signature;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor rayColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SensorMeshComp;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* EnabledSensorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* DisabledSensorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* DynMat;

public:
	UFUNCTION(BlueprintCallable)
		void Enable(bool State);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool Enabled;


	/*
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void OState(bool state);
		virtual void OState_Implementation(bool state);

*/
};
