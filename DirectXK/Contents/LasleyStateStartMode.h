#pragma once
#include <EngineCore/GameMode.h>

class ALasleyStateStartMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public :
	// constrcuter destructer
	ALasleyStateStartMode();
	~ALasleyStateStartMode();

	// delete Function
	ALasleyStateStartMode(const ALasleyStateStartMode& _Other) = delete;
	ALasleyStateStartMode(ALasleyStateStartMode&& _Other) noexcept = delete;
	ALasleyStateStartMode& operator=(const ALasleyStateStartMode& _Other) = delete;
	ALasleyStateStartMode& operator=(ALasleyStateStartMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private :

};

