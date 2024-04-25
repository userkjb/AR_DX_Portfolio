#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

class USpriteRenderer;
class ALasley : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	ALasley();
	~ALasley();

	// delete Function
	ALasley(const ALasley& _Other) = delete;
	ALasley(ALasley&& _Other) noexcept = delete;
	ALasley& operator=(const ALasley& _Other) = delete;
	ALasley& operator=(ALasley&& _Other) noexcept = delete;

	//inline ELasleyState GetState() const
	//{
	//	return State;
	//}

	//inline void SetState(ELasleyState _State)
	//{
	//	StateChange(_State);
	//}

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

	void CreateAnimation();
	void StateInit();

	void SummonsBegin();
	void SummonsTick(float _DeltaTime);
	void SummonsEnd();
	void DevilEyeBegin();
	void DevilEyeTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void WakeBegin();
	void WakeTick(float _DeltaTime);
	void DemonicBladeBegin();
	void DemonicBladeTick(float _DeltaTime);
	void DimensionCutterBegin();
	void DimensionCutterTick(float _DeltaTime);
	void DoubleDimensionCutterBegin();
	void DoubleDimensionCutterTick(float _DeltaTime);
	void DownBegin();
	void DownTick(float _DeltaTime);

	void LasleySummonEnd();

	USpriteRenderer* LasleyRenderer = nullptr;
	USpriteRenderer* LasleySummonFX = nullptr;

	//ELasleyState State = ELasleyState::None;
	UStateManager State;

	const int Life = 4;
	const float MoveSpeed = 500.0f;
};

