#include "PreCompile.h"
#include "LasleyStageOne.h"
#include <EngineCore/DefaultSceneComponent.h>

ALasleyStageOne::ALasleyStageOne()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	MapRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapRenderer->SetupAttachment(Root);	
	MapRenderer->SetActive(true);
	
	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);	
	MapColRenderer->SetActive(false);

	SetRoot(Root);

	InputOn(); // test
}

ALasleyStageOne::~ALasleyStageOne()
{
}

void ALasleyStageOne::BeginPlay()
{
	Super::BeginPlay();

	MapRenderer->SetSprite("StartStage.png");
	MapRenderer->SetAutoSize(4.0f, true);
	MapRenderer->SetOrder(ERenderOrder::Map);

	MapColRenderer->SetSprite("StartStageCol.png");
	MapColRenderer->SetAutoSize(4.0f, true);
	MapColRenderer->SetOrder(ERenderOrder::MapCol);
}

void ALasleyStageOne::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown('O'))
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
