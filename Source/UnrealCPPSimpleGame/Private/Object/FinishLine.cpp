// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/FinishLine.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach PressurePlateBase
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);
	Base->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create and attach TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Base);

	// Bind the overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// Verifica se l'attore che entra è un giocatore
		APawn* PlayerPawn = Cast<APawn>(OtherActor);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController && PlayerPawn == PlayerController->GetPawn())
		{
			// Chiama la funzione per chiudere il gioco
			UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
		}
	}
}