#include "PreCompile.h"
#include "LasleyStageTwoGM.h"

#include "LasleyStageTwoMap.h"
#include "Player.h"

ALasleyStageTwoGM::ALasleyStageTwoGM()
{
}

ALasleyStageTwoGM::~ALasleyStageTwoGM()
{
}

void ALasleyStageTwoGM::BeginPlay()
{
	Super::BeginPlay();

	{
		Camera = GetWorld()->GetMainCamera();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}
}

void ALasleyStageTwoGM::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelState.Update(_DeltaTime);

	if (true == UEngineInput::IsDown(0x30)) // Å°º¸µå 0
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

void ALasleyStageTwoGM::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Stage_2_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Player
	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation({ 1550.0f,  190.0f, 0.0f });
	}

	{
		MapActor = GetWorld()->SpawnActor<ALasleyStageTwoMap>("StageTwoMap", ERenderOrder::Map);
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		MapActor->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}


	InitState();
}

void ALasleyStageTwoGM::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALasleyStageTwoGM::InitState()
{
	LevelState.CreateState("Idle");
	LevelState.CreateState("Battle");


	LevelState.SetFunction("Battle",
		std::bind(&ALasleyStageTwoGM::BattleBegin, this),
		std::bind(&ALasleyStageTwoGM::BattleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoGM::BattleExit, this));


	LevelState.ChangeState("Battle");
}



void ALasleyStageTwoGM::BattleBegin()
{
}

void ALasleyStageTwoGM::BattleTick(float _DeltaTime)
{
	CameraMove(_DeltaTime);
}

void ALasleyStageTwoGM::BattleExit()
{
}





void ALasleyStageTwoGM::CameraMove(float _DeltaTime)
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