// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameBase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLevelInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float DefaultTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 DefaultReflectNumber;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Time;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 ReflectNumber;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool Locked;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Score;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FString> ObjectivesNames;

	FLevelInfo()
	{
		Name = "0";
		Locked = true;
		Time = 0;
		ReflectNumber = 0;
		Score = 0;
	}

};

UCLASS()
class CPPPROJECT_API UGlobalGameBase : public UGameInstance
{
	GENERATED_BODY()

public:
	UGlobalGameBase();

	UFUNCTION(BlueprintCallable)
		void SetupLevel(FString name, float defaultTime, int32 defaultReflectNumber, TArray<FString> objectivesNames);

	UFUNCTION(BlueprintCallable)
		void SetPlayerScoreOnLevel(FString name, float time, int32 reflectNumber, int32 score);

	UFUNCTION(BlueprintCallable)
		void UnlockLevel(FString name);

	UFUNCTION(BlueprintCallable)
		bool IsLevelLocked(int32 LevelIndex);

	UFUNCTION(BlueprintCallable)
		int32 CalculateTotalScore();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 TotalScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FLevelInfo> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool LoadLevelSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PLayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerNamed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime StartTime;

};
