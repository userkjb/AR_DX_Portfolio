#pragma once
#include <EngineCore/Actor.h>

class APlayerWeapon : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	APlayerWeapon();
	~APlayerWeapon();

	// delete Function
	APlayerWeapon(const APlayerWeapon& _Other) = delete;
	APlayerWeapon(APlayerWeapon&& _Other) noexcept = delete;
	APlayerWeapon& operator=(const APlayerWeapon& _Other) = delete;
	APlayerWeapon& operator=(APlayerWeapon&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};

