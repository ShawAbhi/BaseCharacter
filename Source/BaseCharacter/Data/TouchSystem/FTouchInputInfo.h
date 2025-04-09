#pragma once

#include "CoreMinimal.h"
#include "ETouchMode.h"
#include "FTouchInputInfo.generated.h"

USTRUCT(BlueprintType)
struct FTouchInputInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Touch")
	FVector FingerLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Touch")
	EEnum_TouchMode TouchEventType = EEnum_TouchMode::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Touch")
	bool bIsToggle = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Touch")
	TEnumAsByte<ETouchIndex::Type> TouchIndex;
};
