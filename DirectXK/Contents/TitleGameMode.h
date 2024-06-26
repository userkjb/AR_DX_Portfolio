#pragma once
#include <EngineCore/GameMode.h>

class ATitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public :
	// constrcuter destructer
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private :
	void CreateBird(float _DeltaTime);

	float BirdTime = 0.0f;

	UEngineSoundPlayer Sound;
};

