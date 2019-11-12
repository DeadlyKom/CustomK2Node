#pragma once

#include "CoreMinimal.h"
#include "ModuleInterface.h"

CUSTOMK2NODEEDITOR_API DECLARE_LOG_CATEGORY_EXTERN(LogBaseEditor, All, All);

class FBaseEditorModule : public IModuleInterface
{
public:
    /// Begin of IModuleInterface
    //Called right after the module DLL has been loaded and the module object has been created   
    virtual     void StartupModule()    override;
    //Called before the module is unloaded, right before the module object is destroyed.
    virtual     void ShutdownModule()   override;
    /// End of IModuleInterface
};