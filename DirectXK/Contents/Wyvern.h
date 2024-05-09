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

	//inline void SetWyvernLocalPos(FVector _Pos)
	//{
	//	InRenderPos = _Pos;
	//}

	/// <summary>
	/// 받은 Position 값으로 오른쪽 왼쪽을 판단할 수 없다.
	/// </summary>
	/// <param name="_Dir"></param>
	inline void SetWyvernRendDir(EEngineDir _Dir)
	{
		InRenderDir = _Dir;
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

	void RenderAndCollisionPosSetting();

	void CollisionCheck(float _DeltaTime);

	UStateManager State;
#ifdef _DEBUG
	USpriteRenderer* ActorRender = nullptr;
#endif
	USpriteRenderer* WyvernRenderer = nullptr;
	UCollision* WyvernCollision = nullptr;
	UCollision* PlayerCheckCol = nullptr;

	FVector InActorPos = FVector::Zero;
	FVector InRenderPos = FVector(300.0f, 0.0f, 0.0f);
	FVector SendPlayerDir = FVector::Zero;
	
	bool Attack_Ready = false;
	bool b_Attack_Down = false;
	bool b_Attack_Up = false;
	bool ChangeAnimation_One = false;
	float AttackDelayTime = 0.0f;
	EEngineDir InRenderDir = EEngineDir::MAX;

	int Hp = 10;
};

