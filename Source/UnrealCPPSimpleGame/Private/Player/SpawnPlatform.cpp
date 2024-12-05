// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SpawnPlatform.h"

#include "Components/TextRenderComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USpawnPlatform::USpawnPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPlatform::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnedActor.SetNum(SelectedActor.Num());
}


// Called every frame
void USpawnPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnPlatform::SpawnBloack()
{
	if (SelectedActor.Num() == 0 || !SelectedActor.IsValidIndex(Index)) // Check if the ActorClass is valid
	{
		UE_LOG(LogTemp, Error, TEXT("No ActorClass provided for spawning!"));
		return;
	}

	if (!SpawnPoint)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnPoint is null!"));
		return;
	}

	// Get the world context
	UWorld* World = GetWorld();
	if (World)
	{
		FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = SpawnPoint->GetComponentRotation();

		// Raggio della sfera
		float SphereRadius = 20.f;

		// Risultato del trace
		FHitResult HitResult;

		// Parametri di collisione
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(SpawnPoint->GetAttachmentRootActor()); // Ignora l'attore stesso

		// Esegui lo Sphere Trace
		bool bHit = World->SweepSingleByChannel(
			HitResult,
			SpawnLocation,
			SpawnLocation,
			FQuat::Identity, // Nessuna rotazione
			ECC_Visibility,  // Canale di collisione
			FCollisionShape::MakeSphere(SphereRadius), // Crea una sfera per il trace
			CollisionParams
		);

		if (bHit) return;
        
		if (SpawnedActor[Index])
		{
			SpawnedActor[Index]->SetActorLocationAndRotation(SpawnLocation,SpawnRotation,false, nullptr,ETeleportType::TeleportPhysics);
		}
		else
		{
			// Spawn the actor
			SpawnedActor[Index] = World->SpawnActor<AActor>(SelectedActor[Index], SpawnLocation, SpawnRotation);
		}
		
	}
}

void USpawnPlatform::DeletBloack()
{
	if (SpawnedActor.Num() == 0 || !SpawnedActor.IsValidIndex(Index)) // Check if the ActorClass is valid
	{
		UE_LOG(LogTemp, Error, TEXT("No ActorClass provided for spawning!"));
		return;
	}

	if (SpawnedActor[Index])
	{
		SpawnedActor[Index]->Destroy();
		SpawnedActor[Index] = nullptr;
	}
}

void USpawnPlatform::ChangeIndex(const int& InputValue=0)
{
	Index = Index + InputValue;
	if (Index < 0)
	{
		Index = SelectedActor.Num() - 1;
	}
	if (Index > SelectedActor.Num()-1)
	{
		Index = 0;
	}
	if (TextRender)
	{
		// Converti l'intero in stringa e poi in FText
		TextRender->SetText(FText::FromString(FString::FromInt(Index)));
	};
}

void USpawnPlatform::StartingSet(USceneComponent* SP,UTextRenderComponent* Text)
{
	if (!SP || !Text) return;
	TextRender = Text;
	SpawnPoint = SP;
}
