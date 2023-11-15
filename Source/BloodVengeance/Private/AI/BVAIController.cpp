#include "AI/BVAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Damage.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Enemy/Enemy.h"

#include "BloodVengeance/DebugMacro.h"

ABVAIController::ABVAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(Blackboard);
	BehaviorComponent = CreateDefaultSubobject< UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	check(BehaviorComponent);

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	AISight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISight"));
	AISight->SightRadius = 1000;
	AISight->LoseSightRadius = 1200;
	AISight->SetMaxAge(5.f);
	AISight->PeripheralVisionAngleDegrees = 60.0f;
	AISight->DetectionByAffiliation.bDetectEnemies = true;
	AISight->DetectionByAffiliation.bDetectNeutrals = true;
	AISight->DetectionByAffiliation.bDetectFriendlies = true;

	AIHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AIHearing"));
	AIHearing->HearingRange = 1000;
	AIHearing->SetMaxAge(5.f);
	AIHearing->DetectionByAffiliation.bDetectEnemies = true;
	AIHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AIHearing->DetectionByAffiliation.bDetectFriendlies = true;

	AIDamage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("AIDamage"));
	AIDamage->SetMaxAge(5.f);

	PerceptionComponent->ConfigureSense(*AISight);
	PerceptionComponent->ConfigureSense(*AIHearing);
	PerceptionComponent->ConfigureSense(*AIDamage);
}

void ABVAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemy* Enemy = Cast<AEnemy>(InPawn);
	if (Enemy == nullptr)
	{
		return;
	}

	UBehaviorTree* EnemyBehaviorTree = Enemy->GetEnemyBehaviorTree();

	if (EnemyBehaviorTree == nullptr)
	{
		return;
	}

	GetBlackboardComponent()->InitializeBlackboard(*EnemyBehaviorTree->GetBlackboardAsset());
	RunBehaviorTree(EnemyBehaviorTree);

	GetBlackboardComponent()->SetValueAsFloat(FName("AttackRadius"), Enemy->GetAttackRadius());
	GetBlackboardComponent()->SetValueAsFloat(FName("DefaultRadius"), Enemy->GetDefaultAttackRadius());
}

void ABVAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionComponent == nullptr)
	{
		return;
	}

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABVAIController::OnPerceptionSenceUpdate);
}


void ABVAIController::OnPerceptionSenceUpdate(const TArray<AActor*>& UpdatedActors)
{
	FAIStimulus AIStimulus;

	for (AActor* Actor : UpdatedActors)
	{
		if (CanSenceActor(Actor, EAISense::AIS_Sight, AIStimulus))
		{
			HandleSensedSight(Actor);
			Debug::Log(FString("Sight"));
		}
		if (CanSenceActor(Actor, EAISense::AIS_Hearing, AIStimulus))
		{
			HandleSensedSound(AIStimulus.StimulusLocation);
			Debug::Log(FString("Hearing"));
		}
		if (CanSenceActor(Actor, EAISense::AIS_Damage, AIStimulus))
		{
			Debug::Log(FString("Damage"));
		}
	}
}

bool ABVAIController::CanSenceActor(AActor* Actor, const EAISense& InAISence, FAIStimulus& AIStimulus)
{
	if (PerceptionComponent == nullptr)
	{
		return false;
	}

	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;

	bool ReturnValue = PerceptionComponent->GetActorsPerception(Actor, ActorPerceptionBlueprintInfo);

	if (ReturnValue)
	{
		for (const FAIStimulus& AIStimuli : ActorPerceptionBlueprintInfo.LastSensedStimuli)
		{
			TSubclassOf<UAISense> AISense = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimuli);

			UClass* SenceClass = nullptr;

			switch (InAISence)
			{
			case EAISense::AIS_Sight:
				SenceClass = UAISense_Sight::StaticClass();
				break;
			case EAISense::AIS_Hearing:
				SenceClass = UAISense_Hearing::StaticClass();
				break;
			case EAISense::AIS_Damage:
				SenceClass = UAISense_Damage::StaticClass();
				break;
			}
			if (AISense == SenceClass)
			{
				AIStimulus = AIStimuli;
				return AIStimuli.WasSuccessfullySensed();
			}
		}
	}
	return false;
}

void ABVAIController::SetAIStatePassive(const EAIState& InAIState)
{
	EnemyAIState = InAIState;

	AttackTarget = nullptr;

	GetBlackboardComponent()->SetValueAsObject(FName("AttackTarget"), AttackTarget);
	GetBlackboardComponent()->SetValueAsEnum(FName("State"), (uint8)EnemyAIState);
}

void ABVAIController::SetAIStateAttacking(AActor* SightActor)
{
	EnemyAIState = EAIState::AIS_Attacking;

	AttackTarget = SightActor;

	GetBlackboardComponent()->SetValueAsObject(FName("AttackTarget"), AttackTarget);
	GetBlackboardComponent()->SetValueAsEnum(FName("State"), (uint8)EnemyAIState);
}

void ABVAIController::SetAIStateSight(const EAIState& InAIState, AActor* SightActor)
{
	EnemyAIState = InAIState;

	AttackTarget = SightActor;

	GetBlackboardComponent()->SetValueAsObject(FName("AttackTarget"), AttackTarget);
	GetBlackboardComponent()->SetValueAsEnum(FName("State"), (uint8)EnemyAIState);
}

void ABVAIController::SetAIStateSound(const EAIState& InAIState, const FVector& StimulusLocation)
{
	EnemyAIState = InAIState;

	GetBlackboardComponent()->SetValueAsEnum(FName("State"), (uint8)EnemyAIState);
	GetBlackboardComponent()->SetValueAsVector(FName("PointOfInterest"), StimulusLocation);
}

void ABVAIController::SetAIStateDamage(const EAIState& InAIState)
{
	EnemyAIState = InAIState;

	GetBlackboardComponent()->SetValueAsEnum(FName("State"), (uint8)EnemyAIState);
}

void ABVAIController::HandleSensedSight(AActor* SightActor)
{
	switch (EnemyAIState)
	{
	case EAIState::AIS_Passive:
	case EAIState::AIS_Investigating:
		SetAIStateSight(EAIState::AIS_Attacking, SightActor);
		break;
	}
}

void ABVAIController::HandleSensedSound(const FVector& StimulusLocation)
{
	switch (EnemyAIState)
	{
	case EAIState::AIS_Passive:
	case EAIState::AIS_Investigating:
		SetAIStateSound(EAIState::AIS_Investigating, StimulusLocation);
		break;
	}
}

void ABVAIController::HandleSensedDamage()
{
	switch (EnemyAIState)
	{
	case EAIState::AIS_Passive:
	case EAIState::AIS_Investigating:
		SetAIStateDamage(EAIState::AIS_Attacking);
		break;
	}
}
