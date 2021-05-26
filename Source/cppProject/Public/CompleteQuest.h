// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CompleteQuest.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCompleteQuest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPPPROJECT_API ICompleteQuest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void CompleteTask(const FString& TriggerName, bool State);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Go(int32 Case);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ReflectNr(int32 Reflects, const FString& EmiterName);
};
