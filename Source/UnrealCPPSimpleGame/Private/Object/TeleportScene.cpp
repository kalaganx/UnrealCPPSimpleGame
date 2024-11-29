// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/TeleportScene.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATeleportScene::ATeleportScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach PressurePlateBase
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	// Create and attach TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Base);

	// Bind the overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportScene::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATeleportScene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportScene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportScene::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (PlayerPawn && PlayerPawn->IsPlayerControlled())
	{
		if (Scene.IsNone())
		{
			UE_LOG(LogTemp, Warning, TEXT("Il nome del livello non è valido."));
			return;
		}
	}
	
	// Carica il livello specificato
	UGameplayStatics::OpenLevel(GetWorld(), Scene);
}
