// Copyright Epic Games, Inc. All Rights Reserved.


#include "cppProjectGameModeBase.h"
#include "MouseGrabPawn.h"


AcppProjectGameModeBase::AcppProjectGameModeBase()
{
	//DefaultPawnClass = AMouseGrabPawn::StaticClass();

	TimeNow = FDateTime::FDateTime();
	CurrentReflectNumber = 0;

	Paused = false;


}

void AcppProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	int32 index = getCurrentLevelIndex();

	UGlobalGameBase* GBase = GetGameInstance<UGlobalGameBase>();
	SensorsToComplete = GBase->Levels[index].ObjectivesNames;


	for (int c = 0; c < SensorsToComplete.Num(); c++)
	{
		CompletedTasks.Add(false);
	}

	TimeNow = FDateTime::Now();

	//controller = GetWorld()->GetFirstPlayerController();

	//FInputModeGameOnly imputMode;
	//controller->SetInputMode(imputMode);
	//controller->bShowMouseCursor = true;

	//CheckLevel();
}

void AcppProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AcppProjectGameModeBase::CheckTask()
{
	for (int i = 0; i < SensorsToComplete.Num(); i++)
	{
		if (CompletedTasks[i]==false)
		{
			return false;
		}
			
	}
	return true;
}

int32 AcppProjectGameModeBase::getCurrentLevelIndex()
{
	int32 index = 0;
	FString currentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	UGlobalGameBase* GBase = GetGameInstance<UGlobalGameBase>();

	for (index; index < GBase->Levels.Num(); index++)
	{
		if (GBase->Levels[index].Name == currentLevelName)
			return index;
	}


	UE_LOG(LogTemp, Warning, TEXT("Index: %d"), index);
	//GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Purple, TEXT("Reflect"));

	return index;
	
}


void AcppProjectGameModeBase::LoadLevel(int32 Case)
{
	int32 index = getCurrentLevelIndex();
	UGlobalGameBase* GBase = GetGameInstance<UGlobalGameBase>();
	FString LevelName = GBase->Levels[index].Name;

	if (CheckTask())
	{
		if (index < GBase->Levels.Num() - 1)
		{
			GBase->UnlockLevel(GBase->Levels[index + 1].Name);
		}
		else
			Case = 1;

		GBase->SetPlayerScoreOnLevel(LevelName, LevelTime, CurrentReflectNumber, CurrentLevelScore);
	}

	switch (Case)
	{
		case 0: 
			UGameplayStatics::OpenLevel(GetWorld(), (FName)("/Game/Levels/" + GBase->Levels[index+1].Name));
			break;
		case 1:
			UGameplayStatics::OpenLevel(GetWorld(), (FName)("/Game/Levels/MainMenu"));
			break;

		case 2:
			UGameplayStatics::OpenLevel(GetWorld(), (FName)("/Game/Levels/" + GBase->Levels[index].Name));
			break;
	}
	
}

float AcppProjectGameModeBase::CalculateScore()
{
	FTimespan Time = FDateTime::Now() - TimeNow;
	double seconds = Time.GetSeconds();
	double minutes = Time.GetMinutes();

	FTimespan MaxTime = FTimespan(0, 1, 0, 0);
	if (Time == MaxTime)
	{
		LoadLevel(1);
	}
	
	LevelTime = seconds + minutes *(60);

	int32 index = getCurrentLevelIndex();
	
	UGlobalGameBase* GBase = GetGameInstance<UGlobalGameBase>();

	int32 DRNumber = GBase->Levels[index].DefaultReflectNumber;
	float DTime = GBase->Levels[index].DefaultTime;

	float DCombine = (2 * DTime + DRNumber) / 2;
	float Combine = (2 * LevelTime + CurrentReflectNumber) / 2.5;


	if (Combine / DCombine <= 1.0f)
		CurrentLevelScore = 10;
	else
	{
		if (Combine / DCombine >= 2.0f)
			CurrentLevelScore = 0;
		else
			CurrentLevelScore = floor(10 - ((Combine / DCombine) - 1) * 10);
	}

	return CurrentLevelScore;

}

void AcppProjectGameModeBase::PauseGame(bool state)
{
	Paused = state;
	UGameplayStatics::SetGamePaused(GetWorld(), Paused);

}



