// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Ovrvision.h"
#include "OvrvisionHUD.h"

#include "OvrvisionComponent.h"

AOvrvisionHUD::AOvrvisionHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OvrvisionComp = ObjectInitializer.CreateDefaultSubobject<UOvrvisionComponent>(this, TEXT("OvrvisionComp"));
}

void AOvrvisionHUD::DrawHUD()
{
	Super::DrawHUD();

	if (nullptr != Canvas)
	{
		const FVector2D ScreenSize(Canvas->SizeX, Canvas->SizeY);
		if (nullptr != OvrvisionComp)
		{
			const auto Texture = OvrvisionComp->Texture2D;
			if(nullptr != Texture)
			{
#if 0
				const FVector2D TextureSize(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight());
				FCanvasTileItem Item((ScreenSize - TextureSize) * 0.5f, Texture->Resource, FLinearColor::White);
#else
				FCanvasTileItem Item(FVector2D::ZeroVector, Texture->Resource, ScreenSize, FLinearColor::White);
#endif
				Item.BlendMode = SE_BLEND_Opaque;
				Canvas->DrawItem(Item);
			}
		}
	}
}