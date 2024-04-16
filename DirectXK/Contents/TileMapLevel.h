#pragma once
#include <EngineCore/GameMode.h>

class ATileMapLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)

public :
	// constructer destructer
	ATileMapLevel();
	virtual ~ATileMapLevel();

	// delete Function
	ATileMapLevel(const ATileMapLevel& _Other) = delete;
	ATileMapLevel(ATileMapLevel&& _Other) noexcept = delete;
	ATileMapLevel& operator=(const ATileMapLevel) = delete;
	ATileMapLevel& operator=(ATileMapLevel&& _Other) noexcept = delete;

	std::shared_ptr<class ATileMap> TileMap = nullptr;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};

