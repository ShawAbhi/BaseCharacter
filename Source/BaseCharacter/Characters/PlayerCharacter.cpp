// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "BaseCharacter/AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseCharacter/Player/BasePlayerState.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	InitDefaultAttributes();
	InitHUD();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
	InitDefaultAttributes();
	InitHUD();
}

void APlayerCharacter::InitAbilitySystemComponent()
{
	if (ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>())
	{
		AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(BasePlayerState->GetAbilitySystemComponent());
		if (!IsValid(AbilitySystemComponent)) { return; }
		AbilitySystemComponent->InitAbilityActorInfo(BasePlayerState, this);
		AttributeSet = BasePlayerState->GetAttributeSet();
	}
}

void APlayerCharacter::InitHUD() const
{
	// if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	// {
	// 	if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(PlayerController->GetHUD()))
	// 	{
	// 		BaseHUD->Init();
	// 	}
	// }
}
