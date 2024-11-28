// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object/ActivableObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class UNREALCPPSIMPLEGAME_API APressurePlate : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool Activeted = false;
	
	UPROPERTY()
	FVector StartPosition;
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	UStaticMeshComponent* PressurePlateBase;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	UStaticMeshComponent* PressurePlatePlate;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UBoxComponent* TriggerBox;


	
	// Function for handling overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	bool IsActorInTriggerBox() const;

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
    	TArray<AActivableObject*> ActivetableActors;
};
