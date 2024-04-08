#pragma once
#include <EngineCore/GameMode.h>

class ALasleyGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public :
	// constrcuter destructer
	ALasleyGameMode();
	~ALasleyGameMode();

	// delete Function
	ALasleyGameMode(const ALasleyGameMode& _Other) = delete;
	ALasleyGameMode(ALasleyGameMode&& _Other) noexcept = delete;
	ALasleyGameMode& operator=(const ALasleyGameMode& _Other) = delete;
	ALasleyGameMode& operator=(ALasleyGameMode&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
};

