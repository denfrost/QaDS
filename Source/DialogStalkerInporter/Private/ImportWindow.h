#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class UDialogPhraseNode;
class UDialogAsset;
class SEditableTextBox;
class FXmlNode;

class SImportWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SImportWindow){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply HandleImportButton();

private:
	TMap<FString, FText> localize;

	TSharedPtr<SEditableTextBox> gamedataPathTextBox;
	TSharedPtr<SEditableTextBox> dialogIdMaskTextBox;
	TSharedPtr<SEditableTextBox> localNameTextBox;
	TSharedPtr<SEditableTextBox> outputPathTextBox;

	TArray<FString> GetFilesInDir(FString path, FString mask);
	UDialogAsset* CreateDialogAsset(const FString& path, const FString& name);
	void ImportNodes(UDialogAsset* asset, FXmlNode* dialogNode);
	void SetNodeSource(TArray<UDialogPhraseNode*>& handled, UDialogPhraseNode* phrase, bool isParentActor);
	FText GetLocalizeString(FString keyName);
	void LoadLocalize(FString path);
};