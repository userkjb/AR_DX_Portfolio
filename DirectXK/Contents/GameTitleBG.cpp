#include "PreCompile.h"
#include "GameTitleBG.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineBase/EngineRandom.h>
#include "TitleCloud.h"

AGameTitleBG::AGameTitleBG()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	BackGround_Sky = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Sky->SetupAttachment(Root);
	BackGround_Sky->SetOrder(ERenderOrder::MapBack);

	BackGround_Cloud = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Cloud->SetupAttachment(Root);
	BackGround_Cloud->SetOrder(ERenderOrder::Map);
}

AGameTitleBG::~AGameTitleBG()
{
}

void AGameTitleBG::BeginPlay()
{
	Super::BeginPlay();

	BackGround_Sky->SetSprite("TitleSky.png");
	BackGround_Sky->SetAutoSize(UContentsConstValue::AutoSizeValue, true);

	BackGround_Cloud->SetSprite("BackCloud.png");
	BackGround_Cloud->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void AGameTitleBG::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	VertexPlus.X += _DeltaTime * 0.025f;
	BackGround_Cloud->SetVertexUVPlus(VertexPlus);

	CreateCloud(_DeltaTime);
}

void AGameTitleBG::CreateCloud(float _DeltaTime)
{
	CreateCloudTime += _DeltaTime;
	int CreateTime = static_cast<int>(CreateCloudTime);
	if (0 == CreateTime % 1 && 1.0f <= CreateCloudTime)
	{
		float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();
		float PositionY = UEngineRandom::MainRandom.RandomFloat(-ScreenScale.hY(), ScreenScale.hY());
		float SpeedRan = UEngineRandom::MainRandom.RandomFloat(200.0f, 500.0f);
		int CloudSprite = UEngineRandom::MainRandom.RandomInt(0, 1);
		int CloudRender = UEngineRandom::MainRandom.RandomInt(0, 1);

		std::shared_ptr<ATitleCloud> Cloud = GetWorld()->SpawnActor<ATitleCloud>("Bird", EObjectOrder::Map_Object);
		Cloud->SetCreateActorPos(FVector(ScreenScale.X, PositionY));
		Cloud->SetSpriteVal(CloudSprite);
		Cloud->SetCloudRenderOrder(CloudRender);
		Cloud->SetMoveSpeed(SpeedRan);

		Cloud->CloudCreate();
		CreateCloudTime = 0.0f;
	}
}
