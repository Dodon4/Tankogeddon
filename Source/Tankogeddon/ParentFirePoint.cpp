// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentFirePoint.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "Tankogeddon.h"

void AParentFirePoint::TakeDamage(FDamageData DamageData)
{
	UE_LOG(LogTankogeddon, Warning, TEXT("Turret %s taked damage:%f "), *GetName(), DamageData.DamageValue);
	HealthComponent->TakeDamage(DamageData);
}

void AParentFirePoint::Die()
{
	Destroy();
}

void AParentFirePoint::DamageTaken(float InDamage)
{
	UE_LOG(LogTankogeddon, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), InDamage, HealthComponent->GetHealth());
}
void AParentFirePoint::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, Params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
void AParentFirePoint::Destroyed()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
}
AParentFirePoint::AParentFirePoint()
{

}