#include "PreCompile.h"
#include "LasleyStageMap.h"
#include <EngineCore/SpriteRenderer.h>

ALasleyStageMap::ALasleyStageMap()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Map");
}

ALasleyStageMap::~ALasleyStageMap()
{
}

void ALasleyStageMap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("StartStage.png");

	Renderer->SetAutoSize(1.0f, true);

	Renderer->SetOrder(ERenderOrder::Map);
}

void ALasleyStageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
