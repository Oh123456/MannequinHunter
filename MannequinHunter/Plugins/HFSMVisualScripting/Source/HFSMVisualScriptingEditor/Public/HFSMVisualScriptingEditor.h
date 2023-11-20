// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "EdGraphUtilities.h"

DECLARE_LOG_CATEGORY_EXTERN(HFSMVisualScriptingEditor, Log, All);

class FHFSMVisualScriptingEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray<TSharedPtr<IAssetTypeActions>> createdAssetTypeActions;

	EAssetTypeCategories::Type HFSMVisualScriptingAssetCategoryBit;

	TSharedPtr<FGraphPanelNodeFactory> graphPanelNodeFactoryHFSMGraph;
};
