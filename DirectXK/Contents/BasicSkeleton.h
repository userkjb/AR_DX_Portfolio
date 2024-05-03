#pragma once
#include <EngineCore/Actor.h>

class ABasicSkeleton : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABasicSkeleton();
	~ABasicSkeleton();

	// delete Function
	ABasicSkeleton(const ABasicSkeleton& _Other) = delete;
	ABasicSkeleton(ABasicSkeleton&& _Other) noexcept = delete;
	ABasicSkeleton& operator=(const ABasicSkeleton& _Other) = delete;
	ABasicSkeleton& operator=(ABasicSkeleton&& _Other) noexcept = delete;
	
	/// <summary>
	/// 생성 위치 설정.
	/// </summary>
	/// <param name="_Pos">생성 좌표값.</param>
	inline void SetBasicSkeletonPos(FVector _Pos)
	{
		InPos = _Pos;
		SKState.ChangeState("Setting");
		return;
	}

	/// <summary>
	/// BasicSkeleton 생성.
	/// </summary>
	inline void CreateBasicSkeleton()
	{
		SKState.ChangeState("Idle");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void CreateAnimation();
	void StateInit();

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void RunBegin();
	void RunTick(float _DeltaTime);
	void RunExit();
	void AttackBegin();
	void AttackTick(float _DeltaTime);
	void AttackExit();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieExit();

	void CollisionCheck(float _Time);

	UStateManager SKState;
	USpriteRenderer* BasicSkeletonRenderer = nullptr;
	UCollision* BasicSkeletonCollision = nullptr;
	UCollision* PlayerCheckCollision = nullptr;

	const float RumSpeed = 100.0f;
	FVector InPos = FVector::Zero;
	FVector MoveVector = FVector::Zero;
	float PlayerNotCatchTime = 0.0f;
	float RunTime = 0.0f;
	std::string PreState = "";
};

