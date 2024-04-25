#pragma once
#include <EngineCore/Actor.h>

// 설명 :
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
	USpriteRenderer* StageDoor = nullptr; // 스테이지 입장 했을 때 큰 문.
	UCollision* LeftMapCol = nullptr;
	UCollision* DownMapCol = nullptr; // 후추.

	bool b_LeftMapCol = false;
	bool b_DownMapCol = false;

	/// <summary>
	/// 타일맵 데이터 읽어서 출력.
	/// </summary>
	void CreateMapImage();
	
	void CreateAnimation();

	void CollisionCheck(float _DeltaTime);
};

