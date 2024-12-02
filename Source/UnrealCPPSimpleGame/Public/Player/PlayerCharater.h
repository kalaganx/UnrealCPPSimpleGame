// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharater.generated.h"

UCLASS()
class UNREALCPPSIMPLEGAME_API APlayerCharater : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class USpringArmComponent* SpringArm;

protected:
	
	UPROPERTY(EditAnywhere, Category = "EnchancedInput")
	class UInputMappingContext* InputMapping;
	
public:
	// Sets default values for this character's properties
	APlayerCharater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& InputValue);

	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D& InputValue);

	UFUNCTION(BlueprintCallable)
	void Jumping();
};
