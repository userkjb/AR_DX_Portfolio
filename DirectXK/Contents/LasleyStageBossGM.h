#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
class ALasleyStageBoss;
class ALasley;
class ALasleyStageBossGM : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ALasleyStageBossGM();
	~ALasleyStageBossGM();

	// delete Function
	ALasleyStageBossGM(const ALasleyStageBossGM& _Other) = delete;
	ALasleyStageBossGM(ALasleyStageBossGM&& _Other) noexcept = delete;
	ALasleyStageBossGM& operator=(const ALasleyStageBossGM& _Other) = delete;
	ALasleyStageBossGM& operator=(ALasleyStageBossGM&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private :
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<APlayer> Player;
	std::shared_ptr<ALasleyStageBoss> BossMap;
	std::shared_ptr<ALasley> Lasley;


	bool FreeCamera = false;

	UStateManager LevelState;
	void LevelStateInit();

	void InStageBegin();
	void InStageTick(float _DeltaTime);
	void InStageExit();
	void LasleySummonBegin();
	void LasleySummonTick(float _DeltaTime);
	void LasleySummonExit();
	void LasleyBattleBegin();
	void LasleyBattleTick(float _DeltaTime);
	void LasleyBattleExit();
	void PlayerDieBegin();
	void PlayerDieTick(float _DeltaTime);
	void PlayerDieExit();
	void LasleyDieBegin();
	void LasleyDieTick(float _DeltaTime);
	void LasleyDieExit();

	void CameraMove(float _DeltaTime);
};

