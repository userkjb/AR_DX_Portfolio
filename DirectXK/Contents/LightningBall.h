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
	FVector CreatePos = FVector::Zero;
	FVector MoveDir = FVector::Zero;
	EEngineDir WyvernDir = EEngineDir::MAX;
};

