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

	inline void SetState(std::string_view _ChangeState)
	{
		State.ChangeState(_ChangeState);
	}
	inline std::string GetCurLasleyState()
	{
		return State.GetCurStateName();
	}

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

	void LasleySummonEndCallBack();

	USpriteRenderer* LasleyRenderer = nullptr;
	USpriteRenderer* LasleyDemonSword = nullptr;
	USpriteRenderer* LasleySummonFX = nullptr; // �� ó�� Į ����� ��. FX

	//ELasleyState State = ELasleyState::None;
	UStateManager State;

	int Life = 2;
	int MaxHp = 40;
	int Hp = 40;
	const float MoveSpeed = 500.0f;
	float MoveTime = 0.0f;
	std::vector<FVector> MovePos;
};

// �̵��� �� �� �� 2��, �� 12 �� �� �������� �̵��Ѵ�.
// �̵� �ϸ鼭 ����Ʈ�� �Ѹ���.(�� 0.5�� ����?)
