#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class UTileRenderer;
class APlayer;
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
	/// ������ ������?
	/// </summary>
	/// <returns></returns>
	inline bool IsBossStageStart() const
	{
		return BossStageStart;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	UDefaultSceneComponent* Root = nullptr;
	UTileRenderer* TileRenderer = nullptr;
	USpriteRenderer* MapColRenderer = nullptr;
	UCollision* BossStageStartCol = nullptr; // �������� ������ ���� Col
	
	USpriteRenderer* MapObjectLeftDoor = nullptr; // ��
	UCollision* MapObjectLeftDoorCol = nullptr; // �� Col
	USpriteRenderer* MapObjectRightDoor = nullptr; // ��
	UCollision* MapObjectRightDoorCol = nullptr; // �� Col



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

