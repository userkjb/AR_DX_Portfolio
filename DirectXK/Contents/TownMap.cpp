#include "PreCompile.h"
#include "TownMap.h"
#include <EngineCore/DefaultSceneComponent.h>

ATownMap::ATownMap()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	MapImage = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapImage->SetupAttachment(Root);
	MapImage->SetOrder(ERenderOrder::Map);
	MapImage->SetSprite("Town.png");
	MapImage->SetActive(true);


	MapCol = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapCol->SetupAttachment(Root);
	MapCol->SetOrder(ERenderOrder::MapCol);
	MapCol->SetSprite("Town_Col.png");
	MapCol->SetActive(false);
	
}

ATownMap::~ATownMap()
{
}

void ATownMap::BeginPlay()
{
	Super::BeginPlay();
	
	MapImage->SetAutoSize(4.0f, true);
	MapCol->SetAutoSize(4.0f, true);

#ifdef _DEBUG
	InputOn(); // test
#endif
}

void ATownMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

#ifdef _DEBUG
	
	if (true == IsDown('O'))
	{
		if (false == MapImage->IsActive())
		{
			MapCol->SetActive(false);
			MapImage->SetActive(true);
		}
		else
		{
			MapCol->SetActive(true);
			MapImage->SetActive(false);
		}
	}
#endif
}
