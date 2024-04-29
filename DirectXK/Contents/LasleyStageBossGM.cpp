#include "PreCompile.h"
#include "LasleyStageBossGM.h"

#include "Player.h"
#include "LasleyStageBoss.h"
#include "Lasley.h"

ALasleyStageBossGM::ALasleyStageBossGM()
{
}

ALasleyStageBossGM::~ALasleyStageBossGM()
{
}

void ALasleyStageBossGM::BeginPlay()
{
	Super::BeginPlay();

	{
		Camera = GetWorld()->GetMainCamera();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}
}

void ALasleyStageBossGM::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelState.Update(_DeltaTime);

	FVector PlayerPos = Player->GetPlayerPos();

	// 맵에 라슬리를 알려줘야 함
	{
		BossMap->SendLasley(Lasley);
	}

	if (true == UEngineInput::IsDown(0x30)) // 키보드 0
	{
		if (FreeCamera)
		{
			FreeCamera = false;
		}
		else
		{
			FreeCamera = true;
		}
	}
	if (!FreeCamera) // false
	{
		float4 MapSize = UContentsConstValue::MapTexScale;
		float4 ScreenSize = GEngine->EngineWindow.GetWindowScale();

		Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -100.0f });
	}
}

void ALasleyStageBossGM::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Boss_Stage_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Player
	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation({ 160.0f,  125.0f, 0.0f });
	}

	{
		BossMap = GetWorld()->SpawnActor<ALasleyStageBoss>("StageBossMap", ERenderOrder::Map);
		
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		BossMap->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}

	{
		Lasley = GetWorld()->SpawnActor<ALasley>("Lasley");
		FVector MapSize = BossMap->GetActorLocation();
		Lasley->SetActorLocation({MapSize.X, 125.0f, 0.0f});
	}

	LevelStateInit();
}

void ALasleyStageBossGM::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALasleyStageBossGM::LevelStateInit()
{
	LevelState.CreateState("InStage");
	LevelState.CreateState("LasleySummon");
	LevelState.CreateState("LasleyBattle");
	{
		LevelState.CreateState("PlayerDie");
		LevelState.CreateState("LasleyDie");
	}

	LevelState.SetFunction("InStage",
		std::bind(&ALasleyStageBossGM::InStageBegin, this),
		std::bind(&ALasleyStageBossGM::InStageTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBossGM::InStageExit, this));

	LevelState.SetFunction("LasleySummon",
		std::bind(&ALasleyStageBossGM::LasleySummonBegin, this),
		std::bind(&ALasleyStageBossGM::LasleySummonTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBossGM::LasleySummonExit, this));

	LevelState.SetFunction("LasleyBattle",
		std::bind(&ALasleyStageBossGM::LasleyBattleBegin, this),
		std::bind(&ALasleyStageBossGM::LasleyBattleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBossGM::LasleyBattleExit, this));

	LevelState.SetFunction("PlayerDie",
		std::bind(&ALasleyStageBossGM::PlayerDieBegin, this),
		std::bind(&ALasleyStageBossGM::PlayerDieTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBossGM::PlayerDieExit, this));

	LevelState.SetFunction("LasleyDie",
		std::bind(&ALasleyStageBossGM::LasleyDieBegin, this),
		std::bind(&ALasleyStageBossGM::LasleyDieTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBossGM::LasleyDieExit, this));

	LevelState.ChangeState("InStage");
}



#pragma region InStage
void ALasleyStageBossGM::InStageBegin()
{
	Lasley->SetActive(false);
}

void ALasleyStageBossGM::InStageTick(float _DeltaTime)
{
	if (true == BossMap->IsBossStageStart())
	{
		LevelState.ChangeState("LasleySummon");
		return;
	}
}

void ALasleyStageBossGM::InStageExit()
{
}
#pragma endregion


void ALasleyStageBossGM::LasleySummonBegin()
{
	Lasley->SetActive(true);
}

void ALasleyStageBossGM::LasleySummonTick(float _DeltaTime)
{
}

void ALasleyStageBossGM::LasleySummonExit()
{
}

void ALasleyStageBossGM::LasleyBattleBegin()
{
}

void ALasleyStageBossGM::LasleyBattleTick(float _DeltaTime)
{
}

void ALasleyStageBossGM::LasleyBattleExit()
{
}

void ALasleyStageBossGM::PlayerDieBegin()
{
}

void ALasleyStageBossGM::PlayerDieTick(float _DeltaTime)
{
}

void ALasleyStageBossGM::PlayerDieExit()
{
}

void ALasleyStageBossGM::LasleyDieBegin()
{
}

void ALasleyStageBossGM::LasleyDieTick(float _DeltaTime)
{
}

void ALasleyStageBossGM::LasleyDieExit()
{
}
