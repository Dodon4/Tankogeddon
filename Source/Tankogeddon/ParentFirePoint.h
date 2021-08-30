// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "Components/BoxComponent.h"
#include "ParentFirePoint.generated.h"

class UStaticMeshComponent;
class ACannon;
class UHealthComponent;

UCLASS()
class TANKOGEDDON_API AParentFirePoint : public AActor, public IDamageTaker
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
    UArrowComponent* CannonSetupPoint;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UBoxComponent* HitCollider;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    TSubclassOf<ACannon> CannonClass;

    UPROPERTY()
    ACannon* Cannon;

public:	
    AParentFirePoint();

    UFUNCTION()
    virtual void Die();

    UFUNCTION()
    virtual void DamageTaken(float InDamage);

    UFUNCTION()
    void TakeDamage(FDamageData DamageData);
protected:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;
    void Fire();
};
