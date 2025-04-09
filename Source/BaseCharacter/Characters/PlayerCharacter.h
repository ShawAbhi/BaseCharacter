// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BASECHARACTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
private:
	void InitAbilitySystemComponent();
	void InitHUD() const;

protected:
	APlayerCharacter();

public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

};
