#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "LasleyStageGUI.h"

class USpriteRenderer;
class ADevilChurchWarlock;
class ALasley : public AActor
{
	GENERATED_BODY(AActor)

#ifdef _DEBUG
	friend LasleyStageGUI;
#endif
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
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void MoveBegin();
	void MoveTick(float _DeltaTime);
	void MoveExit();
	void DevilEyeBegin();
	void DevilEyeTick(float _DeltaTime);
	void DevilEyeExit();
	void DemonicBladeBegin();
	void DemonicBladeTick(float _DeltaTime);
	void DemonicBladeExit();
	void DimensionCutterBegin();
	void DimensionCutterTick(float _DeltaTime);
	void DimensionCutterExit();
	void DoubleDimensionCutterBegin();
	void DoubleDimensionCutterTick(float _DeltaTime);
	void DoubleDimensionCutterExit();
	void DownBegin();
	void DownTick(float _DeltaTime);
	void DownExit();
	void WakeBegin();
	void WakeTick(float _DeltaTime);
	void WakeExit();
	void DieBegin();
	void DieTick(float _DeltaTime);

	void LasleySummonEndCallBack();

	USpriteRenderer* LasleyRenderer = nullptr;
	USpriteRenderer* LasleyDemonSword = nullptr;
	USpriteRenderer* LasleySummonFX = nullptr; // �� ó�� Į ����� ��. FX
	UCollision* LasleyCollision = nullptr;

	//ELasleyState State = ELasleyState::None;
	UStateManager State;

	const float MovePower = 500.0f;
	const float RotationPower = 0.0f;
	float SummonTime = 0.0f;

	bool Large = false;
	int Life = 3; // ��Ȱ Ƚ��
	int MaxHp = 40;
	int Hp = 40;
	const float MoveSpeed = 500.0f;
	float MoveTime = 0.0f;
	float DownTime = 0.0f;
	std::vector<FVector> MovePos;
	std::vector<std::vector<FVector>> TentacleSummonPos;
	std::vector<FVector> WarlockSummonPos;

	int WarlockCount = 0;
	std::vector<std::shared_ptr<ADevilChurchWarlock>> Warlocks;
};

// �̵� �ϸ鼭 ����Ʈ�� �Ѹ���.(�� 0.5�� ����?)

// �� ������
// �� �ٴ� �� -> (�̵� -> ����(double) -> �� -> ���� Ȯ���� �̵� -> ���̺�)
// ������ �̷�� ����.

// 1������
// �������ڸ��� �翷 �� �տ� �ٴ� �� ��ȯ.
// 1�ʸ��� ������, 1������ ���� �� 7�� ���� ��ȯ.
// ���� ���� ���� �־ �̵� ��ǥ 2���� �߰��ȴ�.
// ���� ��ȯ�� ���� 4�� �� �� ���� ��ȯ �ȴ�.

// 1 -> 2
// �� �ٴ� ���� �� �ٴ��� ���� ����.

// 2������
// ������ �����̴�.
// �� �ٴ��� �ҹٴ� �̹Ƿ� �̵��ϴ� ���� 8�� ����.
// DevilEye �� �� ���� 5�� �� �������� �� ���� ��ȯ.
// -> �ڽ��� �ִ� ���� ��ȯ ����?

// 2 -> 3
// 

// 3������
// ���� 2 ���� �������� ����, X �� �� �� �� ���� �ؼ�
// �� 3���� ������ �ҷ� ����.