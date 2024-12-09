// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPPSIMPLEGAME_API USpawnPlatform : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
	TArray<UClass*> SelectedActors;
    	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actors")
	TArray<AActor*> SpawnedActor;

	UPROPERTY()
	FVector HalfSizes=FVector(40,40,40);

	UPROPERTY()
	USceneComponent* SpawnPoint;

	UPROPERTY()
	class UTextRenderComponent* TextRender;
	
	UPROPERTY()
	int Index = 0;

public:	
	// Sets default values for this component's properties
	USpawnPlatform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SpawnBloack();

	UFUNCTION()
	void DeletBloack();

	UFUNCTION()
	void ChangeIndex(const int& InputValue);

	UFUNCTION()
	void StartingSet(USceneComponent* SP,UTextRenderComponent* Text);
};
