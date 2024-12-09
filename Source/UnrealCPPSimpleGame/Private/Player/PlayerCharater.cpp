// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCPPSimpleGame/Public/Player/PlayerCharater.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SpawnPlatform.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



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

    TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
    TextRender->SetupAttachment(RootComponent);

    SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
    SpawnPoint->SetupAttachment(RootComponent);

    // Enable character rotation based on camera rotation
    bUseControllerRotationYaw = true; // Allow character to rotate with yaw input
    GetCharacterMovement()->bOrientRotationToMovement = true; // Allow movement to control rotation

    SpawnPlatform = CreateDefaultSubobject<USpawnPlatform>("SpawnPlatform");
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
    Super::BeginPlay();
    SetSetting();
    CreateWidgetP();
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

void APlayerCharater::SpawnB()
{
    if (!SpawnPlatform) return;
    FVector StPos = this->GetActorLocation();
    SpawnPlatform->SpawnBloack();
    if (GetWorld())
    {
        // Crea un Timer Delegate per passare i parametri
        FTimerDelegate TimerDelegate;
        TimerDelegate.BindUFunction(this, FName("ResetPosition"),StPos);

        // Configura il timer con il delegate
        GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,0.01f,false);
    }
}

void APlayerCharater::DestroyB()
{
    if (!SpawnPlatform) return;
    SpawnPlatform->DeletBloack();
}

void APlayerCharater::ChangeIndex(int i)
{
    if (!SpawnPlatform) return;
    SpawnPlatform->ChangeIndex(i);
}

void APlayerCharater::ResetPosition(FVector StartingPosition)
{
    this->SetActorLocation(StartingPosition);
}

void APlayerCharater::SetSetting()
{
    if (!SpawnPlatform) return;
    SpawnPlatform -> StartingSet(SpawnPoint,TextRender);
    SpawnPlatform -> ChangeIndex(0);
}

void APlayerCharater::CreateWidgetP()
{
    if (!WidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("WidgetClass non è stato assegnato!"));
        return;
    }
    
    UWorld* World = GetWorld();
    if (!World) return;

    // Crea il widget
    UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(World, WidgetClass);
    if (WidgetInstance)
    {
        // Aggiungi il widget alla viewport
        WidgetInstance->AddToViewport();

        // Log di debug
        UE_LOG(LogTemp, Warning, TEXT("Widget WBP_Istruzioni aggiunto alla viewport."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Impossibile creare l'istanza del widget."));
    }
}
