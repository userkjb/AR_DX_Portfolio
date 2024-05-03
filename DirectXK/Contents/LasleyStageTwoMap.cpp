#include "PreCompile.h"
#include "LasleyStageTwoMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TileRenderer.h>

ALasleyStageTwoMap::ALasleyStageTwoMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");

	RightNextMapCol = CreateDefaultSubObject<UCollision>("Renderer");
	RightNextMapCol->SetupAttachment(Root);
	RightNextMapCol->SetScale(FVector{ 64.0, 280.0, 1.0f });
	RightNextMapCol->SetCollisionGroup(ECollisionOrder::NextMap);
	RightNextMapCol->SetCollisionType(ECollisionType::RotRect);
	RightNextMapCol->SetPosition(FVector{ 832.0f, -195.0f, 0.0f });
	RightNextMapCol->SetActive(false);

	LeftNextMapCol = CreateDefaultSubObject<UCollision>("Renderer");
	LeftNextMapCol->SetupAttachment(Root);
	LeftNextMapCol->SetScale(FVector{ 64.0, 280.0, 1.0f });
	LeftNextMapCol->SetCollisionGroup(ECollisionOrder::NextMap);
	LeftNextMapCol->SetCollisionType(ECollisionType::RotRect);
	LeftNextMapCol->SetPosition(FVector{ -832.0f, -195.0f, 0.0f });
	LeftNextMapCol->SetActive(false);

	MapObjectLeftDoor = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapObjectLeftDoor->SetupAttachment(Root);
	MapObjectLeftDoor->SetPivot(EPivot::MAX);
	MapObjectLeftDoor->SetOrder(ERenderOrder::MapObject);
	MapObjectLeftDoor->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	MapObjectLeftDoor->SetActive(false);

	MapObjectRightDoor = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapObjectRightDoor->SetupAttachment(Root);
	MapObjectRightDoor->SetPivot(EPivot::MAX);
	MapObjectRightDoor->SetOrder(ERenderOrder::MapObject);
	MapObjectRightDoor->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	MapObjectRightDoor->SetActive(false);

	MapObjectLeftDoorCol = CreateDefaultSubObject<UCollision>("RendererCol");
	MapObjectLeftDoorCol->SetupAttachment(Root);
	MapObjectLeftDoorCol->SetCollisionGroup(ECollisionOrder::MapDoor);
	MapObjectLeftDoorCol->SetCollisionType(ECollisionType::RotRect);
	MapObjectLeftDoorCol->SetActive(false);

	MapObjectRightDoorCol = CreateDefaultSubObject<UCollision>("RendererCol");
	MapObjectRightDoorCol->SetupAttachment(Root);
	MapObjectRightDoorCol->SetCollisionGroup(ECollisionOrder::MapDoor);
	MapObjectRightDoorCol->SetCollisionType(ECollisionType::RotRect);
	MapObjectRightDoorCol->SetActive(false);

	InputOn(); // test
}

ALasleyStageTwoMap::~ALasleyStageTwoMap()
{
}

void ALasleyStageTwoMap::BeginPlay()
{
	Super::BeginPlay();

	float CSize = UContentsConstValue::AutoSizeValue; // const

	MapColRenderer->SetSprite("Stage_2_Col.png");
	MapColRenderer->SetAutoSize(CSize, true); // const Size
	MapColRenderer->SetOrder(ERenderOrder::MapCol);

	CreateMapImage();
	CreateAnimation();
	StateInit();

	MapObjectRightDoor->SetPosition(FVector{ 800.0f, -195.0f, 0.0f });
	MapObjectRightDoor->SetRotationDeg({ 0.0f, 0.0f, -90.0f });
	MapObjectLeftDoor->SetPosition(FVector{ -800.0f, -195.0f, 0.0f });
	MapObjectLeftDoor->SetRotationDeg({ 0.0f, 0.0f, 90.0f });

	FVector DoorScale = MapObjectRightDoor->GetLocalScale();
	MapObjectRightDoorCol->SetScale({ DoorScale.Y, DoorScale.X });
	MapObjectRightDoorCol->SetPosition(MapObjectRightDoor->GetLocalPosition());
	
	MapObjectLeftDoorCol->SetScale({ DoorScale.Y, DoorScale.X });
	MapObjectLeftDoorCol->SetPosition(MapObjectLeftDoor->GetLocalPosition());
}

void ALasleyStageTwoMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	CollisionCheck(_DeltaTime);

	if (true == IsDown('O'))
	{
		if (false == MapColRenderer->IsActive())
		{
			MapColRenderer->SetActive(true);
		}
		else
		{
			MapColRenderer->SetActive(false);
		}
	}
}

void ALasleyStageTwoMap::StateInit()
{
	State.CreateState("StageIn");
	State.CreateState("StageIdle");
	State.CreateState("StageBattle");

	State.SetFunction("StageIn",
		std::bind(&ALasleyStageTwoMap::StageInBegin, this),
		std::bind(&ALasleyStageTwoMap::StageInTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoMap::StageInExit, this));
	
	State.SetFunction("StageIdle",
		std::bind(&ALasleyStageTwoMap::StageIdleBegin, this),
		std::bind(&ALasleyStageTwoMap::StageIdleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoMap::StageIdleExit, this));
	
	State.SetFunction("StageBattle",
		std::bind(&ALasleyStageTwoMap::StageBattleBegin, this),
		std::bind(&ALasleyStageTwoMap::StageBattleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoMap::StageBattleExit, this));


	State.ChangeState("StageIn");
}

