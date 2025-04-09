// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInGameButton.h"

#include "GameFramework/GameplayMessageSubsystem.h"

void UBaseInGameButton::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (((ButtonData.bIsToggleButton && bIsActive) || bWasPressed) && ButtonData.bTickTouchEvent)
	{
		Payload.bIsToggle = (ButtonData.bIsToggleButton && bIsActive) ? false : ButtonData.bIsToggleButton;
		Payload.TouchEventType = ButtonData.TouchModeToTick;

		UGameplayMessageSubsystem::Get(this).BroadcastMessage(
			FGameplayTag::RequestGameplayTag(
				(ButtonData.bSeparateTickTag && ButtonData.TickModeTag != FGameplayTag::EmptyTag)
					? ButtonData.TickModeTag.GetTagName()
					: ButtonData.ActionTag.GetTagName()),
			Payload);
	}
}

void UBaseInGameButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseInGameButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ButtonData.bListenAbility)
	{
		ListenForAbility();
	}
}

FReply UBaseInGameButton::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	bWasPressed = true;
	TouchGeometry = InGeometry;
	ListenToTouchIndexMessages(InGestureEvent.GetPointerIndex());

	if (!ButtonData.bPassthroughTouch)
	{
		EventOnPressed(Payload.FingerLocation);
		OnPressed.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));
	}

	return ButtonData.bPassthroughTouch ? FReply::Unhandled() : FReply::Handled();
}

FReply UBaseInGameButton::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

	if (InGestureEvent.GetPointerIndex() != CurrentPointerIndex)
	{
		return FReply::Unhandled();
	}
	if (ButtonData.bPassthroughTouch)
	{
		return FReply::Unhandled();
	}
	EventOnReleased(Payload.FingerLocation);
	OnReleased.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));

	return FReply::Handled();
}

FReply UBaseInGameButton::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

	if (InGestureEvent.GetPointerIndex() != CurrentPointerIndex)
	{
		return FReply::Unhandled();
	}
	if (ButtonData.bPassthroughTouch)
	{
		return FReply::Unhandled();
	}
	EventOnMoved(Payload.FingerLocation);
	OnMoved.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));

	return FReply::Handled();
}

void UBaseInGameButton::ListenToTouchIndexMessages(const int& PointerIndex)
{
	if (CurrentPointerIndex == PointerIndex)
	{
		return;
	}

	if (ListenerHandle.IsValid())
	{
		UGameplayMessageSubsystem::Get(this).UnregisterListener(ListenerHandle);
	}

	CurrentPointerIndex = PointerIndex;
	const FString TagName = FString::Printf(TEXT("Message.Input.Touch.Index.%d"), CurrentPointerIndex);

	 ListenerHandle = UGameplayMessageSubsystem::Get(this).RegisterListener(
		FGameplayTag::RequestGameplayTag(*TagName), this,
		&UBaseInGameButton::HandleTouchIndexMessages);
}

void UBaseInGameButton::HandleTouchIndexMessages(FGameplayTag Tag, const FTouchInputInfo& TouchInfo)
{
	if (!bWasPressed)
	{
		return;
	}
	Payload = TouchInfo;

	if (ButtonData.ActionTag != FGameplayTag::EmptyTag)
	{
		Payload.bIsToggle = ButtonData.bIsToggleButton;
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(
			FGameplayTag::RequestGameplayTag(ButtonData.ActionTag.GetTagName()),
			Payload);
	}
	switch (Payload.TouchEventType)
	{
	case EEnum_TouchMode::Pressed:
		{
			EventOnPressed(Payload.FingerLocation);
			OnPressed.Broadcast(Payload.FingerLocation);
			break;
		}

	case EEnum_TouchMode::Released:
		{
			EventOnReleased(Payload.FingerLocation);
			OnReleased.Broadcast(Payload.FingerLocation);
			bWasPressed = false;
			break;
		}

	case EEnum_TouchMode::Moved:
		{
			EventOnMoved(Payload.FingerLocation);
			OnMoved.Broadcast(Payload.FingerLocation);
			break;
		}

	default:
		{
			// Handle unexpected cases (optional)
			break;
		}
	}
}

void UBaseInGameButton::SetIsActive_Implementation(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
}

void UBaseInGameButton::ListenForAbility()
{
	UGameplayMessageSubsystem::Get(this).RegisterListener(
		FGameplayTag::RequestGameplayTag(ButtonData.AbilityTag.GetTagName()), this,
		&UBaseInGameButton::HandleListenAbilityMessages);
}

void UBaseInGameButton::HandleListenAbilityMessages_Implementation(FGameplayTag Tag, const FTouchInputInfo& TouchInfo)
{
	SetIsActive(TouchInfo.TouchEventType == EEnum_TouchMode::Hold);
}

void UBaseInGameButton::EventOnPressed_Implementation(const FVector& FingerLocation)
{
}

void UBaseInGameButton::EventOnReleased_Implementation(const FVector& FingerLocation)
{
}

void UBaseInGameButton::EventOnMoved_Implementation(const FVector& FingerLocation)
{
}
