// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Ovrvision.h"

class FOvrvisionGameModuleImpl : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()
	{
		const auto DllRoot = FPaths::ProjectConfigDir() / TEXT("../ThirdParty/ovrvisionsdk_windows/bin") / (PLATFORM_64BITS ? TEXT("x64/") : TEXT("x86/"));
		FPlatformProcess::PushDllDirectory(*DllRoot);
		{
#if UE_BUILD_DEBUG
			DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + "ovrvision" + (PLATFORM_64BITS ? "_64" : "") + "d.dll")));
#else
			DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + "ovrvision" + (PLATFORM_64BITS ? "_64" : "") + ".dll")));
#endif
			check(nullptr != DllHandles.Last());
			DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + "OpenAL32.dll")));
			check(nullptr != DllHandles.Last());
		}
		FPlatformProcess::PopDllDirectory(*DllRoot);
	}
	virtual void ShutdownModule()
	{
		for (auto i : DllHandles)
		{
			FPlatformProcess::FreeDllHandle(i);
		}
	}

	TArray<void*> DllHandles;
};

IMPLEMENT_PRIMARY_GAME_MODULE( FOvrvisionGameModuleImpl, UE4Ovrvision, "UE4Ovrvision" );
