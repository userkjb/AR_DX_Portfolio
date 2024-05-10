#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
class ATownGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATownGameMode();
	~ATownGameMode();

	// delete Function
	ATownGameMode(const ATownGameMode& _Other) = delete;
	ATownGameMode(ATownGameMode&& _Other) noexcept = delete;
	ATownGameMode& operator=(const ATownGameMode& _Other) = delete;
	ATownGameMode& operator=(ATownGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private :
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<APlayer> Player;
	UEngineSoundPlayer Sound;
	bool FreeCamera = false;
};

