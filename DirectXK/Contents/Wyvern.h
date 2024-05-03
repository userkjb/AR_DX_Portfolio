#pragma once
#include <EngineCore/Actor.h>

class AWyvern : public AActor, public std::enable_shared_from_this<AWyvern>
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AWyvern();
	~AWyvern();

	// delete Function
	AWyvern(const AWyvern& _Other) = delete;
	AWyvern(AWyvern&& _Other) noexcept = delete;
	AWyvern& operator=(const AWyvern& _Other) = delete;
	AWyvern& operator=(AWyvern&& _Other) noexcept = delete;

	inline void SettingPosition()
	{
		State.ChangeState("Setting");
		return;
	}

	inline void CreateWyvern()
	{
		State.ChangeState("Idle");
		return;
	}

	inline void SetWyvernWorldPos(FVector _Pos)
	{
		InActorPos = _Pos;
	}

	inline void SetWyvernLocalPos(FVector _Pos)
	{
		InRenderPos = _Pos;
	}

	inline void SetPlayerPos(FVector _PlayerPos)
	{
		SendPlayerDir = _PlayerPos;
	}

	inline FVector GetRenderWorldPos()
	{
		return WyvernRenderer->GetWorldPosition();
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateAnimation();
	void StateInit();

	void SettingBegin();
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void AttackBegin();
	void AttackTick(float _DeltaTime);
	void AttackExit();


	void CollisionCheck(float _DeltaTime);

	UStateManager State;
	USpriteRenderer* WyvernRenderer = nullptr;
	UCollision* WyvernCollision = nullptr;
	UCollision* PlayerCheck = nullptr;

	FVector InActorPos = FVector::Zero;
	FVector InRenderPos = FVector::Zero;
	FVector SendPlayerDir = FVector::Zero;
	
	bool Attack_Ready = false;
	bool b_Attack_Down = false;
	bool b_Attack_Up = false;
	bool ChangeAnimation_One = false;
	float AttackDelayTime = 0.0f;
};

