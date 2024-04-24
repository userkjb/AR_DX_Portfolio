#pragma once
#include <EngineCore/Actor.h>

//class APlayerWeapon;
class UDefaultSceneComponent;
class APlayerWeapon;
class AWeaponFX : public AActor
{
	GENERATED_BODY(AActor)

	friend APlayerWeapon;
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
	UCollision* Weapon_FX_Collision = nullptr;
	FVector CreateFX_Pos = FVector::Zero;
};

