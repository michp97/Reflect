// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase.h"
/*
AGameBase::AGameBase()
{
	FLevelInfo l;

	Levels.Init(l, 20);
	for (int i = 0; i < Levels.Num(); i++)
	{
		Levels[i].Name = FString::FromInt(i);
	}

	TotalScore = 0;

	UnlockLevel("0");
	UnlockLevel("1");

}

void AGameBase::SetupLevel(FString name, float defaultTime, int32 defaultReflectNumber)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].DefaultTime = defaultTime;
	Levels[index].DefaultReflectNumber = defaultReflectNumber;

}

void AGameBase::SetPlayerScoreOnLevel(FString name, float time, int32 reflectNumber, int32 score)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].Time = time;
	Levels[index].ReflectNumber = reflectNumber;
	Levels[index].Score = score;

}

void AGameBase::UnlockLevel(FString name)
{
	int32 index = FCString::Atoi(*name);

	Levels[index].Locked=false;
}
*/