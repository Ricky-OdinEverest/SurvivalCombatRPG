#pragma once
UENUM()
enum class ESCR_VaultingState : uint8
{
	NotVaulting,
	WantsToVault,
	Vaulting
};