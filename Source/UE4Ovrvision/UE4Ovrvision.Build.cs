// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using Tools.DotNETCommon;

public class UE4Ovrvision : ModuleRules
{
	public UE4Ovrvision(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
															"RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			FileReference FR;
            UProjectInfo.TryGetProjectForTarget("UE4Ovrvision", out FR);
            RulesAssembly RA = RulesCompiler.CreateProjectRulesAssembly(FR);
            var ModulePath = Path.GetDirectoryName(RA.GetModuleFileName(GetType().Name).CanonicalName);
			var ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty"));

			var Name = "ovrvisionsdk_windows";
			var Platform = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
			var LibPath = Path.Combine(ThirdPartyPath, Name, "bin", Platform);
			PublicLibraryPaths.Add(LibPath);

			var LibName = "ovrvision_64" + (Target.Configuration == UnrealTargetConfiguration.Debug ? "d" : "");
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, LibName + ".lib"));
			PublicDelayLoadDLLs.Add(LibName + ".dll");
			PublicDelayLoadDLLs.Add("OpenAL32.dll");
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, Name, "include"));
		}
	}
}
