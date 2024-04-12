#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* MapRenderer;
	USpriteRenderer* MapColRenderer;

};

