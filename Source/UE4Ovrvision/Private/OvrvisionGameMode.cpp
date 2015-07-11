// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Ovrvision.h"
#include "OvrvisionGameMode.h"

#include "OvrvisionHUD.h"

AOvrvisionGameMode::AOvrvisionGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HUDClass = AOvrvisionHUD::StaticClass();
}