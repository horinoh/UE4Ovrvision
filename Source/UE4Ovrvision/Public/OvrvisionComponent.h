// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Windows/PreWindowsApi.h"
#include <ovrvision.h>
#include "Windows/PostWindowsApi.h"

#include "Components/ActorComponent.h"
#include "OvrvisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4OVRVISION_API UOvrvisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOvrvisionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	class OVR::Ovrvision* OvrvisionInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Texture)
	UTexture2D* Texture2D;
};
