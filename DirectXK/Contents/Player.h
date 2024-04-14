#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

class USpriteRenderer;
class UDefaultSceneComponent;
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
	void DashBegin();
	void DashTick(float _DeltaTime);
	void DashEnd();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieEnd();

	void Gravity(float _DeltaTime);

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	UStateManager State;
	EEngineDir ActorDir = EEngineDir::MAX;
	FVector PlayerPos = FVector::Zero;
		
	float4 MouseCenter = float4::Zero;
	float4 PlayerToMouseDir = float4::Zero;

	const float RunSpeed = 500.0f;
	const float JumpPower = 100.0f;
	const float DashPower = 100.0f;
	float DashCreationTime = 0.0f;
	const float DashCountUp = 3.0f; // 3√ 
	const float GravityPower = 100.0f;
	int Hp = 0;
	int MaxHp = 0;

	int DashCount = 2;
	int DashCountMax = 2;
};

