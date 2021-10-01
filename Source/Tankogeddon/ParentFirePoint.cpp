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
#include "AmmoBox.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "HealthBarWidget.h"
#include "Engine/World.h"

void AParentFirePoint::TakeDamage(FDamageData DamageData)
{
	UE_LOG(LogTankogeddon, Warning, TEXT("Turret %s taked damage:%f "), *GetName(), DamageData.DamageValue);
	HealthComponent->TakeDamage(DamageData);
	UHealthBarWidget* myProgress =
		Cast<UHealthBarWidget>(HealthBar->GetUserWidgetObject());
	myProgress->SetHpValue(HealthComponent->GetHealthState());
}

void AParentFirePoint::Die()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestuctionParticleSystem, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestructionSound, GetActorLocation());
	if (AmmoboxClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		GetWorld()->SpawnActor<AAmmoBox>(AmmoboxClass, GetActorTransform(), SpawnParams);
	}
	Destroy();
}

void AParentFirePoint::DamageTaken(float InDamage)
{
	UE_LOG(LogTankogeddon, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), InDamage, HealthComponent->GetHealth());
	if (this == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestuctionParticleSystem, GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DestructionSound, GetActorLocation());

		//UHealthBarWidget* myProgress =
		//	Cast<UHealthBarWidget>(comp->GetUserWidgetObject());
		//myProgress->SetHpValue(1.f);
	}

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
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestuctionParticleSystem, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestructionSound, GetActorLocation());
	if (Cannon)
	{
		Cannon->Destroy();
	}
}
AParentFirePoint::AParentFirePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("BarHP");
	HealthBar->SetWidgetClass(UHealthBarWidget::StaticClass());

	// 
	//DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot effect"));
	//DestroyEffect->SetupAttachment(BodyMesh);

	//DestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio effect"));
	//DestroyAudioEffect->SetupAttachment(BodyMesh);
}
void AParentFirePoint::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}