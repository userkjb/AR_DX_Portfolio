#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "LasleyStageGUI.h"

class USpriteRenderer;
class ADevilChurchWarlock;
class ATentacle;
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

	inline void IsStart()
	{
		BattleStart = true;
	}

	inline std::string GetState() const
	{
		return State.GetCurStateName();
	}

	inline void SetState(std::string_view _ChangeState)
	{
		State.ChangeState(_ChangeState);
		return;
	}
	inline std::string GetCurLasleyState()
	{
		return State.GetCurStateName();
	}

	inline void GMToPlayerPos(FVector _Pos)
	{
		PlayerPos = _Pos;
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
	void DoorTentacle(float _DeltaTime);

	void CollisionCheck(float _DeltaTime);

	USpriteRenderer* LasleyRenderer = nullptr;
	USpriteRenderer* LasleyDemonSword = nullptr;
	USpriteRenderer* LasleySummonFX = nullptr; // �� ó�� Į ����� ��. FX
	UCollision* LasleyCollision = nullptr;

	//ELasleyState State = ELasleyState::None;
	UStateManager State;
	std::string PreStateName = "";

	int MovePosNum = 0;
	const float MoveSpeed = 1500.0f;
	const float SwordSpeed = 500.0f;
	const float RotationPower = 0.0f;

	FVector PlayerPos = FVector::Zero;

	bool BattleStart = false;
	bool Large = false;
	bool MoveBlade = false;
	int Life = 3; // ��Ȱ Ƚ��
	int MaxHp = 40;
	int Hp = 40;

	float SummonTime = 0.0f;
	float IdleTime = 0.0f;
	float DevilEyeTime = 0.0f;
	float DownTime = 0.0f;
	float DoorTentacleTime = 0.0f;
	float DieTime = 0.0f;

	std::vector<FVector> LasleyMovePos;
	std::vector<std::vector<FVector>> TentacleSummonPos;
	std::vector<FVector> WarlockSummonPos;
	FVector MoveVectorPos = FVector::Zero;

	int WarlockCount = 0; // ���� ī��Ʈ
	std::vector<std::shared_ptr<ADevilChurchWarlock>> Warlocks;
	FVector DemonSwordVector = FVector::Zero;
	bool MoveOne = false;
	bool DieOne = false;
	
	std::vector<std::shared_ptr<ATentacle>> DoorTentacles;
	bool b_DoorTentacle = false; // Tick Ʈ����.
	bool b_DoorTentacleOne = false;
	bool b_DevilEye_One = false;
	int doorTentacleCount = 0;
	size_t DoorTentacleCount_2 = 0;
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