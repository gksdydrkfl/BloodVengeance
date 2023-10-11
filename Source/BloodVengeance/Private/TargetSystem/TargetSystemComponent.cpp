#include "TargetSystem/TargetSystemComponent.h"
#include "TargetSystem/TargetSystemInterface.h"
#include "EngineUtils.h"
#include "BloodVengeance/DebugMacro.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"

UTargetSystemComponent::UTargetSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bTargetLock = false;
}

void UTargetSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();
	
	if (OwnerActor)
	{
		AController* Controller = Cast<APawn>(OwnerActor)->GetController();
		if (Controller)
		{
			OwnerController = Cast<APlayerController>(Controller);
		}
	}
}

void UTargetSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateControllerRotation();
}

void UTargetSystemComponent::TargetLockOn()
{
	NearTarget = nullptr;

	TArray<AActor*> Actors;

	Actors = GetAllActors();

	if (Actors.Num() <= 0)
	{
		return;
	}

	TArray<AActor*> HitActors;

	for (AActor* Actor : Actors)
	{
		bool bHitTarget = LineTraceForTarget(HitActors, Actor);

		if (bHitTarget)
		{
			HitActors.Add(Actor);
		}
	}

	NearTarget = FindNearTarget(HitActors);

	if (NearTarget == nullptr)
	{
		return;
	}

	SetControllerRotation(true);

	CreateWidgetTargetMark();

	bTargetLock = true;
}

void UTargetSystemComponent::TargetLockOff()
{
	if (LockOnWidgetComponent)
	{
		LockOnWidgetComponent->DestroyComponent();
	}

	SetControllerRotation(false);

	NearTarget = nullptr;

	bTargetLock = false;
}

TArray<AActor*> UTargetSystemComponent::GetAllActors()
{
	TArray<AActor*> Actors;

	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		AActor* Enemy = *Actor;

		if (Enemy->GetClass()->ImplementsInterface(UTargetSystemInterface::StaticClass()))
		{

			ITargetSystemInterface* Inteface = Cast<ITargetSystemInterface>(Enemy);
			if (Inteface->IsTargetable())
			{
				Actors.Add(Enemy);
			}
		}
	}

	return Actors;
}

bool UTargetSystemComponent::LineTraceForTarget(TArray<AActor*>& HitActors, const AActor* Actor)
{
	FHitResult HitResult;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(OwnerActor);

	const FVector Start = OwnerActor->GetActorLocation();

	const FVector End = Actor->GetActorLocation();

	GetWorld()->LineTraceSingleByChannel(HitResult,	Start, End,	ECollisionChannel::ECC_Pawn, Params);

	AActor* HitActor = HitResult.GetActor();

	if (HitActor == Actor)
	{
		return true;
	}

	return false;
}

AActor* UTargetSystemComponent::FindNearTarget(const TArray<AActor*> HitActors)
{
	float ClosestDistance = TargetMaxDistance;

	AActor* ReturnActor = nullptr;

	for (AActor* Actor : HitActors)
	{
		float Distance = GetDistanceForTarget(Actor);

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ReturnActor = Actor;
		}
	}

	return ReturnActor;
}

float UTargetSystemComponent::GetDistanceForTarget(AActor* TargetActor)
{
	const FVector TargetVector = TargetActor->GetActorLocation();
	const FVector OwnerVector = OwnerActor->GetActorLocation();

	return (TargetVector - OwnerVector).Size();
}

void UTargetSystemComponent::SetControllerRotation(bool bValue)
{
	if (OwnerActor == nullptr)
	{
		return;
	}

	if (OwnerController == nullptr)
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if (OwnerPawn == nullptr)
	{
		return;
	}

	OwnerController->SetIgnoreLookInput(bValue);

	OwnerPawn->bUseControllerRotationYaw = bValue;
}

void UTargetSystemComponent::CreateWidgetTargetMark()
{
	if (LockedOnWidgetClass)
	{
		LockOnWidgetComponent = NewObject<UWidgetComponent>(NearTarget, MakeUniqueObjectName(NearTarget, UWidgetComponent::StaticClass(), FName("TargetLockOn")));
		if (LockOnWidgetComponent)
		{
			UMeshComponent* MeshComponent = NearTarget->FindComponentByClass<UMeshComponent>();
			if (MeshComponent)
			{
				LockOnWidgetComponent->SetWidgetClass(LockedOnWidgetClass);
				LockOnWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				LockOnWidgetComponent->SetupAttachment(MeshComponent, FName("pelvis"));
				LockOnWidgetComponent->SetDrawSize(FVector2D(32.f, 32.f));
				LockOnWidgetComponent->RegisterComponent();
			}
		}
	}
}

void UTargetSystemComponent::UpdateControllerRotation()
{
	if (OwnerActor == nullptr)
	{
		return;
	}
	if (NearTarget == nullptr)
	{
		return;
	}
	if (OwnerController == nullptr)
	{
		return;
	}

	FVector Start = OwnerActor->GetActorLocation();
	FVector End = NearTarget->GetActorLocation();
	FVector Direction = (End - Start).GetSafeNormal();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	const float Distance = (NearTarget->GetActorLocation() - OwnerActor->GetActorLocation()).Size();
	if (Distance > TargetMaxDistance)
	{
		TargetLockOff();

		return;
	}
	const float PitchValue = (Distance * PitchDistanceCoefficient + PitchDistanceOffset) * -1.f;
	const float PitchOffset = FMath::Clamp(PitchValue, PitchMin, PitchMax);

	NewRotation.Pitch = PitchOffset;

	FRotator CurrnetRotation = OwnerController->GetControlRotation();

	const FRotator InterpRotation = FMath::RInterpTo(CurrnetRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 3.f);

	OwnerController->SetControlRotation(InterpRotation);
}

