#pragma once
 
UENUM()
enum class ESCR_ConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESCR_ValidType : uint8
{
	Valid,
	Invalid
};

UENUM(BlueprintType)
enum class EFoot : uint8
{
	Left  UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

