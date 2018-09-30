#pragma once

#include "EngineUtils.h"
#include "Components/ActorComponent.h"
#include "QuestNode.h"
#include "QuestProcessor.generated.h"

class UQuestAsset;
class UQuestRuntimeAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestStartSignature, UQuestRuntimeAsset*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestStageCompleteSignature, UQuestRuntimeAsset*, Quest, FQuestStageInfo, Stage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestEndSignature, UQuestRuntimeAsset*, Quest, EQuestCompleteStatus, QuestStatus);

UCLASS()
class DIALOGSYSTEMRUNTIME_API UQuestProcessor : public UObject
{
	GENERATED_BODY()

	TArray<UQuestRuntimeAsset*> archiveQuests;
	TArray<UQuestRuntimeAsset*> activeQuests;
	bool bIsResetBegin;

public:
	UPROPERTY(BlueprintAssignable, Category = "Gameplay|Quest")
	FQuestStartSignature OnQuestStart;

	UPROPERTY(BlueprintAssignable, Category = "Gameplay|Quest")
	FQuestStageCompleteSignature OnStageComplete;

	UPROPERTY(BlueprintAssignable, Category = "Gameplay|Quest")
	FQuestEndSignature OnQuestEnd;

	UPROPERTY(BlueprintReadOnly)
	UStoryKeyManager* StoryKeyManager;

	UPROPERTY(BlueprintReadOnly)
	UStoryTriggerManager* StoryTriggerManager;

	UFUNCTION(BlueprintPure, Category = "Gameplay|Quest")
	static UQuestProcessor* GetQuestProcessor();

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Quest")
	void StartQuest(TAssetPtr<UQuestAsset> QuestAsset);

	void CompleteStage(UQuestRuntimeNode* Stage);
	void WaitStage(UQuestRuntimeNode* Stage);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Quest")
	void EndQuest(UQuestRuntimeAsset* Quest, EQuestCompleteStatus QuestStatus);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Quest")
	TArray<UQuestRuntimeAsset*> GetQuests(EQuestCompleteStatus FilterStatus) const;

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Quest")
	void Reset();
};
