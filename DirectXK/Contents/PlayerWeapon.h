#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
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

	inline void SetPlayerToMouseDir(float4 _PlayerToMouseDir)
	{
		PlayerToMouseDir = _PlayerToMouseDir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void AttackState(float _DeltaTime);

	float4 PlayerToMouseDir = float4::Zero;
		
	USpriteRenderer* Weapon_One_Renderer = nullptr;
	USpriteRenderer* Weapon_Two_Renderer = nullptr;
};

