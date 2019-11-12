#include "BaseEditorModule.h"
#include "ModuleManager.h"

/// Here add include modules
// ToDo #include 
/// ~Here add include modules

DEFINE_LOG_CATEGORY(LogBaseEditor);

void FBaseEditorModule::StartupModule()
{
    UE_LOG(LogBaseEditor, Display, TEXT("BaseEditorModule -> Startup Module"));

    /// Here add function StartupModule
    // ToDo Code::StartupModule();
    /// ~Here add function StartupModule
}

void FBaseEditorModule::ShutdownModule()
{
    /// Here add function ShutdownModule
    // ToDo Code ::ShutdownModule();
    /// ~Here add function ShutdownModule

    UE_LOG(LogBaseEditor, Display, TEXT("BaseEditorModule -> Shutdown Module"));
}

IMPLEMENT_MODULE(FBaseEditorModule, CustomK2NodeEditor);