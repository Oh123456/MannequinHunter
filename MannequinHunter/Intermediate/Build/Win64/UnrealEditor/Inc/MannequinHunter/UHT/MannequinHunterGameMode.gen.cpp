// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MannequinHunter/MannequinHunterGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMannequinHunterGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	MANNEQUINHUNTER_API UClass* Z_Construct_UClass_AMannequinHunterGameMode();
	MANNEQUINHUNTER_API UClass* Z_Construct_UClass_AMannequinHunterGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MannequinHunter();
// End Cross Module References
	void AMannequinHunterGameMode::StaticRegisterNativesAMannequinHunterGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMannequinHunterGameMode);
	UClass* Z_Construct_UClass_AMannequinHunterGameMode_NoRegister()
	{
		return AMannequinHunterGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMannequinHunterGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMannequinHunterGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MannequinHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMannequinHunterGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MannequinHunterGameMode.h" },
		{ "ModuleRelativePath", "MannequinHunterGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMannequinHunterGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMannequinHunterGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMannequinHunterGameMode_Statics::ClassParams = {
		&AMannequinHunterGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AMannequinHunterGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMannequinHunterGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMannequinHunterGameMode()
	{
		if (!Z_Registration_Info_UClass_AMannequinHunterGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMannequinHunterGameMode.OuterSingleton, Z_Construct_UClass_AMannequinHunterGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMannequinHunterGameMode.OuterSingleton;
	}
	template<> MANNEQUINHUNTER_API UClass* StaticClass<AMannequinHunterGameMode>()
	{
		return AMannequinHunterGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMannequinHunterGameMode);
	AMannequinHunterGameMode::~AMannequinHunterGameMode() {}
	struct Z_CompiledInDeferFile_FID_MannequinHunter_Source_MannequinHunter_MannequinHunterGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MannequinHunter_Source_MannequinHunter_MannequinHunterGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMannequinHunterGameMode, AMannequinHunterGameMode::StaticClass, TEXT("AMannequinHunterGameMode"), &Z_Registration_Info_UClass_AMannequinHunterGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMannequinHunterGameMode), 366733161U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MannequinHunter_Source_MannequinHunter_MannequinHunterGameMode_h_928718528(TEXT("/Script/MannequinHunter"),
		Z_CompiledInDeferFile_FID_MannequinHunter_Source_MannequinHunter_MannequinHunterGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MannequinHunter_Source_MannequinHunter_MannequinHunterGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
