#pragma once
#include <EngineCore/Actor.h>

// ���� :
class USpriteRenderer;
class UTileRenderer;
class UDefaultSceneComponent;
class ALasleyStageOne : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALasleyStageOne();
	~ALasleyStageOne();

	// delete Function
	ALasleyStageOne(const ALasleyStageOne& _Other) = delete;
	ALasleyStageOne(ALasleyStageOne&& _Other) noexcept = delete;
	ALasleyStageOne& operator=(const ALasleyStageOne& _Other) = delete;
	ALasleyStageOne& operator=(ALasleyStageOne&& _Other) noexcept = delete;

	inline bool IsLeftMapCol() const
	{
		return b_LeftMapCol;
	}

	inline bool IsDownMapCol() const
	{
		return b_DownMapCol;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* Root = nullptr;
	UTileRenderer* TileRenderer = nullptr;
	USpriteRenderer* MapColRenderer = nullptr;
	USpriteRenderer* StageDoor = nullptr; // �������� ���� ���� �� ū ��.
	UCollision* LeftMapCol = nullptr;
	UCollision* DownMapCol = nullptr; // ����.

	bool b_LeftMapCol = false;
	bool b_DownMapCol = false;

	/// <summary>
	/// Ÿ�ϸ� ������ �о ���.
	/// </summary>
	void CreateMapImage();
	
	void CreateAnimation();

	void CollisionCheck(float _DeltaTime);
};

