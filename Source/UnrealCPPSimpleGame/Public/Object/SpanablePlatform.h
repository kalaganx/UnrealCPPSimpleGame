// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpanablePlatform.generated.h"

UCLASS()
class UNREALCPPSIMPLEGAME_API ASpanablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpanablePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxHalfSize = FVector(20.f, 20.f, 20.f);

public:
	UFUNCTION()
	FString GetName();

	UFUNCTION()
	FVector GetBoxHalfSize();
};
