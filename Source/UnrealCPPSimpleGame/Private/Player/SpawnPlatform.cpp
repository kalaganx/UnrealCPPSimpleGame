// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SpawnPlatform.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

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
	SpawnedActor.SetNum(SelectedActors.Num());
}


// Called every frame
void USpawnPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnPlatform::SpawnBloack()
{
	if (SelectedActors.Num() == 0 || !SelectedActors.IsValidIndex(Index)) // Check if the ActorClass is valid
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
		// Ottieni posizione e rotazione della Box
		FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = SpawnPoint->GetComponentRotation();
		

		// Array per contenere gli attori colpiti
		TArray<AActor*> OverlappedActors;

		// Configura il rilevamento per tutti i tipi di oggetti
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		for (int32 i = 0; i < EObjectTypeQuery::ObjectTypeQuery_MAX; ++i)
		{
			ObjectTypes.Add(static_cast<EObjectTypeQuery>(i));
		}

		// Attori da ignorare
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(SpawnPoint->GetAttachmentRootActor()); // Ignora l'attore stesso
		
		// Esegui il Box Overlap
		UKismetSystemLibrary::BoxOverlapActors(World,SpawnLocation,HalfSizes,ObjectTypes,nullptr,ActorsToIgnore,OverlappedActors);

		// Disegna la box per il debug
		UKismetSystemLibrary::DrawDebugBox(World,SpawnLocation,HalfSizes,FColor::Red,SpawnRotation,5.0f,2.0f );

		// Controlla se il risultato del Box Overlap include l'attore specificato
		if (SpawnedActor.IsValidIndex(Index) && !OverlappedActors.Contains(SpawnedActor[Index]) && OverlappedActors.Num() > 0)
		{
			return; // Evita ulteriori azioni se è stato rilevato l'attore
		}
        
		if (SpawnedActor[Index])
		{
			SpawnedActor[Index]->SetActorLocationAndRotation(SpawnLocation,SpawnRotation,false, nullptr,ETeleportType::TeleportPhysics);
		}
		else
		{
			// Spawn the actor
			SpawnedActor[Index] = World->SpawnActor<AActor>(SelectedActors[Index], SpawnLocation, SpawnRotation);
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
		Index = SelectedActors.Num() - 1;
	}
	if (Index > SelectedActors.Num()-1)
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
