#include "PreCompile.h"
#include "LasleyStageBossGM.h"

#include "LasleyStageBoss.h"

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
}

void ALasleyStageBossGM::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Boss_Stage_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Player
	{

	}

	{
		BossMap = GetWorld()->SpawnActor<ALasleyStageBoss>("StageBossMap", ERenderOrder::Map);
		
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		BossMap->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}
}

void ALasleyStageBossGM::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
