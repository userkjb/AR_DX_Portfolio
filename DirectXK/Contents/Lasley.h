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

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void DevilEyeBegin();
	void DevilEyeTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void WakeBegin();
	void WakeTick(float _DeltaTime);
	void DemonicBladeBegin();
	void DemonicBladeTick(float _DeltaTime);
	void DimensionCutterBegin();
	void DimensionCutterTick(float _DeltaTime);
	void DoubleDimensionCutterBegin();
	void DoubleDimensionCutterTick(float _DeltaTime);
	void DownBegin();
	void DownTick(float _DeltaTime);

	USpriteRenderer* LasleyRenderer = nullptr;

	ELasleyState State = ELasleyState::None;
};

