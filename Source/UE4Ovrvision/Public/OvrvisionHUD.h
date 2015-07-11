// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "OvrvisionHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE4OVRVISION_API AOvrvisionHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AOvrvisionHUD(const FObjectInitializer& ObjectInitializer);
	
	virtual void DrawHUD() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ovrvision)
	class UOvrvisionComponent* OvrvisionComp;
};
