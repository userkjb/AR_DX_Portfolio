#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "LasleyStageGUI.h"

class USpriteRenderer;
class ADevilChurchWarlock;
class ATentacle;
class ULasleyUI;
class ALasley : public AActor
{
	GENERATED_BODY(AActor)

#ifdef _DEBUG
	friend LasleyStageGUI;
	friend ULasleyUI;
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
	void SoundCheck(float _DeltaTime);

	USpriteRenderer* LasleyRenderer = nullptr;
	USpriteRenderer* LasleyDemonSword = nullptr;
	USpriteRenderer* LasleySummonFX = nullptr; // 맨 처음 칼 잡았을 때. FX
	UCollision* LasleyCollision = nullptr;
	ULasleyUI* Widget = nullptr;

	//ELasleyState State = ELasleyState::None;
	UStateManager State;
	std::string PreStateName = "";

	UEngineSoundPlayer Explosion_Sound;
	UEngineSoundPlayer Cutter_Sound;
	UEngineSoundPlayer DoubleCutter_Sound;
	UEngineSoundPlayer Tentacle_Sound;

	int MovePosNum = 0;
	const float MoveSpeed = 1500.0f;
	const float SwordSpeed = 500.0f;
	const float RotationPower = 0.0f;

	FVector PlayerPos = FVector::Zero;

	bool BattleStart = false;
	bool Large = false;
	bool MoveBlade = false;
	int Life = 3; // 부활 횟수
	int MaxHp = 40;
	int Hp = 40;

	float SummonTime = 0.0f;
	float IdleTime = 0.0f;
	float ExplosionSoundTime = 0.0f;
	float DevilEyeSoundTime = 0.0f;
	float CutterSoundTime = 0.0f;
	float DoubleCutterSoundTime = 0.0f;
	float DownTime = 0.0f;
	float DoorTentacleTime = 0.0f;
	float DieTime = 0.0f;

	std::vector<FVector> LasleyMovePos;
	std::vector<std::vector<FVector>> TentacleSummonPos;
	std::vector<FVector> WarlockSummonPos;
	FVector MoveVectorPos = FVector::Zero;

	int WarlockCount = 0; // 워록 카운트
	std::vector<std::shared_ptr<ADevilChurchWarlock>> Warlocks;
	FVector DemonSwordVector = FVector::Zero;
	bool MoveOne = false;
	bool DieOne = false;
	bool b_ExplosionSound = false;
	bool b_CutterSound = false;
	bool b_DoubleCutterSound = false;
	bool b_TentacleSound = false;
	
	std::vector<std::shared_ptr<ATentacle>> DoorTentacles;
	bool b_DoorTentacle = false; // Tick 트리거.
	bool b_DoorTentacleOne = false;
	bool b_DevilEye_One = false;
	int doorTentacleCount = 0;
	size_t DoorTentacleCount_2 = 0;
};

// 이동 하면서 더스트를 뿌린다.(약 0.5초 마다?)

// 주 패턴은
// 밑 바닥 불 -> (이동 -> 참격(double) -> 불 -> 낮은 확률로 이동 -> 웨이브)
// 순으로 이루어 진다.

// 1페이즈
// 시작하자마자 양옆 문 앞에 바닥 불 소환.
// 1초마다 번지며, 1페이즈 최종 각 7개 까지 소환.
// 불이 없는 곳이 있어서 이동 좌표 2곳이 추가된다.
// 불을 소환할 때는 4곳 중 한 곳에 소환 된다.

// 1 -> 2
// 밑 바닥 불이 밑 바닥을 전부 덮음.

// 2페이즈
// 레이지 상태이다.
// 밑 바닥이 불바다 이므로 이동하는 곳은 8곳 랜덤.
// DevilEye 할 때 마다 5곳 중 랜덤으로 불 장판 소환.
// -> 자신이 있는 곳은 소환 안함?

// 2 -> 3
// 

// 3페이즈
// 발판 2 곳을 랜덤으로 선택, X 축 중 한 축 선택 해서
// 총 3곳의 발판을 불로 덮음.