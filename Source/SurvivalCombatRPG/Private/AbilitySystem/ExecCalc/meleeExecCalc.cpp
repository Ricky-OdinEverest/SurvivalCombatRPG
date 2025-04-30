// Copyright Ricky Everest


#include "AbilitySystem/ExecCalc/meleeExecCalc.h"
#include "AbilitySystem/SCR_AttributeSet.h"
#include "SCR_GameplayTags.h"
#include "SCR_DebugHelper.h"
 
 struct FMeleeDamageCapture
 {
 	DECLARE_ATTRIBUTE_CAPTUREDEF(MeleeAttack)
	 DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
 	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage)
 
	 FMeleeDamageCapture()
 	{
 		 DEFINE_ATTRIBUTE_CAPTUREDEF(USCR_AttributeSet,MeleeAttack,Source,false)
		 DEFINE_ATTRIBUTE_CAPTUREDEF(USCR_AttributeSet,Defense,Target,false)
 		DEFINE_ATTRIBUTE_CAPTUREDEF(USCR_AttributeSet,IncomingDamage,Target,false)
	 }
 };
 
static const FMeleeDamageCapture& GetPlayerDamageCapture()
{
	static FMeleeDamageCapture MeleeDamageCapture;
	return MeleeDamageCapture;
}
 
UmeleeExecCalc::UmeleeExecCalc()
{
	/*Slow way of doing capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	//);
 
	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);
 
	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);
 
	RelevantAttributesToCapture.Add(GetPlayerDamageCapture().MeleeAttackDef);
	RelevantAttributesToCapture.Add(GetPlayerDamageCapture().DefenseDef);
	RelevantAttributesToCapture.Add(GetPlayerDamageCapture().IncomingDamageDef);
}

void UmeleeExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
 	
	/*EffectSpec.GetContext().GetSourceObject();
	EffectSpec.GetContext().GetAbility();
	EffectSpec.GetContext().GetInstigator();
	EffectSpec.GetContext().GetEffectCauser();*/
 
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
 
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPlayerDamageCapture().MeleeAttackDef,EvaluateParameters,SourceAttackPower);
	/*Debug::Print(TEXT("SourceAttackPower"),SourceAttackPower);*/
	float BaseDamage = 0.f;
	int32 UsedLightAttckComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
 
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(SCR_GameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			/*Debug::Print(TEXT("BaseDamage"),BaseDamage);*/
		}
 
		if (TagMagnitude.Key.MatchesTagExact(SCR_GameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttckComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedLightAttckComboCount"),UsedLightAttckComboCount);*/
		}
 
		if (TagMagnitude.Key.MatchesTagExact(SCR_GameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedHeavyAttackComboCount"),UsedHeavyAttackComboCount);*/
		}
	}
 
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPlayerDamageCapture().DefenseDef,EvaluateParameters,TargetDefensePower);
	/*Debug::Print(TEXT("TargetDefensePower"),TargetDefensePower);*/
 
	if (UsedLightAttckComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttckComboCount - 1) * 0.05 + 1.f;
 
		BaseDamage *= DamageIncreasePercentLight;
		/*Debug::Print(TEXT("ScaledBaseDamageLight"),BaseDamage);*/
	}
 
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
 
		BaseDamage *= DamageIncreasePercentHeavy;
		/*Debug::Print(TEXT("ScaledBaseDamageHeavy"),BaseDamage);*/
	}
 
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	/*Debug::Print(TEXT("FinalDamageDone"),FinalDamageDone);*/
 
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetPlayerDamageCapture().IncomingDamageProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