void ALasleyStageTwoMap::CreateAnimation()
{
	MapObjectRightDoor->SetSprite("Stele");
	MapObjectRightDoor->CreateAnimation("Stele_CloseRightDoor", "Stele", 0.125f, false, 0, 8);
	MapObjectRightDoor->CreateAnimation("Stele_IdleRightDoor", "Stele", 0.125f, true, 8, 15);
	MapObjectRightDoor->CreateAnimation("Stele_OpenRightDoor", "Stele", 0.125f, false, 16, 23);
		
	MapObjectLeftDoor->SetSprite("Stele");
	MapObjectLeftDoor->CreateAnimation("Stele_CloseLeftDoor", "Stele", 0.125f, false, 0, 8);
	MapObjectLeftDoor->CreateAnimation("Stele_IdleLeftDoor", "Stele", 0.125f, true, 8, 15);
	MapObjectLeftDoor->CreateAnimation("Stele_OpenLeftDoor", "Stele", 0.125f, false, 16, 23);


	MapObjectRightDoor->ChangeAnimation("Stele_CloseRightDoor");
	MapObjectLeftDoor->ChangeAnimation("Stele_CloseLeftDoor");
}

void ALasleyStageTwoMap::CreateMapImage()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	Dir.Move("TileMapData");

	std::vector<std::vector<int>> TileData;
	std::string FileName = "";
	UEngineSerializer Ser;

	UEngineFile File = Dir.GetPathFromFile("DarkStage_2.Data");
	File.Open(EIOOpenMode::Read, EIODataType::Binary);
	File.Load(Ser);

	Ser >> FileName;
	Ser >> TileData;

	File.Close();

	size_t ImageXSize = TileData[0].size();
	size_t ImageYSize = TileData.size();

	//TileRenderer->CreateTileMap("Map4X(64).png", { 64, 64 }, static_cast<int>(TileData[0].size()), static_cast<int>(TileData.size()), 0);
	//TileRenderer->CreateTileMap("DarkDesert_Sprite.png", { 64, 64 }, static_cast<int>(TileData[0].size()), static_cast<int>(TileData.size()), 0);
	TileRenderer->CreateTileMap(FileName, { 64, 64 }, static_cast<int>(TileData[0].size()), static_cast<int>(TileData.size()), 0);

	for (size_t y = 0; y < ImageYSize; y++)
	{
		for (size_t x = 0; x < ImageXSize; x++)
		{
			int ix = static_cast<int>(x);
			int iy = static_cast<int>(y);
			TileRenderer->SetTile(ix, iy, TileData[iy][ix]);
		}
	}

	TileRenderer->SetOrder(ERenderOrder::Map);
	TileRenderer->SetPosition({ 0.0, 0.0, -10.0f });
}



void ALasleyStageTwoMap::StageInBegin()
{
}

void ALasleyStageTwoMap::StageInTick(float _DeltaTime)
{
	if (true == StageIsOne)
	{
		State.ChangeState("StageBattle");
		return;
	}
	else
	{
		State.ChangeState("StageIdle");
		return;
	}
}

void ALasleyStageTwoMap::StageInExit()
{
}


void ALasleyStageTwoMap::StageIdleBegin()
{
	MapObjectRightDoor->ChangeAnimation("Stele_OpenRightDoor");
	MapObjectLeftDoor->ChangeAnimation("Stele_OpenLeftDoor");
}

void ALasleyStageTwoMap::StageIdleTick(float _DeltaTime)
{
	MapObjectRightDoor->SetLastFrameCallback("Stele_OpenRightDoor", [=]()
		{
			MapObjectRightDoorCol->SetActive(false);
			MapObjectRightDoor->SetActive(false);
			RightNextMapCol->SetActive(true);
		}
	);
	MapObjectLeftDoor->SetLastFrameCallback("Stele_OpenLeftDoor", [=]()
		{
			MapObjectLeftDoorCol->SetActive(false);
			MapObjectLeftDoor->SetActive(false);
			LeftNextMapCol->SetActive(true);
		}
	);
}

void ALasleyStageTwoMap::StageIdleExit()
{
}



void ALasleyStageTwoMap::StageBattleBegin()
{
	MapObjectRightDoor->SetActive(true);
	MapObjectRightDoor->ChangeAnimation("Stele_CloseRightDoor");
	MapObjectLeftDoor->SetActive(true);
	MapObjectLeftDoor->ChangeAnimation("Stele_CloseLeftDoor");

	// 몬스터 소환.
}

void ALasleyStageTwoMap::StageBattleTick(float _DeltaTime)
{
	MapObjectRightDoor->SetLastFrameCallback("Stele_CloseRightDoor", [=]()
		{
			MapObjectRightDoorCol->SetActive(true);
			MapObjectRightDoor->ChangeAnimation("Stele_IdleRightDoor");
		}
	);
	MapObjectLeftDoor->SetLastFrameCallback("Stele_CloseLeftDoor", [=]()
		{
			MapObjectLeftDoorCol->SetActive(true);
			MapObjectLeftDoor->ChangeAnimation("Stele_IdleLeftDoor");
		}
	);


	// test
	if (true == IsDown('P'))
	{
		State.ChangeState("StageIdle");
		b_BattleEnd = true;
		return;
	}
}

void ALasleyStageTwoMap::StageBattleExit()
{
}


void ALasleyStageTwoMap::CollisionCheck(float _DeltaTime)
{
	RightNextMapCol->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			b_RightMapCol = true;
		}
	);

	LeftNextMapCol->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			b_LeftMapCol = true;
		}
	);
}
