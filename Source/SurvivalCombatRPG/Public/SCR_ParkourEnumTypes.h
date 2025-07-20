#pragma once
UENUM()
enum class ESCR_VaultingState : uint8
{
	NotVaulting,
	WantsToVault,
	Vaulting
};

UENUM(BlueprintType)
enum class EFoot : uint8
{
	Left  UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

