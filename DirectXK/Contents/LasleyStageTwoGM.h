#pragma once
#include <EngineCore/GameMode.h>

class ALasleyStageTwoMap;
class APlayer;
class AWyvern;
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


	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void BattleBegin();
	void BattleTick(float _DeltaTime);
	void BattleExit();

	void CameraMove(float _DeltaTime);


	bool FreeCamera = false;
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<ALasleyStageTwoMap> MapActor = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<AWyvern> BlackSphere = nullptr;

	UStateManager LevelState;
	bool IsOne = true;
};

