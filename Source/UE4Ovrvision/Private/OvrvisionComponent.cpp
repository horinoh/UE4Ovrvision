// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Ovrvision.h"
#include "OvrvisionComponent.h"


// Sets default values for this component's properties
UOvrvisionComponent::UOvrvisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOvrvisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (nullptr == OvrvisionInst)
	{
		OvrvisionInst = new OVR::Ovrvision();
		if (OV_RESULT_OK == OvrvisionInst->Open(0, OVR::OV_CAMVGA_FULL, OVR::OV_HMD_OCULUS_DK1))
		{
			if (nullptr == Texture2D)
			{
				const auto Width = OvrvisionInst->GetImageWidth();
				const auto Height = OvrvisionInst->GetImageHeight();
				Texture2D = UTexture2D::CreateTransient(Width << 1, Height);
				if (nullptr != Texture2D)
				{
					Texture2D->UpdateResource();
				}
			}
		}
	}
}

void UOvrvisionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (nullptr != OvrvisionInst)
	{
		if (OVR::OV_CAMOPENED == OvrvisionInst->GetCameraStatus())
		{
			OvrvisionInst->Close();
		}
		delete OvrvisionInst;
		OvrvisionInst = nullptr;
	}
}

// Called every frame
void UOvrvisionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	if (nullptr != OvrvisionInst && OVR::OV_CAMOPENED == OvrvisionInst->GetCameraStatus())
	{
		if (nullptr != Texture2D)
		{
			ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(UpdateTexture2D,
				UOvrvisionComponent*, This, this,
				UTexture2D*, Tex, Texture2D,
				{
					//!< カメラ画像を取得
					//!< Get camera image
					This->OvrvisionInst->PreStoreCamData();
					auto LeftImage = This->OvrvisionInst->GetCamImage(OVR::OV_CAMEYE_LEFT/*, OVR::OV_PSQT_LOW*/);
					auto RightImage = This->OvrvisionInst->GetCamImage(OVR::OV_CAMEYE_RIGHT/*, OVR::OV_PSQT_LOW*/);

					const auto Width = This->OvrvisionInst->GetImageWidth();
					const auto Width2 = Width << 1;
					const auto Height = This->OvrvisionInst->GetImageHeight();
					const auto BPP = This->OvrvisionInst->GetPixelSize();

					//!< カメラ画像は 24ビットカラー(RGB) で取得されるので、32ビットカラー(FColor)配列へ変換する
					//!< Because camera image is 24bit color(RGB), convert to 32bit color(FColor)
					TArray<FColor> Source;
					Source.Reserve(Width2 * Height);
					for (auto i = 0; i < Height; ++i)
					{
						for (auto j = 0; j < Width; ++j)
						{
							Source.Add(FColor(LeftImage[0], LeftImage[1], LeftImage[2]));
							LeftImage += BPP;
						}
						for (auto j = 0; j < Width; ++j)
						{
							Source.Add(FColor(RightImage[0], RightImage[1], RightImage[2]));
							RightImage += BPP;
						}
					}

					//!< テクスチャを更新
					//!< update texture
					const auto Pitch = GPixelFormats[Tex->GetPixelFormat()].BlockBytes * Width2;
					RHIUpdateTexture2D(Tex->Resource->TextureRHI->GetTexture2D(), 0, FUpdateTextureRegion2D(0, 0, 0, 0, Width2, Height), Pitch, reinterpret_cast<const uint8*>(&Source[0]));
				}
			);
		}
	}
}

