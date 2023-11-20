// Copyright Epic Games, Inc. All Rights Reserved.

#include "HFSMVisualScriptingEditor.h"

#define LOCTEXT_NAMESPACE "FHFSMVisualScriptingEditorModule"

void FHFSMVisualScriptingEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FHFSMVisualScriptingEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FHFSMVisualScriptingEditorModule::RegisterAssetTypeAction(IAssetTools& assetTools, TSharedRef<IAssetTypeActions> action)
{
	assetTools.RegisterAssetTypeActions(action);
	createdAssetTypeActions.Add(action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHFSMVisualScriptingEditorModule, HFSMVisualScriptingEditor)