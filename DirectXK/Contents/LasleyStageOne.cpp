#include "PreCompile.h"
#include "LasleyStageOne.h"
#include <EngineCore/DefaultSceneComponent.h>

ALasleyStageOne::ALasleyStageOne()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	MapRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapRenderer->SetupAttachment(Root);
	MapRenderer->SetActive(true);
	
	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);
	
	InputOn(); // test
}

ALasleyStageOne::~ALasleyStageOne()
{
}

void ALasleyStageOne::BeginPlay()
{
	Super::BeginPlay();

	MapRenderer->SetSprite("StartStage.png");
	MapRenderer->SetAutoSize(3.0f, true);
	MapRenderer->SetOrder(ERenderOrder::Map);

	MapColRenderer->SetSprite("StartStageCol.png");
	MapColRenderer->SetAutoSize(3.0f, true);
	MapColRenderer->SetOrder(ERenderOrder::Map);
}

void ALasleyStageOne::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown('I'))
	{
		if (true == MapRenderer->IsActive() && false == MapColRenderer->IsActive())
		{
			MapRenderer->SetActive(false);
			MapColRenderer->SetActive(true);
		}
		else
		{
			MapRenderer->SetActive(true);
			MapColRenderer->SetActive(false);
		}
	}
}
