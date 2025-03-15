// Copyright Ricky Everest


#include "AbilitySystem/Data/AttributeInfo.h"

#include "SCR_GameplayTags.h"
#include "AbilitySystem/SCR_AttributeSet.h"


FSCR_AttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FSCR_AttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}

	return FSCR_AttributeInfo();
}
#if WITH_EDITOR
void UAttributeInfo::PopulateDataAsset()
{
	const FSCR_GameplayTags SCR_GameplayTags = FSCR_GameplayTags::Get();
	AttributeInformation.Empty();
	AttributeInformation.SetNumZeroed(SCR_GameplayTags.SCR_TagsContainer.Num());

	for (int i = 0; i < SCR_GameplayTags.SCR_TagsContainer.Num(); i++)
	{
		const FGameplayTag IndexTag = SCR_GameplayTags.SCR_TagsContainer.GetByIndex(i);
		AttributeInformation[i].AttributeTag = IndexTag; // SetAttributeTag

		const FGameplayTagNode* TagNode = UGameplayTagsManager::Get().FindTagNode(IndexTag).Get(); // Get the last node of the gameplay tag
		FString NodeString = FName::NameToDisplayString(TagNode->GetSimpleTagName().ToString(), false); // Get Node Name (Attribute.Primary.Strength returns Strength)

		AttributeInformation[i].AttributeName = FText::FromString(NodeString); //Set Attributes

		//Set Attributes To Get
		for (TFieldIterator<FProperty> It(USCR_AttributeSet::StaticClass()); It; ++It)
		{
			if(FGameplayAttribute::IsGameplayAttributeDataProperty(*It) && FGameplayAttribute(*It).GetName() == TagNode->GetSimpleTagName().ToString())
			{
				AttributeInformation[i].AttributeToGet = FGameplayAttribute(*It);
				break;
			}
		}

		const FName TagName = IndexTag.GetTagName();
		// Outs
		FString TagComment = FString();
		FName TagSource = FName();
		bool bIsTagExplicit = false;
		bool bIsRestrictedTag = false;
		bool bAllowNonRestrictedChildren = false;

		UGameplayTagsManager::Get().GetTagEditorData(
			TagName,
			TagComment,
			TagSource,
			bIsTagExplicit,
			bIsRestrictedTag,
			bAllowNonRestrictedChildren);
		AttributeInformation[i].AttributeDescription = FText::FromString(TagComment); // Set Attribute Description
	}
	
}
#endif

