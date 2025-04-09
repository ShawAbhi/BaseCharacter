// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAbilitySystemComponent.h"

UBaseAbilitySystemComponent::UBaseAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UBaseAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
