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

	FVector PlayerPos = Player->GetPlayerPos();

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
		std::shared_ptr<ALasley> Lasley = GetWorld()->SpawnActor<ALasley>("Lasley");
		Lasley->SetActorLocation({300.0f, 125.0f, 0.0f});
	}
}

void ALasleyStageBossGM::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
