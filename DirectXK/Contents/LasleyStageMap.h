#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class ALasleyStageMap : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	ALasleyStageMap();
	~ALasleyStageMap();

	// delete Function
	ALasleyStageMap(const ALasleyStageMap& _Other) = delete;
	ALasleyStageMap(ALasleyStageMap&& _Other) noexcept = delete;
	ALasleyStageMap& operator=(const ALasleyStageMap& _Other) = delete;
	ALasleyStageMap& operator=(ALasleyStageMap&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	USpriteRenderer* Renderer;
};

