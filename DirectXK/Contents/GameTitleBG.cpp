#include "PreCompile.h"
#include "GameTitleBG.h"
#include <EngineCore/DefaultSceneComponent.h>

AGameTitleBG::AGameTitleBG()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	BackGround_Cloud_1 = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Cloud_1->SetupAttachment(Root);

	BackGround_Cloud_2 = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Cloud_2->SetupAttachment(Root);

	BackGround_Cloud_3 = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Cloud_3->SetupAttachment(Root);
}

AGameTitleBG::~AGameTitleBG()
{
}

void AGameTitleBG::BeginPlay()
{
	Super::BeginPlay();

	BackGround_Cloud_1->SetSprite("BackCloud.png");
	BackGround_Cloud_1->SetAutoSize(4.0f, true);
}

void AGameTitleBG::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	VertexPlus.X += _DeltaTime;
	BackGround_Cloud_1->SetVertexUVPlus(VertexPlus);
}
