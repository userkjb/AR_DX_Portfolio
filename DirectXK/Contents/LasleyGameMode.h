#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
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

	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private :
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<APlayer> Player;

	bool FreeCamera = false;
};

