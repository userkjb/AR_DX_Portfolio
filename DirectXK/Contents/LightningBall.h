#pragma once
#include <EngineCore/Actor.h>

class ALightningBall : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALightningBall();
	~ALightningBall();

	// delete Function
	ALightningBall(const ALightningBall& _Other) = delete;
	ALightningBall(ALightningBall&& _Other) noexcept = delete;
	ALightningBall& operator=(const ALightningBall& _Other) = delete;
	ALightningBall& operator=(ALightningBall&& _Other) noexcept = delete;

	inline void SetPlayerDir(FVector _Pos)
	{
		MovePlayerDir = _Pos;
	}

	inline void SettingActorPosition(FVector _Pos)
	{
		CreatePos = _Pos;
		State.ChangeState("Setting");
		return;
	}

	inline void CreateLightningBool()
	{
		State.ChangeState("Create");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void CreateAnimation();
	void StateInit();

	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();



	USpriteRenderer* LightningBallRenderer = nullptr;
	
	UStateManager State;
	FVector MovePlayerDir = FVector::Zero;
	FVector CreatePos = FVector::Zero;

	const float Speed = 200.0f;
	const float LifeIsTime = 5.0f; // 5.0f
	float LifeTime = 0.0f;
};

