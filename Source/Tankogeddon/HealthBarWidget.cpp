// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHpValue(float health)
{
   HpBar->SetPercent(health);
}
void UHealthBarWidget::NativeConstruct()
{
}