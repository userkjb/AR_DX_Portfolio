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
	
	DungeonEat = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	DungeonEat->SetupAttachment(Root);

	DungeonInCol = CreateDefaultSubObject<UCollision>("Collision");
	DungeonInCol->SetupAttachment(Root);
	DungeonInCol->SetCollisionGroup(ECollisionOrder::Boss);
	DungeonInCol->SetCollisionType(ECollisionType::RotRect);
}

ATownMap::~ATownMap()
{
}

void ATownMap::BeginPlay()
{
	Super::BeginPlay();

	MapImage->SetAutoSize(4.0f, true);
	MapCol->SetAutoSize(4.0f, true);
	DungeonEat->SetAutoSize(4.0f, true);
	DungeonEat->SetOrder(ERenderOrder::StageDoor);
	DungeonEat->SetPosition(FVector(-4000.0f, -500.0f));
	DungeonEat->SetActive(false);

	DungeonInCol->SetScale(FVector(100.0f, 100.0f));
	DungeonInCol->SetPosition(DungeonEat->GetWorldPosition());

	StateInit();
	CreateAnimation();

#ifdef _DEBUG
	InputOn(); // test
#endif
}

void ATownMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	CollisionCheck(_DeltaTime);
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

void ATownMap::CreateAnimation()
{
	DungeonEat->CreateAnimation("DungeonEat_Up", "DungeonEat", 0.125f, false, 0, 3);
	DungeonEat->CreateAnimation("DungeonEat_Ing", "DungeonEat", 0.125f, true, 4, 8);
	DungeonEat->CreateAnimation("DungeonEat_Down", "DungeonEat", 0.125f, false, 9, 27);

	DungeonEat->ChangeAnimation("DungeonEat_Up");
}

void ATownMap::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");
	State.CreateState("Up");
	State.CreateState("Ing");
	State.CreateState("Down");

	State.SetStartFunction("None", std::bind(&ATownMap::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ATownMap::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Up",
		std::bind(&ATownMap::IdleBegin, this),
		std::bind(&ATownMap::IdleTick, this, std::placeholders::_1),
		std::bind(&ATownMap::IdleExit, this));

	State.SetFunction("Up",
		std::bind(&ATownMap::UpBegin, this),
		std::bind(&ATownMap::UpTick, this, std::placeholders::_1),
		std::bind(&ATownMap::UpExit, this));
	State.SetFunction("Ing",
		std::bind(&ATownMap::IngBegin, this),
		std::bind(&ATownMap::IngTick, this, std::placeholders::_1),
		std::bind(&ATownMap::IngExit, this));
	State.SetFunction("Down",
		std::bind(&ATownMap::DownBegin, this),
		std::bind(&ATownMap::DownTick, this, std::placeholders::_1),
		std::bind(&ATownMap::DownExit, this));

	State.ChangeState("None");
}



void ATownMap::NoneBegin()
{
}

void ATownMap::NoneTick(float _DeltaTime)
{
	int a = 0;
}



void ATownMap::IdleBegin()
{
}

void ATownMap::IdleTick(float _DeltaTime)
{
	int a = 0;
}

void ATownMap::IdleExit()
{
}



void ATownMap::UpBegin()
{
}

void ATownMap::UpTick(float _DeltaTime)
{
}

void ATownMap::UpExit()
{
}

void ATownMap::IngBegin()
{
}

void ATownMap::IngTick(float _DeltaTime)
{
}

void ATownMap::IngExit()
{
}

void ATownMap::DownBegin()
{
}

void ATownMap::DownTick(float _DeltaTime)
{
}

void ATownMap::DownExit()
{
}


void ATownMap::CollisionCheck(float _DeltaTime)
{
	DungeonInCol->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			State.ChangeState("Up");
			return;
		}
	);
}