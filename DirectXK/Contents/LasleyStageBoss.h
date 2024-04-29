#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class UTileRenderer;
class APlayer;
class ALasley;
class ALasleyStageBoss : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALasleyStageBoss();
	~ALasleyStageBoss();

	// delete Function
	ALasleyStageBoss(const ALasleyStageBoss& _Other) = delete;
	ALasleyStageBoss(ALasleyStageBoss&& _Other) noexcept = delete;
	ALasleyStageBoss& operator=(const ALasleyStageBoss& _Other) = delete;
	ALasleyStageBoss& operator=(ALasleyStageBoss&& _Other) noexcept = delete;

	/// <summary>
	/// 보스전 시작함?
	/// </summary>
	/// <returns></returns>
	inline bool IsBossStageStart() const
	{
		return BossStageStart;
	}

	/// <summary>
	/// ALasleyStageBossGM::Tick 에서 Lasley를 넘겨 줌.
	/// </summary>
	/// <param name="_Lasley"></param>
	inline void SendLasley(std::shared_ptr<ALasley> _Lasley)
	{
		Lasley = _Lasley;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	UDefaultSceneComponent* Root = nullptr;
	UTileRenderer* TileRenderer = nullptr;
	USpriteRenderer* MapColRenderer = nullptr;
	UCollision* BossStageStartCol = nullptr; // 스테이지 시작을 위한 Col
	
	USpriteRenderer* MapObjectLeftDoor = nullptr; // 문
	UCollision* MapObjectLeftDoorCol = nullptr; // 문 Col
	USpriteRenderer* MapObjectRightDoor = nullptr; // 문
	UCollision* MapObjectRightDoorCol = nullptr; // 문 Col

	std::shared_ptr<ALasley> Lasley = nullptr;

	UStateManager State;

	bool BossStageStart = false;

	void LasleyBossStageInBegin();
	void LasleyBossStageInTick(float _DeltaTime);
	void LasleyBossStageInExit();
	void LasleyBossStageStartBegin();
	void LasleyBossStageStartTick(float _DeltaTime);
	void LasleyBossStageStartExit();
	void LasleyBossStageIngBegin();
	void LasleyBossStageIngTick(float _DeltaTime);
	void LasleyBossStageIngExit();
	void LasleyBossStageEndBegin();
	void LasleyBossStageEndTick(float _DeltaTime);
	void LasleyBossStageEndExit();

	void CreateMapImage();
	void StateInit();
	void CreateAnimation();

	void StageStartCollisionCheck(float _DeltaTime);
	void PlayerStageOutCollisionCheck(float _DeltaTime);
	void SendMapInDoor(APlayer* _Player, float _SendFloatValue);
	
};

