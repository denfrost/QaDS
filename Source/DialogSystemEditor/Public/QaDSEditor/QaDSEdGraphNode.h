#pragma once

#include "EdGraph/EdGraphNode.h"
#include "QaDSEdGraphNode.generated.h"

class UEdGraphPin;
class FXmlNode;

class DIALOGSYSTEMEDITOR_API FNodePropertyObserver
{
public:
	virtual void OnPropertyChanged(class UEdGraphNode* Sender, const FName& PropertyName) = 0;
};

UCLASS()
class DIALOGSYSTEMEDITOR_API UQaDSEdGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdGraphPin* InputPin;	//todo:: remove
	UEdGraphPin* OutputPin;

	TSharedPtr<FNodePropertyObserver> PropertyObserver;

	virtual UObject* GetCompile() { return NULL; } // todo:: remove this
	//virtual UQaDSEdGraphNode* Compile(UQaDSEdGraphNode* owner) {} //todo:: compile in virtual methods
	virtual void ResetCompile() {}
	virtual int GetOrder() const;
	TArray<UQaDSEdGraphNode*> GetChildNodes() const;

	virtual FString SaveToXml(int tabLevel) const;
	virtual void LoadInXml(FXmlNode* xmlNode, const TMap<FString, UQaDSEdGraphNode*>& nodeById);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
};
