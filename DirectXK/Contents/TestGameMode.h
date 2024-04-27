#pragma once
#include "TileMapLevel.h"

// ���� :
class ATestGameMode : public ATileMapLevel
{
	GENERATED_BODY(ATileMapLevel)

public:
	// constrcuter destructer
	ATestGameMode();
	~ATestGameMode();

	// delete Function
	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

	std::atomic_int LoadingCount; // Thread

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	std::vector<std::shared_ptr<UEngineThread>> LoadingThreads; // Thread
	std::shared_ptr<UCamera> Camera = nullptr;
};

