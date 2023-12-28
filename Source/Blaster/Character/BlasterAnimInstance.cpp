// Copyright SF5Gaming, Inc.


#include "BlasterAnimInstance.h"

#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}
	
	if (BlasterCharacter == nullptr) return;

	FVector Velocity = BlasterCharacter->GetVelocity();	
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();
	bIsCrouched = BlasterCharacter->bIsCrouched;

	bAiming = BlasterCharacter->IsAiming();
	//UE_LOG(LogTemp, Warning, TEXT("Character Is Aiming %hhd"), bAiming);

	FRotator AimRotation = BlasterCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);

	//YawOffset = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

	YawOffset = DeltaRotation.Yaw;
	//UE_LOG(LogTemp, Warning, TEXT("AimRotation Yaw %f"), AimRotation.Yaw);

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = UKismetMathLibrary::SafeDivide(Delta.Yaw,DeltaSeconds);
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = BlasterCharacter->GetAO_Yaw();	
	AO_Pitch = BlasterCharacter->GetAO_Pitch();
	
	/*
	if (!BlasterCharacter->HasAuthority() && !BlasterCharacter->IsLocallyControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("AimRotation Yaw %f"), AimRotation.Yaw);
		UE_LOG(LogTemp, Warning, TEXT("MovementRotation Yaw %f"), MovementRotation.Yaw);
	}
	*/
	
}
