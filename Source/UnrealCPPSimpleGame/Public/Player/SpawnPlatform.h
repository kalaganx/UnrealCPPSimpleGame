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
	TArray<UClass*> SelectedActor;
    	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actors")
	TArray<AActor*> SpawnedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnBloack();

	UFUNCTION(BlueprintCallable)
	void ChangeIndex(const float& InputValue);

	UFUNCTION(BlueprintCallable)
	void SetList(TArray<UClass*> SObject);
};
