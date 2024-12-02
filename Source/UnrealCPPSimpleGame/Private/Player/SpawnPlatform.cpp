// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SpawnPlatform.h"

#include "Components/TextRenderComponent.h"

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
	if (TextRender)
	{
		// Converti l'intero in stringa e poi in FText
		TextRender->SetText(FText::FromString(FString::FromInt(Index)));
	}
	
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
        
		if (SpawnedActor[Index])
		{
			SpawnedActor[Index]->SetActorLocation(SpawnLocation);
			SpawnedActor[Index]->SetActorRotation(SpawnRotation);
		}
		else
		{
			// Spawn the actor
			SpawnedActor[Index] = World->SpawnActor<AActor>(SelectedActor[Index], SpawnLocation, SpawnRotation);
		}
		
	}
}

void USpawnPlatform::ChangeIndex(const float& InputValue=0)
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

void USpawnPlatform::SetList(TArray<UClass*> SObject)
{
	SelectedActor = SObject;
	SpawnedActor.SetNum(SelectedActor.Num());
}
