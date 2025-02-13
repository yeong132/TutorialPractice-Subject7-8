#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpartaDronePawn.generated.h"

UCLASS()
class TUTORIALPRACTICE_API ASpartaDronePawn : public APawn
{
	GENERATED_BODY()

public:
	ASpartaDronePawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
