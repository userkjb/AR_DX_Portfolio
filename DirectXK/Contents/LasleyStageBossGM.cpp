#include "PreCompile.h"
#include "LasleyStageBossGM.h"

#include "Player.h"
#include "LasleyStageBoss.h"
#include "Lasley.h"
#include "BackGround.h"

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

	{
		std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		BackGournd->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, -200.0f });
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

	CameraMove(_DeltaTime);
}

void ALasleyStageBossGM::InStageExit()
{
}
#pragma endregion


#pragma region LasleySummon
void ALasleyStageBossGM::LasleySummonBegin()
{
	Lasley->SetActive(true);

	// Player 키보드 입력 제한.
	if (nullptr != Player)
	{
		Player->SetPlayerStateIdleLock();
	}
}

void ALasleyStageBossGM::LasleySummonTick(float _DeltaTime)
{

	std::string LasleyState = Lasley->GetState();
	if (LasleyState != "Summons") // 라슬리의 상태가 Idle로 넘어감.
	{
		DelayTime += _DeltaTime;
		if (3.0f <= DelayTime)
		{
			// 약간의 딜레이 있어야 함.
			// 정확히는 UI 이벤트가 끝나야 함.
			LevelState.ChangeState("LasleyBattle");
			return;
		}
	}

	LasleySummonCameraMove(_DeltaTime);
}

void ALasleyStageBossGM::LasleySummonExit()
{
}
#pragma endregion

#pragma region LasleyBattle
void ALasleyStageBossGM::LasleyBattleBegin()
{
	Player->SetPlayerStateIdle();
	Lasley->IsStart();
}

void ALasleyStageBossGM::LasleyBattleTick(float _DeltaTime)
{
	Lasley->GMToPlayerPos(Player->GetActorLocation());

	CameraMove(_DeltaTime);
}

void ALasleyStageBossGM::LasleyBattleExit()
{
}
#pragma endregion

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

	CameraMove(_DeltaTime);
}

void ALasleyStageBossGM::LasleyDieExit()
{
}

void ALasleyStageBossGM::CameraMove(float _DeltaTime)
{
	if (!FreeCamera) // false
	{
		float4 MapSize = UContentsConstValue::MapTexScale;
		float4 GameMapSize = MapSize * UContentsConstValue::AutoSizeValue;
		//float4 ScreenSize = GEngine->EngineWindow.GetWindowScale();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		FVector PlayerPos = Player->GetPlayerPos();

		FVector CameraPos = Camera->GetActorLocation();

		CameraPos.X = PlayerPos.X;
		CameraPos.Y = PlayerPos.Y;

		if (CameraPos.X <= ScreenScaleHalf.X)
		{
			CameraPos.X = ScreenScaleHalf.X;
		}
		else if (CameraPos.X >= (GameMapSize.X - ScreenScaleHalf.X))
		{
			CameraPos.X = (GameMapSize.X - ScreenScaleHalf.X);
		}


		if (CameraPos.Y <= ScreenScaleHalf.Y)
		{
			CameraPos.Y = ScreenScaleHalf.Y;
		}
		else if (CameraPos.Y >= (GameMapSize.Y - ScreenScaleHalf.Y))
		{
			CameraPos.Y = (GameMapSize.Y - ScreenScaleHalf.Y);
		}
		

		Camera->SetActorLocation({ CameraPos.X, CameraPos.Y, -500.0f });
	}
}

void ALasleyStageBossGM::LasleySummonCameraMove(float _DeltaTime)
{
	if (!FreeCamera) // false
	{
		FVector CameraMoveVector = FVector::Zero;

		FVector CameraPos = Camera->GetActorLocation();
		FVector LasleyPos = Lasley->GetActorLocation();
		float CalPos = LasleyPos.X - CameraPos.X;
		if (0 > CalPos)
		{
			CalPos *= -1.0f;
		}

		if (10.0 <= CalPos)
		{
			CameraMoveVector = FVector::Right * CameraMoveSpeed * _DeltaTime;
			Camera->AddActorLocation(CameraMoveVector);
		}
	}
}
