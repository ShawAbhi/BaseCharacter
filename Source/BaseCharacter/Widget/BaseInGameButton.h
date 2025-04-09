// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter/Data/TouchSystem/FInGameButtonData.h"
#include "BaseCharacter/Data/TouchSystem/FTouchInputInfo.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "BaseInGameButton.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFVector, FVector);

struct FTouchInputInfo;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class BASECHARACTER_API UBaseInGameButton : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool bIsActive{false};
	FTouchInputInfo Payload;
	FGameplayMessageListenerHandle ListenerHandle;
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	int CurrentPointerIndex{-1};
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	bool bWasPressed{false};
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	FGeometry TouchGeometry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseInGameButton")
	FInGameButtonData ButtonData;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	
	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

	void ListenToTouchIndexMessages(const int& PointerIndex);
	UFUNCTION()
	void HandleTouchIndexMessages(FGameplayTag Tag, const FTouchInputInfo& TouchInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseInGameButton")
	void SetIsActive(bool bNewIsActive);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BaseInGameButton")
	bool GetIsActive() const { return bIsActive; }

	void ListenForAbility();
	UFUNCTION(BlueprintNativeEvent)
	void HandleListenAbilityMessages(FGameplayTag Tag, const FTouchInputInfo& TouchInfo);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FTouchInputInfo GetPayload() const { return Payload; }
	
public:

	FMulticastDelegateOneParamFVector OnPressed;
	FMulticastDelegateOneParamFVector OnReleased;
	FMulticastDelegateOneParamFVector OnMoved;

	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnPressed(const FVector& FingerLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnReleased(const FVector& FingerLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnMoved(const FVector& FingerLocation);
	
};
