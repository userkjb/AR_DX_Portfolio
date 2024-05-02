#include "PreCompile.h"
#include "LasleyStageTwoGM.h"

#include "LasleyStageTwoMap.h"

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

	State.Update(_DeltaTime);

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
	State.CreateState("Idle");
	State.CreateState("Battle");


	State.SetFunction("Battle",
		std::bind(&ALasleyStageTwoGM::BattleBegin, this),
		std::bind(&ALasleyStageTwoGM::BattleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoGM::BattleExit, this));


	State.ChangeState("Idle");
}

void ALasleyStageTwoGM::BattleBegin()
{
}

void ALasleyStageTwoGM::BattleTick(float _DeltaTime)
{
}

void ALasleyStageTwoGM::BattleExit()
{
}
