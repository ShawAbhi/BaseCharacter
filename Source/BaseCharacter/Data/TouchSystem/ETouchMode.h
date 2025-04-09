#pragma once

UENUM(BlueprintType)
enum class EEnum_TouchMode : uint8
{
	None			UMETA(DisplayName = "None"),
	Pressed			UMETA(DisplayName = "Pressed"),
	Released		UMETA(DisplayName = "Released"),
	Moved			UMETA(DisplayName = "Moved"),
	Tap				UMETA(DisplayName = "Tap"),
	Hold			UMETA(DisplayName = "Hold"),
	HoldReleased	UMETA(DisplayName = "HoldReleased")
};
