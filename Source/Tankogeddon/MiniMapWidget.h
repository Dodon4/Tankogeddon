// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/NativeWidgetHost.h"
#include "MiniMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UMiniMapWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UNativeWidgetHost* MiniMap;
public:

	void NativeConstruct() override;
	
};
