#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{

	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30;
	bHasExploded = false;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

}

void AMineItem::ActivateItem(AActor* Activator)
{
	if (bHasExploded) return;

	Super::ActivateItem(Activator);

	// ���� ���忡�� ���� ���� Ÿ�̸� �ڵ鷯�� ����. �װ� �����ϴ� �� Ÿ�̸� �Ŵ���
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay,
		false
	);

	bHasExploded = true;
}

void AMineItem::Explode()
{
	UParticleSystemComponent* Particle = nullptr;
	if (ExplosionParticle)
	{
		 Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
		);
	}

	TArray<AActor*> OverlappingActors;
	// ExplosionCollision ������Ʈ�� ���� ���� �ִ� ��� ���͵��� �ڵ����� ã�Ƽ� 
	// OverlappingActors �迭�� �־���
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				4.0f,
				FColor::Red,
				FString::Printf(TEXT("Player Damaged %d by MineItem!!"), ExplosionDamage));

			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass()
			);
		}
	}

	DestroyItem();
}