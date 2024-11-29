// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCPPSimpleGame/Public/Player/PlayerCharater.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharater::APlayerCharater()
{
    // Enable ticking every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach SpringArm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true; // Camera follows controller rotation

    // Create and attach Camera
    Camera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
    Camera->SetupAttachment(SpringArm);

    // Create and attach the SpawnPoint component
    TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
    TextRender->SetupAttachment(RootComponent);

    // Create and attach the SpawnPoint component
    SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
    SpawnPoint->SetupAttachment(RootComponent);

    // Enable character rotation based on camera rotation
    bUseControllerRotationYaw = true; // Allow character to rotate with yaw input
    GetCharacterMovement()->bOrientRotationToMovement = true; // Allow movement to control rotation
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
    Super::BeginPlay();

    SpawnedActor.SetNum(SelectedActor.Num());
    if (TextRender)
    {
        // Converti l'intero in stringa e poi in FText
        TextRender->SetText(FText::FromString(FString::FromInt(Index)));
    }
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

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMapping, 0);
        }
    }
}

void APlayerCharater::Move(const FVector2D& InputValue)
{
    if (IsValid(Controller))
    {
        const FRotator CameraRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, CameraRotation.Yaw, 0); // Align rotation to camera yaw

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, InputValue.Y); // Forward/backward movement
        AddMovementInput(RightDirection, InputValue.X);   // Left/right movement
    }
}

void APlayerCharater::Look(const FVector2D& InputValue)
{
    if (IsValid(Controller))
    {
        // Apply mouse input to character rotation
        AddControllerYawInput(InputValue.X);  // Horizontal mouse movement rotates camera yaw
        AddControllerPitchInput(InputValue.Y); // Vertical mouse movement adjusts camera pitch
    }
}

void APlayerCharater::Jumping()
{
    ACharacter::Jump();
}

void APlayerCharater::SpawnBloack()
{
    if (SelectedActor.Num() == 0 || !SelectedActor.IsValidIndex(Index)) // Check if the ActorClass is valid
    {
        UE_LOG(LogTemp, Error, TEXT("No ActorClass provided for spawning!"));
        return;
    }

    if (!SpawnPoint)
    {
        UE_LOG(LogTemp, Error, TEXT("SpawnPoint is null!"));
        return;
    }

    // Get the world context
    UWorld* World = GetWorld();
    if (World)
    {
        // Spawn parameters
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // Get the spawn location and rotation from the SpawnPoint
        FVector SpawnLocation = SpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = SpawnPoint->GetComponentRotation();
        
        if (SpawnedActor[Index])
        {
            SpawnedActor[Index]->Destroy();
        }
        // Spawn the actor
        SpawnedActor[Index] = World->SpawnActor<AActor>(SelectedActor[Index], SpawnLocation, SpawnRotation, SpawnParams);
    }
}

void APlayerCharater::ChangeIndex(const float& InputValue)
{
    Index = Index + InputValue;
    if (Index < 0)
    {
        Index = SelectedActor.Num() - 1;
    }
    if (Index > SelectedActor.Num()-1)
    {
        Index = 0;
    }
    if (TextRender)
    {
        // Converti l'intero in stringa e poi in FText
        TextRender->SetText(FText::FromString(FString::FromInt(Index)));
    };
}
