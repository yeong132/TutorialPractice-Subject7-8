#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class TUTORIALPRACTICE_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	virtual void ActivateItem(AActor* Activator) override;

	FTimerHandle ExplosionTimerHandle;

	void Explode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	bool bHasExploded;
};
