#include "Player/AidenPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/BVPlayerState.h"
#include "UI/HUD/BVMainHUD.h"
#include "BloodVengeance/DebugMacro.h"


AAidenPlayerController::AAidenPlayerController()
{

}

void AAidenPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (!InputMapping.IsNull())
            {
                InputSystem->AddMappingContext(InputMapping, 0);
            }
        }
    }
}

void AAidenPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAidenPlayerController::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAidenPlayerController::Look);
}

void AAidenPlayerController::Move(const FInputActionValue& Value)
{
    const FVector2D MoveVector = Value.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

    const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    APawn* PlayerPawn = GetPawn<APawn>();
    if (PlayerPawn)
    {
        PlayerPawn->AddMovementInput(Forward, MoveVector.Y);
        PlayerPawn->AddMovementInput(Right, MoveVector.X);
    }
}

void AAidenPlayerController::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    APawn* PlayerPawn = GetPawn<APawn>();
    if (PlayerPawn)
    {
        PlayerPawn->AddControllerYawInput(LookAxisVector.X);
        PlayerPawn->AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AAidenPlayerController::CreateHUDWidget()
{
    ABVPlayerState* BVPlayerState = GetPlayerState<ABVPlayerState>();

    if (BVPlayerState)
	{
		BVMainHUD = Cast<ABVMainHUD>(GetHUD());
		if (BVMainHUD)
		{
			BVMainHUD->CreateHUDWidget();

			BVMainHUD->UpdateHealthBar(BVPlayerState->GetHealth() / BVPlayerState->GetMaxHealth());
			BVMainHUD->UpdateStaminaBar(BVPlayerState->GetStamina() / BVPlayerState->GetMaxStamina());
		}
    }
}

void AAidenPlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();


}
