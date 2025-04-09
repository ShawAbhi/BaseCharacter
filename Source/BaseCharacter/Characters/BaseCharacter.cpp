// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "BaseCharacter/AbilitySystem/BaseAbilitySystemComponent.h"
#include "Modules/ModuleManager.h"

//Do Not Remove, Very Important to Load Editor.
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, BaseCharacter, "BaseCharacter" );

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAttributeSet* ABaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ABaseCharacter::GiveDefaultAbilities()
{
	if (!HasAuthority()) return;
	
	if (!IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is null"));
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void ABaseCharacter::InitDefaultAttributes() const
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect) { return; }

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributeEffect, 1.f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}