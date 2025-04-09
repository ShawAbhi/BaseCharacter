// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

#include "AbilitySystemComponent.h"
#include "BaseCharacter/AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseCharacter/AbilitySystem/BaseAttributeSet.h"

ABasePlayerState::ABasePlayerState()
{
	SetNetUpdateFrequency(100.0f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAttributeSet* ABasePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
