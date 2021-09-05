// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "AmmoBox.h"
#include "TimerManager.h"
#include "ParentFirePoint.generated.h"

class UStaticMeshComponent;
class ACannon;
class UHealthComponent;
class UParticleSystemComponent;
class UAudioComponent;

UCLASS()
class TANKOGEDDON_API AParentFirePoint : public APawn, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* BodyMesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* TurretMesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UParticleSystemComponent* DestroyEffect;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UAudioComponent* DestroyAudioEffect;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UArrowComponent* CannonSetupPoint;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UBoxComponent* HitCollider;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    TSubclassOf<ACannon> CannonClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    TSubclassOf<AAmmoBox> AmmoboxClass;
    UPROPERTY()
    ACannon* Cannon;

    FTimerHandle DestroyTimerHandle;

public:	
    AParentFirePoint();

    UFUNCTION()
    virtual void Die();

    UFUNCTION()
    virtual void DamageTaken(float InDamage);

    UFUNCTION()
    void TakeDamage(FDamageData DamageData);

    UFUNCTION()
    void KillExposion();

    UFUNCTION()
    void Fire();
protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
};
