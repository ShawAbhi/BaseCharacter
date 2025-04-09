// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

class UBaseAbilitySystemComponent;
class UBaseAttributeSet;
/**
 * 
 */
UCLASS()
class BASECHARACTER_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	ABasePlayerState();
	
	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;

public:
	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//~End of IAbilitySystemInterface interface

	virtual UBaseAttributeSet* GetAttributeSet() const;
};
