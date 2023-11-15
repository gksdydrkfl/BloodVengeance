#include "Player/AidenPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/BVPlayerState.h"
#include "UI/HUD/BVMainHUD.h"
#include "Player/BVPlayerState.h"
#include "BloodVengeance/DebugMacro.h"
#include "AbilitySystemComponent.h"
#include "Input/BVEnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/BVAbilitySystemComponent.h"
#include "Character/AidenCharacter.h"

#include "BloodVengeance/DebugMacro.h"

AAidenPlayerController::AAidenPlayerController()
{

}

void AAidenPlayerController::BeginPlay()
{
	Super::BeginPlay();

    check(InputMapping);

    if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            InputSystem->AddMappingContext(InputMapping, 0);
        }
    }
}

void AAidenPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (GetASC() == nullptr)
    {
        return;
    }
    GetASC()->AbilityInputTagPressed(InputTag);
}

void AAidenPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
    if (GetASC() == nullptr)
    {
        return;
    }
    GetASC()->AbilityInputTagReleased(InputTag);
}

void AAidenPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
    if (GetASC() == nullptr)
    {
        return;
    }
	GetASC()->AbilityInputTagHeld(InputTag);
}

void AAidenPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UBVEnhancedInputComponent* BVEnhancedInputComponent = CastChecked<UBVEnhancedInputComponent>(InputComponent);

    BVEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAidenPlayerController::Move);
    BVEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAidenPlayerController::Look);
    BVEnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &AAidenPlayerController::LockOn);


    BVEnhancedInputComponent->BindAbilityActions(InputDataAsset, this, 
        &ThisClass::AbilityInputTagPressed,
        &ThisClass::AbilityInputTagReleased,
        &ThisClass::AbilityInputTagHeld);
}

void AAidenPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    //ABVPlayerState* BVPlayerState = GetPlayerState<ABVPlayerState>();
    //if (BVPlayerState)
    //{
    //    BVPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BVPlayerState, InPawn);
    //}
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

void AAidenPlayerController::LockOn(const FInputActionValue& Value)
{
    APawn* PlayerPawn = GetPawn<APawn>();
    if (PlayerPawn)
    {
        AAidenCharacter* AidenCharacter = Cast<AAidenCharacter>(PlayerPawn);
        if (AidenCharacter)
        {
            if (AidenCharacter->GetTartgetLock())
            {
                AidenCharacter->TargetLockOff();
            }
            else
            {
                AidenCharacter->TargetLockOn();
            }
        }
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

UBVAbilitySystemComponent* AAidenPlayerController::GetASC()
{
    if (BVAbilitySystemComponent == nullptr)
    {
        BVAbilitySystemComponent = Cast<UBVAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    }
    return BVAbilitySystemComponent;
}

void AAidenPlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
}
