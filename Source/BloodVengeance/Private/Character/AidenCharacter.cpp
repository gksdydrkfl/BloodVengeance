#include "Character/AidenCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BVPlayerState.h"
#include "GAS/BVAbilitySystemComponent.h"
#include "Player/AidenPlayerController.h"
#include "Item/Weapon/Katana/Katana.h"
#include "MotionWarpingComponent.h"
#include "TargetSystem/TargetSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GroomComponent.h"

AAidenCharacter::AAidenCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 130.f));
	CameraBoom->TargetArmLength = 250.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 45.f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 8.5f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	//GetCharacterMovement()->MaxWalkSpeed = 400.f;

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	TargetSystem = CreateDefaultSubobject<UTargetSystemComponent>(TEXT("TargetSystem"));

	Face = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	Face->SetupAttachment(GetMesh());
	//EnableMasterPose(Face);

	Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	Legs->SetupAttachment(GetMesh());

	Torso = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Torso"));
	Torso->SetupAttachment(GetMesh());

	Feet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
	Feet->SetupAttachment(GetMesh());

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(Face);
	Eyebrows->AttachmentName = FString("head");

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(Face);
	Hair->AttachmentName = FString("head");

	Mustache = CreateDefaultSubobject<UGroomComponent>(TEXT("Mustache"));
	Mustache->SetupAttachment(Face);
	Mustache->AttachmentName = FString("head");

	Beard = CreateDefaultSubobject<UGroomComponent>(TEXT("Beard"));
	Beard->SetupAttachment(Face);
	Beard->AttachmentName = FString("head");


	
}

void AAidenCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();

	AddCharacterAbilities();

	AAidenPlayerController* AidenPlayerController = Cast<AAidenPlayerController>(GetController());

	if (AidenPlayerController)
	{
		AidenPlayerController->CreateHUDWidget();
	}
}

void AAidenCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();

	AAidenPlayerController* AidenPlayerController = Cast<AAidenPlayerController>(GetController());

	if (AidenPlayerController)
	{
		AidenPlayerController->CreateHUDWidget();
	}
}

void AAidenCharacter::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

	AWeapon* Katana = GetWorld()->SpawnActor<AKatana>(KatanaClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Katana)
	{
		Katana->AttachToComponent(GetMesh(), AttachmentTransformRules, FName("WeaponSocket"));
	}

	SetCurrentWeapon(Katana);
}

void AAidenCharacter::InitAbilityActorInfo()
{
	ABVPlayerState* BVPlayerState = GetPlayerState<ABVPlayerState>();

	if (BVPlayerState)
	{
		BVPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BVPlayerState, this);

		AbilitySystemComponent = Cast<UBVAbilitySystemComponent>(BVPlayerState->GetAbilitySystemComponent());

		AttributeSet = BVPlayerState->GetAttributeSet();
	}

	InitializeDefaultAttributes();
}

bool AAidenCharacter::GetTartgetLock()
{
	if (TargetSystem)
	{
		return TargetSystem->GetTargetLock();
	}
	return false;
}

void AAidenCharacter::TargetLockOn()
{
	if (TargetSystem)
	{
		TargetSystem->TargetLockOn();

		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
}

void AAidenCharacter::TargetLockOff()
{
	if (TargetSystem)
	{
		TargetSystem->TargetLockOff();

		GetCharacterMovement()->MaxWalkSpeed = 400.f;
	}
}

void AAidenCharacter::EnableMasterPose(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (SkeletalMeshComponent == nullptr)
	{
		return;
	}

	USkeletalMesh* SkeletalMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();

	if (SkeletalMesh)
	{
		TSubclassOf<UAnimInstance> PostProcessAnimBlueprint = SkeletalMesh->PostProcessAnimBlueprint;
		TSubclassOf<UAnimInstance> AnimClass = SkeletalMeshComponent->AnimClass;

		if(IsValid(PostProcessAnimBlueprint) && IsValid(AnimClass))
		{
			return;
		}
		else
		{
			SkeletalMeshComponent->SetLeaderPoseComponent(GetMesh());
		}
	}
}
