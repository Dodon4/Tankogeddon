// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class TANKOGEDDON_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
private:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HpBar;
	
public:
	UFUNCTION()
	void SetHpValue(float health);

	void NativeConstruct() override;
};
