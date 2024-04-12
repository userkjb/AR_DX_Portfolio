#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
class AGameStartGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public :
	// constrcuter destructer
	AGameStartGameMode();
	~AGameStartGameMode();

	// delete Function
	AGameStartGameMode(const AGameStartGameMode& _Other) = delete;
	AGameStartGameMode(AGameStartGameMode&& _Other) noexcept = delete;
	AGameStartGameMode& operator=(const AGameStartGameMode& _Other) = delete;
	AGameStartGameMode& operator=(AGameStartGameMode&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private :
	void StateInit();

	std::shared_ptr<APlayer> Player = nullptr;
	float4 PlayerPos = float4::Zero;
	UStateManager State;
};

