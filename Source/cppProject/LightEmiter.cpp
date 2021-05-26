// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEmiter.h"


// Sets default values
ALightEmiter::ALightEmiter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	//SetRootComponent(meshComp);

	Mirror = CreateDefaultSubobject<UMaterial>(TEXT("Mirror"));
	Sensor = CreateDefaultSubobject<UMaterial>(TEXT("Sensor"));

	ConstructorHelpers::FObjectFinder< UParticleSystem> ParticleRef(TEXT("ParticleSystem'/Game/Objects/Particles/LaserParticle.LaserParticle'"));
	
	laserParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("Laser Beam Particles"));
	laserParticle = ParticleRef.Object;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser Beam Particles Comp"));

	//ConstructorHelpers::FObjectFinder< UMaterial> ParticleMaterialRef(TEXT("Material'/Game/Objects/Materials/laser_beam.laser_beam'"));

	//UMaterial* LaserMaterial = ParticleMaterialRef.Object;
	//FName ParamName = "BeamColor";

	PartArray.Init(0,10);
	for(int i = 0; i<10;i++)
	{
		FName x = (FName)(FString::FromInt(i));
		PartArray[i] = CreateDefaultSubobject<UParticleSystemComponent>(x);
		PartArray[i]->Template = laserParticle;
		//PartArray[i]->SetMaterial(0, LaserMaterial);
		//PartArray[i]->SetColorParameter(ParamName, laserColor);
		//Partic->bDeactivateTriggered = true;
			//UE_LOG(LogTemp, Warning, TEXT("Array[ %d ] == Particle"), i);

	}

	// LSensor =new AActor();
	//HittedSensorName = new FString;
	//*HittedSensorName = "";

}

// Called when the game starts or when spawned
void ALightEmiter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALightEmiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ALightSensor* ALightEmiter::CastLight(FVector CastOrigin, FVector CastDirection, float CastDistance) const
{
	FVector LaserStart = CastOrigin;
	FVector LaserDirection = CastDirection;
	float LaserDistance = CastDistance;
	bool LaserContinue = true;
	bool blocked = false;
	FHitResult* OutHit = new FHitResult;
	FVector LaserEnd;
	int32 section = 1;
	FName TraceTag("TraceTag");
	int ReflectNumber = 0;
	//TArray<UParticleSystemComponent*> PartArray;
	ALightSensor* LSensor=nullptr;


	//if (*HittedSensorName != "")
	//	LSensor->Enable(false);


	while (LaserContinue == true)
	{
		if (ReflectNumber >= 10)
			break;
		LaserEnd = LaserStart + LaserDirection * LaserDistance;
		//GetWorld()->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams CollisionParams(TraceTag, true);
		CollisionParams.bReturnFaceIndex = true;
		CollisionParams.bTraceComplex = true;


		blocked = this->GetWorld()->LineTraceSingleByChannel(*OutHit, LaserStart, LaserEnd, ECC_GameTraceChannel1, CollisionParams, ECR_Block);

		//DrawParticle(LaserStart, LaserEnd, laserParticle);

		//DrawDebugLine(GetWorld(), LaserStart, LaserEnd, FColor::Blue, false, 0.1f);


		if (blocked == false)
		{
			LaserContinue = false;
			if (ReflectNumber < 10)
			{
				//PartArray.Add((GetWorld()->SpawnActor<UParticleSystemComponent>()));
				//PartArray[ReflectNumber]->Template = laserParticle;

				PartArray[ReflectNumber]->SetBeamSourcePoint(0, LaserStart, 0);
				PartArray[ReflectNumber]->SetBeamTargetPoint(0, LaserEnd, 0);
				//GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green, TEXT("Reflect"));
				//UE_LOG(LogTemp, Warning, TEXT("-> %d"), ReflectNumber);

			}
			ReflectNumber++;
		}
		else
		{

			if (ReflectNumber < 10)
			{
			//	PartArray.Add((GetWorld()->SpawnActor<UParticleSystemComponent>()));
			//	PartArray[ReflectNumber]->Template = laserParticle;
				PartArray[ReflectNumber]->SetBeamSourcePoint(0, LaserStart, 0);
				PartArray[ReflectNumber]->SetBeamTargetPoint(0, OutHit->ImpactPoint, 0);
				//GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Purple, TEXT("Reflect"));
				//UE_LOG(LogTemp, Warning, TEXT("-> %d"), ReflectNumber);

			}
			ReflectNumber++;

			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(OutHit->Component);
			UMaterialInterface* objectMat = mesh->GetMaterialFromCollisionFaceIndex(OutHit->FaceIndex, section);

			//UE_LOG(LogTemp, Warning, TEXT("-> %d"), OutHit->FaceIndex);

			if (objectMat->GetName() == Mirror->GetName())
			{
				LaserStart = OutHit->ImpactPoint;
				LaserDirection = LaserDirection.MirrorByVector(OutHit->ImpactNormal);
				//UE_LOG(LogTemp, Warning, TEXT("Yes"));
			}
			else
			{
				if (objectMat->GetBaseMaterial() == Sensor->GetBaseMaterial())
				{
					LSensor = Cast<ALightSensor>(OutHit->GetActor());
					if (laserColor.Equals(LSensor->rayColor))
					{
						LSensor->Enable(true);
						//UE_LOG(LogTemp, Warning, TEXT("RIGHT COLOR"));
					}
					//UE_LOG(LogTemp, Warning, TEXT("------ "));
					//if(OutHit->Actor == NULL)

					LaserContinue = false;
				}
				else
					LaserContinue = false;
			}
		}
	OutHit = new FHitResult;
	}

	int i = 0;
	for(UParticleSystemComponent* Partic : PartArray)
	{
		if (i >= ReflectNumber)
		{
			Partic->SetBeamSourcePoint(0, { 9999,9999,9999 }, 0);
			Partic->SetBeamTargetPoint(0, { 9999,9999,9999 }, 0);
		}
		i++;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Array: %d"), i);
	if (LSensor!=nullptr)
	{
		ICompleteQuest* Interface = Cast<ICompleteQuest>(UGameplayStatics::GetGameMode(GetWorld()));
		Interface->Execute_ReflectNr(UGameplayStatics::GetGameMode(GetWorld()), ReflectNumber, GetName());
	}

	return LSensor;

}

