// Copyright SF5Gaming, Inc.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(const FString& TextToDisplay) const
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(const APawn* InPawn) const
{
	const ENetRole LocalRole = InPawn->GetLocalRole();
	const ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString FS_LocalRole;
	FString FS_RemoteRole;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		FS_LocalRole = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		FS_LocalRole = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		FS_LocalRole = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		FS_LocalRole = FString("None");
		break;
	default:
		break;
	}

	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		FS_RemoteRole = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		FS_RemoteRole = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		FS_RemoteRole = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		FS_RemoteRole = FString("None");
		break;
	default:
		break;
	}
	const FString RoleString = FString::Printf(TEXT("Local Role: %s\nRemote Role: %s"), *FS_LocalRole, *FS_RemoteRole);
	SetDisplayText(RoleString);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}
