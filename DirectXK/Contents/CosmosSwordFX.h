#pragma once
#include <EngineCore/Actor.h>

class ACosmosSword;
class ACosmosSwordFX : public AActor
{
	friend ACosmosSword;
	GENERATED_BODY(AActor)

public:
	// constructer destructer
	ACosmosSwordFX();
	virtual ~ACosmosSwordFX();

	// delete Function
	ACosmosSwordFX(const ACosmosSwordFX& _Other) = delete;
	ACosmosSwordFX(ACosmosSwordFX&& _Other) noexcept = delete;
	ACosmosSwordFX& operator=(const ACosmosSwordFX) = delete;
	ACosmosSwordFX& operator=(ACosmosSwordFX&& _Other) noexcept = delete;

private :
	inline void CreateWeaponFX()
	{
		State.ChangeState("Swing");
		return;
	}

	inline void SetCreatePosition(FVector _Pos)
	{
		InPosition = _Pos;
	}

	inline void SetCreateRotation(FVector _Rot)
	{
		InRotation = _Rot;
	}

	inline void SetFXScale(FVector _Scale)
	{
		InScale = _Scale;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();
	void CreateAnimation();

	void SwingBegin();
	void SwingTick(float _DeltaTime);
	void SwingExit();

	USpriteRenderer* Weapon_FX_Render = nullptr;
	UCollision* Weapon_FX_Collision = nullptr;

	UStateManager State;
	FVector InPosition = FVector::Zero;
	FVector InRotation = FVector::Zero;
	FVector InScale = FVector::Zero;
};
