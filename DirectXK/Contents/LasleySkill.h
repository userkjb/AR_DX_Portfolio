#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ALasleySkill : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALasleySkill();
	~ALasleySkill();

	// delete Function
	ALasleySkill(const ALasleySkill& _Other) = delete;
	ALasleySkill(ALasleySkill&& _Other) noexcept = delete;
	ALasleySkill& operator=(const ALasleySkill& _Other) = delete;
	ALasleySkill& operator=(ALasleySkill&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};

