#pragma once
#include <EngineCore/Actor.h>

class APlayer;
class ACosmosSword : public AActor
{
	GENERATED_BODY(AActor)
	friend APlayer;
public:
	// constrcuter destructer
	ACosmosSword();
	~ACosmosSword();

	// delete Function
	ACosmosSword(const ACosmosSword& _Other) = delete;
	ACosmosSword(ACosmosSword&& _Other) noexcept = delete;
	ACosmosSword& operator=(const ACosmosSword& _Other) = delete;
	ACosmosSword& operator=(ACosmosSword&& _Other) noexcept = delete;

private :
	inline void SetWeaponActorPosition(FVector _Pos)
	{
		SetActorPos = _Pos;
	}
	
	inline void SetPlayerRenderDir(EEngineDir _Dir)
	{
		SetPlayerDir = _Dir;
	}


	inline std::string GetWeaponState() const
	{
		//return PreState;
		return State.GetCurStateName();
	}

	inline void CreateWeapon()
	{
		State.ChangeState("Idle");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void CreateAnimation();
	void StateInit();

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();

	USpriteRenderer* WeaponRenderer = nullptr;
	UStateManager State;

	bool b_Attack = false;
	FVector SetActorPos = FVector::Zero;
	FVector AttackRotation = FVector::Zero;
	EEngineDir SetPlayerDir = EEngineDir::MAX;
	std::string PreState = "";
};

