#pragma once
#include <EngineCore/Actor.h>

//class APlayerWeapon;
class UDefaultSceneComponent;
class AWeaponFX : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constructer destructer
	AWeaponFX();
	virtual ~AWeaponFX();

	// delete Function
	AWeaponFX(const AWeaponFX& _Other) = delete;
	AWeaponFX(AWeaponFX&& _Other) noexcept = delete;
	AWeaponFX& operator=(const AWeaponFX) = delete;
	AWeaponFX& operator=(AWeaponFX&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Weapon_FX_Render = nullptr;
	UCollision* Collision = nullptr;
};

