
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"



class FHFSMVisualScriptingRuntime : public IModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};


