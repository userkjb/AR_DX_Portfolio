#pragma once
#include <EngineCore/GameMode.h>

class ALasleyStageTwoMap;
class ALasleyStageTwoGM : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ALasleyStageTwoGM();
	~ALasleyStageTwoGM();

	// delete Function
	ALasleyStageTwoGM(const ALasleyStageTwoGM& _Other) = delete;
	ALasleyStageTwoGM(ALasleyStageTwoGM&& _Other) noexcept = delete;
	ALasleyStageTwoGM& operator=(const ALasleyStageTwoGM& _Other) = delete;
	ALasleyStageTwoGM& operator=(ALasleyStageTwoGM&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private :
	void InitState();

	void BattleBegin();
	void BattleTick(float _DeltaTime);
	void BattleExit();

	bool FreeCamera = false;
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<ALasleyStageTwoMap> MapActor;

	UStateManager State;
};

