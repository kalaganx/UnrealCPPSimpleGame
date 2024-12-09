// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SpanablePlatform.h"

// Sets default values
ASpanablePlatform::ASpanablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpanablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpanablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ASpanablePlatform::GetName()
{
	return Name;
}

FVector ASpanablePlatform::GetBoxHalfSize()
{
	return BoxHalfSize;
}

