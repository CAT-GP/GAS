#include "ActorComponents/GAS_FootstepComponent.h"

#include "GASCharacter.h"
#include "PhysicalMaterials/GAS_PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"

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
					UGAS_PhysicalMaterial* PhysicalMaterial = Cast<UGAS_PhysicalMaterial>(HitResult.PhysMaterial.Get());

					if (PhysicalMaterial)
					{
						UGameplayStatics::PlaySoundAtLocation(this, PhysicalMaterial->FootstepSound, Location, 1.f);
					}
				}
			}

		}
	}
}

