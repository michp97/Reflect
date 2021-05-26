// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GlobalGameBase.h"
#include "CompleteQuest.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "cppProjectGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class CPPPROJECT_API AcppProjectGameModeBase : public AGameModeBase, public ICompleteQuest
{
	GENERATED_BODY()

public:
	AcppProjectGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<bool> CompletedTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentReflectNumber;

	UPROPERTY(BlueprintReadWrite)
		int32 CurrentLevelScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Paused;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> SensorsToComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelReflectNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LevelTime;


private:

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int32 getCurrentLevelIndex();

	UFUNCTION(BlueprintCallable)
		bool CheckTask();

	UFUNCTION(BlueprintCallable)
		void LoadLevel(int32 Case);

	UFUNCTION(BlueprintCallable)
		float CalculateScore();

	UFUNCTION(BlueprintCallable)
		void PauseGame(bool state);



	FDateTime TimeNow;

};
