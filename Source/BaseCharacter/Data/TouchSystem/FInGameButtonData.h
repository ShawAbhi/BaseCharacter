#pragma once

#include "CoreMinimal.h"
#include "ETouchMode.h"
#include "GameplayTagContainer.h"
#include "FInGameButtonData.generated.h"

USTRUCT(BlueprintType)
struct FInGameButtonData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	bool bIsToggleButton = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	bool bTickTouchEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	bool bSeparateTickTag = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	bool bPassthroughTouch = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	bool bListenAbility = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	EEnum_TouchMode TouchModeToTick = EEnum_TouchMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	FGameplayTag TickModeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InGameButton")
	FGameplayTag AbilityTag;
};
