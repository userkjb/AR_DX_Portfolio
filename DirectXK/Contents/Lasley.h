#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnums.h"

class ALasley : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	ALasley();
	~ALasley();

	// delete Function
	ALasley(const ALasley& _Other) = delete;
	ALasley(ALasley&& _Other) noexcept = delete;
	ALasley& operator=(const ALasley& _Other) = delete;
	ALasley& operator=(ALasley&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateChange(ELasleyState _State);
	void StateUpdate(float _DeltaTime);

	void CreateAnimation();


	USpriteRenderer* LasleyRenderer = nullptr;

	ELasleyState State = ELasleyState::None;
};

