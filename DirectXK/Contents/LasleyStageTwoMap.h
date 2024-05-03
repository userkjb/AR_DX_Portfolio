#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class UTileRenderer;
class APlayer;
class ALasleyStageTwoMap : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALasleyStageTwoMap();
	~ALasleyStageTwoMap();

	// delete Function
	ALasleyStageTwoMap(const ALasleyStageTwoMap& _Other) = delete;
	ALasleyStageTwoMap(ALasleyStageTwoMap&& _Other) noexcept = delete;
	ALasleyStageTwoMap& operator=(const ALasleyStageTwoMap& _Other) = delete;
	ALasleyStageTwoMap& operator=(ALasleyStageTwoMap&& _Other) noexcept = delete;

	inline bool IsRightMapCol() const
	{
		return b_RightMapCol;
	}
	inline bool IsLeftMapCol() const
	{
		return b_LeftMapCol;
	}
	inline void SetIsOne(bool _Val)
	{
		StageIsOne = _Val;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateMapImage();
	void StateInit();
	void CreateAnimation();

	void StageInBegin();
	void StageInTick(float _DeltaTime);
	void StageInExit();
	void StageIdleBegin();
	void StageIdleTick(float _DeltaTime);
	void StageIdleExit();
	void StageBattleBegin();
	void StageBattleTick(float _DeltaTime);
	void StageBattleExit();

	void CollisionCheck(float _DeltaTime);
	void SendMapInDoor(APlayer* _Player, float _SendFloatValue);

	UDefaultSceneComponent* Root = nullptr;
	UTileRenderer* TileRenderer = nullptr;
	USpriteRenderer* MapColRenderer = nullptr;
	UCollision* RightNextMapCol = nullptr; // �������� ���� ��.
	UCollision* LeftNextMapCol = nullptr; // ������.
	UStateManager State;

	USpriteRenderer* MapObjectLeftDoor = nullptr; // ��
	UCollision* MapObjectLeftDoorCol = nullptr; // �� Col
	USpriteRenderer* MapObjectRightDoor = nullptr; // ��
	UCollision* MapObjectRightDoorCol = nullptr; // �� Col

	bool StageIsOne = true;
	bool b_RightMapCol = false;
	bool b_LeftMapCol = false;
};

