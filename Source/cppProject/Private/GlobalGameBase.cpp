// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameBase.h"

UGlobalGameBase::UGlobalGameBase()
{

	PlayerNamed = false;

	FLevelInfo l;

	Levels.Init(l, 11);
	for (int i = 0; i < Levels.Num(); i++)
	{
		Levels[i].Name = FString::FromInt(i);
		Levels[i].Locked = true;
	}

	TotalScore = 0;

	StartTime = FDateTime::Now();

	PLayerName = TEXT("PLayer");

	//Levels
	TArray<FString> a;
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	SetupLevel("0", 10, 6, a);

	a.Empty();
	
	//1
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	SetupLevel("1", 10, 4, a);

	UnlockLevel("1");
	a.Empty();

	//2
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	a.Add(TEXT("B"));
	SetupLevel("2", 20, 8, a);

	a.Empty();

	//3
	a.Add(TEXT("R"));
	a.Add(TEXT("B"));
	SetupLevel("3", 20, 6, a);

	a.Empty();

	//4
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	a.Add(TEXT("B"));
	SetupLevel("4", 30, 8, a);

	a.Empty();

	//5
	a.Add(TEXT("R"));
	a.Add(TEXT("B"));
	SetupLevel("5", 30, 8, a);

	a.Empty();

	//6
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	a.Add(TEXT("B"));
	SetupLevel("6", 30, 10, a);

	a.Empty();

	//7
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	a.Add(TEXT("B"));
	SetupLevel("7", 80, 16, a);

	a.Empty();

	//8
	a.Add(TEXT("W"));
	a.Add(TEXT("R"));
	a.Add(TEXT("G"));
	a.Add(TEXT("B"));
	SetupLevel("8", 100, 20, a);

	a.Empty();

	//9
	a.Add(TEXT("W"));
	a.Add(TEXT("G"));
	SetupLevel("9", 60, 6, a);

	a.Empty();

	//10
	a.Add(TEXT("P"));
	SetupLevel("10", 20, 5, a);

	a.Empty();
}

void UGlobalGameBase::SetupLevel(FString name, float defaultTime, int32 defaultReflectNumber, TArray<FString> objectivesNames)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].DefaultTime = defaultTime;
	Levels[index].DefaultReflectNumber = defaultReflectNumber;
	Levels[index].ObjectivesNames = objectivesNames;

}

void UGlobalGameBase::SetPlayerScoreOnLevel(FString name, float time, int32 reflectNumber, int32 score)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].Time = time;
	Levels[index].ReflectNumber = reflectNumber;
	Levels[index].Score = score;

}

void UGlobalGameBase::UnlockLevel(FString name)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].Locked = false;
}

bool UGlobalGameBase::IsLevelLocked(int32 LevelIndex)
{
	bool locked = Levels[LevelIndex].Locked;

	return locked ;
}

int32 UGlobalGameBase::CalculateTotalScore()
{
	int32 score=0;
	for (int i = 0; i < Levels.Num(); i++)
	{
		score = score + Levels[i].Score;
	}
	return score;
}

