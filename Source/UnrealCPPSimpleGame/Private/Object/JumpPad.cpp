// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/JumpPad.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AJumpPad::AJumpPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the block's mesh
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);

	// Create and attach the trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(BlockMesh);

	// Bind the overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Handle overlap
void AJumpPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// Check if the overlapping actor has physics
		UPrimitiveComponent* OtherActorComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
		if (OtherActorComp && OtherActorComp->IsSimulatingPhysics())
		{
			// Apply an upward impulse
			FVector LaunchDirection = FVector(0.0f, 0.0f, 1.0f); // Upwards direction
			OtherActorComp->AddImpulse(LaunchDirection * LaunchForce, NAME_None, true);
		}
		else if (ACharacter* Character = Cast<ACharacter>(OtherActor))
		{
			// For characters, modify their velocity directly
			if (Character->GetCharacterMovement())
			{
				FVector LaunchVelocity = FVector(0.0f, 0.0f, LaunchForce);
				Character->LaunchCharacter(LaunchVelocity, true, true);
			}
		}
	}
}