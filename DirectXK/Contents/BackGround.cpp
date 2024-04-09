#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("BGLayer.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::BackGroundImage);
}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
