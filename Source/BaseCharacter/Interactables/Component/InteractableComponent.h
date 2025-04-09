// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "InteractableComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Interactables), meta=(BlueprintSpawnableComponent))
class BASECHARACTER_API UInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()
};
