// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealCPPSimpleGame/Public/Player/PlayerCharater.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharater::APlayerCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

