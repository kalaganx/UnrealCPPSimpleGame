#include "Player/PlayerPawn.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


class UEnhancedInputLocalPlayerSubsystem;
// Sets default values
APlayerPawn::APlayerPawn()
{
 // Impostazioni di base
    PrimaryActorTick.bCanEverTick = true;
    
    // Componente di collisione
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = CapsuleComponent;

    // Mesh
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    // Creazione e configurazione dello SpringArm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true; // La telecamera segue la rotazione del Pawn

    // Creazione e configurazione della telecamera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Componente di movimento
    FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
    
    // Possesso del giocatore
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Applicazione della gravità se non è a terra
    if (!IsGrounded())
    {
       CurrentVelocity.Z += Gravity * DeltaTime;
    }
    else
    {
        if (!bIsJumping)
        {
            CurrentVelocity.Z = 0+JumpForce;
        }
        else
        {
            CurrentVelocity.Z = 0;
        }
    }

    // Movimento del Pawn
    FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
    SetActorLocation(NewLocation);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void APlayerPawn::Move(const FVector2D& InputValue)
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

void APlayerPawn::Jump()
{
    if (IsGrounded() && !bIsJumping)
    {
        bIsJumping = true;
        CurrentVelocity.Z = JumpForce; // Imposta la velocità del salto
    }
}

void APlayerPawn::StopJumping()
{
    if (bIsJumping)
    {
        bIsJumping = false;
    }
}

bool APlayerPawn::IsGrounded() const
{
    FVector Start = GetActorLocation();
    FVector End = Start - FVector(0.f, 0.f, 100.f); // Piccolo raggio per il controllo del terreno
    float Radius = 50.f;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Ignora il Pawn stesso

    // Esegui Sphere Trace
    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeSphere(Radius),
        QueryParams
    );

    // Debug visivo (opzionale)
#if WITH_EDITOR
    FColor TraceColor = bHit ? FColor::Green : FColor::Red;
    DrawDebugSphere(GetWorld(), Start, Radius, 12, TraceColor, false, 1.0f);
    DrawDebugLine(GetWorld(), Start, End, TraceColor, false, 1.0f, 0, 2.0f);
#endif

    return bHit;
}

void APlayerPawn::Look(const FVector2D& InputValue)
{
    if (IsValid(Controller))
    {
        // Apply mouse input to character rotation
        AddControllerYawInput(InputValue.X);  // Horizontal mouse movement rotates camera yaw
        AddControllerPitchInput(InputValue.Y); // Vertical mouse movement adjusts camera pitch
    }
}