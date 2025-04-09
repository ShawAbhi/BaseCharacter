
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UGameplayAbility;
class UBaseAbilitySystemComponent;
class UBaseAttributeSet;
class UGameplayEffect;

UCLASS()
class BASECHARACTER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface interface
	virtual UBaseAttributeSet* GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GiveDefaultAbilities();
	void InitDefaultAttributes() const;

	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
};
