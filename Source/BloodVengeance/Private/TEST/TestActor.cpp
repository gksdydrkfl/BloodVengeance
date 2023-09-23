// Fill out your copyright notice in the Description page of Project Settings.


#include "TEST/TestActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/BVAttributeSet.h"
#include "Components/SphereComponent.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

	TestValue = 25.f;
}

void ATestActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBVAttributeSet* AuraAttributeSet = Cast<UBVAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBVAttributeSet::StaticClass()));

		UBVAttributeSet* MutableAuraAttributeSet = const_cast<UBVAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetMaxHealth(AuraAttributeSet->GetMaxHealth() + TestValue);
		Destroy();
	}
}

void ATestActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ATestActor::EndOverlap);
}