#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayer;
class APlayerWeapon : public AActor
{
	GENERATED_BODY(AActor)

	friend APlayer;
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
	inline void SetPlayerToMouseDir(float4 _PlayerToMouseDir)
	{
		PlayerToMouseDir = _PlayerToMouseDir;
	}
	inline void SetWeaponRotation(FVector _Rot)
	{
		WeaponRotation = _Rot;
	}

	void AttackState(float _DeltaTime);

	float4 PlayerToMouseDir = float4::Zero;
	FVector WeaponRotation = FVector::Zero;

	USpriteRenderer* Weapon_One_Renderer = nullptr;
	USpriteRenderer* Weapon_Two_Renderer = nullptr;
	//USpriteRenderer* Weapon_Effect = nullptr;
};

