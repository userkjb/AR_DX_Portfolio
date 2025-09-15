#include "PreCompile.h"
#include "DungeonEntrance.h"
#include <EngineCore/DefaultSceneComponent.h>

ADungeonEntrance::ADungeonEntrance()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	EntranceRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EntranceRenderer->SetupAttachment(Root);
	EntranceRenderer->SetOrder(ERenderOrder::StageDoor);
}

ADungeonEntrance::~ADungeonEntrance()
{
}

void ADungeonEntrance::BeginPlay()
{
	EntranceRenderer->SetSprite("Sign.png");
	EntranceRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ADungeonEntrance::Tick(float _DeltaTime)
{
}
