#include "PreCompile.h"
#include "GameTitleBG.h"
#include <EngineCore/DefaultSceneComponent.h>

AGameTitleBG::AGameTitleBG()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	BackGround_Cloud = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	BackGround_Cloud->SetupAttachment(Root);
}

AGameTitleBG::~AGameTitleBG()
{
}

void AGameTitleBG::BeginPlay()
{
	Super::BeginPlay();

	BackGround_Cloud->SetSprite("BackCloud.png");
	BackGround_Cloud->SetAutoSize(4.0f, true);
}

void AGameTitleBG::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	VertexPlus.X += _DeltaTime * 0.025f;
	BackGround_Cloud->SetVertexUVPlus(VertexPlus);
}
