#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	inline int GetHp() const
	{
		return Hp;
	}
	inline void SetHp(int _Hp)
	{
		Hp = _Hp;
	}

	inline FVector GetPlayerPos() const
	{
		return PlayerPos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateAnimation();
	void StateInit();
	void PlayerMouseDir();
	void DashCountTime(float _DeltaTime);

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleEnd();
	void RunBegin();
	void RunTick(float _DeltaTime);
	void RunEnd();
	void JumpBegin();
	void JumpTick(float _DeltaTime);
	void JumpEnd();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieEnd();

	USpriteRenderer* PlayerRenderer = nullptr;
	UStateManager State;
	EActorDir ActorDir = EActorDir::Right;
	FVector PlayerPos = FVector::Zero;
	const float RunSpeed = 500.0f;
	const float JumpPower = 100.0f;
	const float DashPower = 100.0f;
	float DashCreationTime = 0.0f;
	int Hp = 0;
	int MaxHp = 0;

	int DashCount = 2;
	int DashCountMax = 2;
};

