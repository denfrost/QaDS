#pragma once

#include "QuestStageEvent.h"
#include "QuestAsset.h"
#include "QuestNode.generated.h"

class UQuestProcessor;

USTRUCT(BlueprintType)
struct DIALOGSYSTEMRUNTIME_API FQuestStageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
	FName SystemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
	FText Caption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stage")
	TMap<FName, FString> AditionalData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions")
	TArray<FName> CheckHasKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions")
	TArray<FName> CheckDontHasKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions")
	TArray<FQuestStageCondition> Predicate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Task")
	TArray<FName> WaitHasKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Task")
	TArray<FName> WaitDontHasKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Task")
	TArray<FQuestStageCondition> WaitPredicate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Failed")
	TArray<FName> FailedIfGiveKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Failed")
	TArray<FName> FailedIfRemoveKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Failed")
	TArray<FQuestStageCondition> FailedPredicate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Failed")
	bool bFailedQuest = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Complete")
	TArray<FName> GiveKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Complete")
	TArray<FName> RemoveKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Complete")
	TArray<FQuestStageEvent> Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Complete")
	EQuestCompleteStatus ChangeQuestState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Complete")
	EQuestCompleteStatus ChangeOderActiveStagesState;
};

UCLASS()
class DIALOGSYSTEMRUNTIME_API UQuestNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UQuestNode*> Childs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FQuestStageInfo Stage;

	UQuestRuntimeNode* Load(UQuestProcessor* processor, UQuestRuntimeAsset* quest);
};

UCLASS()
class DIALOGSYSTEMRUNTIME_API UQuestRuntimeNode : public UObject
{
	GENERATED_BODY()

	void Activate();
	void Failed();
	void Complete();
	void Deactivate();
public:
	UPROPERTY()
	UQuestProcessor* Processor;

	UPROPERTY()
	UQuestRuntimeAsset* OwnerQuest;

	UPROPERTY()
	TArray<UQuestRuntimeNode*> Childs;

	UPROPERTY(BlueprintReadOnly)
	EQuestCompleteStatus Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FQuestStageInfo Stage;

	bool TryComplete();
	bool CkeckForActivate();
	bool CkeckForComplete();
	bool CkeckForFailed();
	void SetStatus(EQuestCompleteStatus NewStatus);
	TArray<UQuestRuntimeNode*> GetNextStage();

	UFUNCTION()
	void OnChangeStoryKey(const FName& key);
};