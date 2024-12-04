#include "Object/PressurePlate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Object/ActivableObject.h"

// Sets default values
APressurePlate::APressurePlate()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach PressurePlateBase
    PressurePlateBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    PressurePlateBase->SetupAttachment(RootComponent);

    // Create and attach PressurePlatePlate
    PressurePlatePlate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate"));
    PressurePlatePlate->SetupAttachment(PressurePlateBase);
    PressurePlateBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Create and attach TriggerBox
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(PressurePlateBase);

    // Bind the overlap event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
    Super::BeginPlay();
    if (PressurePlateBase)
    {
        StartPosition = PressurePlatePlate->GetComponentLocation(); // Correggi la variabile
    }
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor)
    {
        // Check if the overlapping actor has physics
        UPrimitiveComponent* OtherActorComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
        // Verifica se l'attore che entra è il Player Character
        APawn* PlayerPawn = Cast<APawn>(OtherActor);
        if ((OtherActorComp && OtherActorComp->IsSimulatingPhysics())||(PlayerPawn && PlayerPawn->IsPlayerControlled()))
        {
            Activeted = true;
            PressurePlatePlate->SetWorldLocation(PressurePlateBase->GetComponentLocation());
            for (int i = 0; i < ActivetableActors.Num(); i++)
            {
                ActivetableActors[i]->Active(Activeted);
            }
        }
    }
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    UE_LOG(LogTemp, Error, TEXT("dsadad as"));
    if (OtherActor != this)
    {
        Activeted = IsActorInTriggerBox();
        if (!Activeted)
        {
            for (int i = 0; i < ActivetableActors.Num(); i++)
            {
                ActivetableActors[i]->Active(Activeted);
            }
            PressurePlatePlate->SetWorldLocation(StartPosition); // Correggi la variabile
        }
    }
}

bool APressurePlate::IsActorInTriggerBox() const
{
    TArray<AActor*> OverlappingActors;
    if (TriggerBox)
    {
        TriggerBox->GetOverlappingActors(OverlappingActors);
    }
    return OverlappingActors.Num() > 0;
}

