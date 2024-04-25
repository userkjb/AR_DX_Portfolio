#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
class ALasleyStageBoss;
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

	void test()
	{
		int a = 0;
	}

	int i_test = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private :
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<APlayer> Player;
	std::shared_ptr<ALasleyStageBoss> BossMap;
};

