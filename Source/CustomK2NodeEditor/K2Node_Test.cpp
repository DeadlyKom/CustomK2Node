#include "K2Node_Test.h"

#include "EdGraphSchema_K2.h"
#include "Engine/MemberReference.h"
#include "EditorCategoryUtils.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompiler.h"
#include "KismetCompilerMisc.h"

#define LOCTEXT_NAMESPACE "CustomNode"

class FKCHandler_Test : public FNodeHandlingFunctor
{
public:
    FKCHandler_Test(FKismetCompilerContext& InCompilerContext)
        : FNodeHandlingFunctor(InCompilerContext)
    {
    }
    virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
    {
        // For imperative nodes, make sure the exec function was actually triggered and not just included due to an output data dependency
        FEdGraphPinType ExpectedExecPinType;
        ExpectedExecPinType.PinCategory = UEdGraphSchema_K2::PC_Exec;

        UEdGraphPin* ExecTriggeringPin = Context.FindRequiredPinByName(Node, UEdGraphSchema_K2::PN_Execute, EGPD_Input);
        if ((ExecTriggeringPin == NULL) || !Context.ValidatePinType(ExecTriggeringPin, ExpectedExecPinType))
        {
            CompilerContext.MessageLog.Error(*LOCTEXT("NoValidExecutionPinForBranch_Error", "@@ must have a valid execution pin @@").ToString(), Node, ExecTriggeringPin);
            return;
        }
        else if (ExecTriggeringPin->LinkedTo.Num() == 0)
        {
            CompilerContext.MessageLog.Warning(*LOCTEXT("NodeNeverExecuted_Warning", "@@ will never be executed").ToString(), Node);
            return;
        }

        // Generate the output impulse from this node
        UEdGraphPin* ThenPin = Context.FindRequiredPinByName(Node, UEdGraphSchema_K2::PN_Then, EGPD_Output);
        if (Context.ValidatePinType(ThenPin, ExpectedExecPinType))
        {
            FBlueprintCompiledStatement& GotoThen = Context.AppendStatementForNode(Node);
            //GotoThen.Type = KCST_UnconditionalGoto;
            //GotoThen.LHS = *CondTerm;
            //Context.GotoFixupRequestMap.Add(&GotoThen, ThenPin);
        }
        else
        {
            //CompilerContext.MessageLog.Error(*LOCTEXT("ResolveTermPassed_Error", "Failed to resolve term passed into @@").ToString(), CondPin);
        }
    }
};

struct FK2Node_Test_Helper
{
    static FName DelegateInputName;
};

FName FK2Node_Test_Helper::DelegateInputName(TEXT("InputDelegate"));

UK2Node_Test::UK2Node_Test(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UK2Node_Test::AllocateDefaultPins()
{
    CreatePin(EEdGraphPinDirection::EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EEdGraphPinDirection::EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

    //UClass* PropertyOwnerClass = DelegateReference.GetMemberParentClass(GetBlueprintClassFromNode());
    //if (PropertyOwnerClass != nullptr)
    //{
    //    PropertyOwnerClass = PropertyOwnerClass->GetAuthoritativeClass();
    //}
    //const UBlueprint* Blueprint = GetBlueprint();
    //
    //const bool bUseSelf = Blueprint && (PropertyOwnerClass == Blueprint->GeneratedClass);
    //
    //UEdGraphPin* SelfPin = NULL;
    //if (bUseSelf)
    //{
    //    SelfPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UEdGraphSchema_K2::PSC_Self, UEdGraphSchema_K2::PN_Self);
    //}
    //else
    //{
    //    SelfPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, PropertyOwnerClass, UEdGraphSchema_K2::PN_Self);
    //}
    //
    //if (SelfPin)
    //{
    //    SelfPin->PinFriendlyName = NSLOCTEXT("K2Node", "BaseMCDelegateSelfPinName", "Target");
    //}

    //if (UEdGraphPin* DelegatePin = CreatePin(EEdGraphPinDirection::EGPD_Input, UEdGraphSchema_K2::PC_Delegate, FK2Node_Test_Helper::DelegateInputName)) {
    //    DelegatePin->PinFriendlyName = NSLOCTEXT("K2Node", "CreateDelegate_DelegateOutName", "Event");
    //}

    Super::AllocateDefaultPins();
}

FText UK2Node_Test::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return NSLOCTEXT("K2Node", "TestNode", "Test Node With Output Event");
}

bool UK2Node_Test::IsNodePure() const
{
    return false;
}

FNodeHandlingFunctor* UK2Node_Test::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
    return new FKCHandler_Test(CompilerContext);
}

void UK2Node_Test::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);
}

void UK2Node_Test::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* NodeClass = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(NodeClass))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(NodeClass);
        check(NodeSpawner);
        ActionRegistrar.AddBlueprintAction(NodeClass, NodeSpawner);
    }
}

FText UK2Node_Test::GetMenuCategory() const
{
    return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::Utilities);
}

#undef LOCTEXT_NAMESPACE
