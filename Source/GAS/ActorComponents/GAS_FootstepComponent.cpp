#include "ActorComponents/GAS_FootstepComponent.h"

#include "GASCharacter.h"
#include "PhysicalMaterials/GAS_PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"

///*********************************************************************************************************///
static TAutoConsoleVariable<int32> CVarShowFootsteps(
	TEXT("ShowDebugFootsteps"),

	0,

	TEXT("Draws debug info about footsteps")
	TEXT(" 0: off/n")
	TEXT(" 1: on/n"),

	ECVF_Cheat);

///*********************************************************************************************************///

UGAS_FootstepComponent::UGAS_FootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGAS_FootstepComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGAS_FootstepComponent::HandleFootstep(EFoot Foot)
{
	if (AGASCharacter* Character = Cast<AGASCharacter>(GetOwner()))
	{

		const int32 DebugShowFootsteps = CVarShowFootsteps.GetValueOnAnyThread();

		if (USkeletalMeshComponent* Mesh = Character->GetMesh())
		{
			FHitResult HitResult;

			const FVector SocketLocation = Mesh->GetSocketLocation(Foot == EFoot::Left ? LeftFootSocket : RightFootSocket);
			const FVector Location = SocketLocation + FVector::UpVector * 20;

			FCollisionQueryParams QueryParams;
			QueryParams.bReturnPhysicalMaterial = true;
			QueryParams.AddIgnoredActor(Character);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + FVector::UpVector * -50.f, ECollisionChannel::ECC_WorldStatic, QueryParams))
			{
				if (HitResult.bBlockingHit)
				{

					if (HitResult.PhysMaterial.Get())
					{
						UGAS_PhysicalMaterial* PhysicalMaterial = Cast<UGAS_PhysicalMaterial>(HitResult.PhysMaterial.Get());

						if (PhysicalMaterial)
						{
							UGameplayStatics::PlaySoundAtLocation(this, PhysicalMaterial->FootstepSound, Location, 1.f);
							
							if (DebugShowFootsteps > 0)
							{
								DrawDebugString(GetWorld(), Location, PhysicalMaterial->GetName(), nullptr, FColor::White, 4.f);
							}
						}

					}

					if (DebugShowFootsteps > 0)
					{
						DrawDebugSphere(GetWorld(), Location, 16, 16, FColor::Red, false, 4.f);
					}


				}
				else
				{
					if (DebugShowFootsteps > 0)
					{
						DrawDebugLine(GetWorld(), Location, Location + FVector::UpVector * -50.f, FColor::Red, false, 4, 0, 1);
					}
				}
			}
			else
			{
				if (DebugShowFootsteps > 0)
				{
					DrawDebugLine(GetWorld(), Location, Location + FVector::UpVector * -50.f, FColor::Red, false, 4, 0, 1);
					DrawDebugSphere(GetWorld(), Location, 16, 16, FColor::Red, false, 4.f);
				}
			}
		}
	}


}

