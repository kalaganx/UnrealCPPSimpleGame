// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class UNREALCPPSIMPLEGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	// Impostazioni di base
	APlayerPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Funzioni di movimento
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& InputValue);
	UFUNCTION(BlueprintCallable)
	void Jump();
	UFUNCTION(BlueprintCallable)
	void StopJumping();
	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D& InputValue);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "EnchancedInput")
	class UInputMappingContext* InputMapping;
	
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	class UCapsuleComponent* CapsuleComponent;

	FVector CurrentVelocity;
	bool bIsJumping = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpForce = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gravity = -980.0f;

	bool IsGrounded() const;
};
