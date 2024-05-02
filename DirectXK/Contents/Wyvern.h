#pragma once
#include <EngineCore/Actor.h>

class AWyvern : public AActor
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

	inline void CreateWyvern()
	{
		State.ChangeState("Idle");
		return;
	}

	inline void SetWyvernPos(FVector _Pos)
	{
		InPos = _Pos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateAnimation();
	void StateInit();

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();


	UStateManager State;

	USpriteRenderer* WyvernRenderer = nullptr;
	UCollision* WyvernCollision = nullptr;

	FVector InPos = FVector::Zero;
};

