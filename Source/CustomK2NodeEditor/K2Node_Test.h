#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SGraphNode.h"
#include "Engine/MemberReference.h"
#include "K2Node_Test.generated.h"

class FNodeHandlingFunctor;
class FKismetCompilerContext;

UCLASS(BlueprintType, Blueprintable)
class UK2Node_Test : public UK2Node
{
    GENERATED_UCLASS_BODY()

public:
    //~ Begin UEdGraphNode Interface
    virtual void                    AllocateDefaultPins() override;
    virtual FText                   GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    //~ End UEdGraphNode Interface

    //~ Begin UK2Node Interface
    virtual bool                    IsNodePure() const override;
    virtual FNodeHandlingFunctor*   CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override; 
    virtual void                    ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override; 
    virtual void                    GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText                   GetMenuCategory() const override;
    //~ End UK2Node Interface

protected:
    /** Constructing FText strings can be costly, so we cache the node's title */
    FNodeTextCache                  CachedNodeTitle;

private:
    UPROPERTY()
    FName                           SelectedFunctionName;
    UPROPERTY()
    FGuid                           SelectedFunctionGuid;
};