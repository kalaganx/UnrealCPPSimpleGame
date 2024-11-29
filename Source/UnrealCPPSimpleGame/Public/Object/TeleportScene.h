// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportScene.generated.h"

UCLASS()
class UNREALCPPSIMPLEGAME_API ATeleportScene : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportScene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UBoxComponent* TriggerBox;

	// Function for handling overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName  Scene;
};
