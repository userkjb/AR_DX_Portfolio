#include "PreCompile.h"
#include "LasleyStageBoss.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TileRenderer.h>

ALasleyStageBoss::ALasleyStageBoss()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");

	MapObject = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapObject->SetupAttachment(Root);
	MapObject->SetPivot(EPivot::MAX);
	MapObject->SetOrder(ERenderOrder::MapObject);
	MapObject->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	MapObject->SetActive(false);

	MapObjectCol = CreateDefaultSubObject<UCollision>("RendererCol");
	MapObjectCol->SetupAttachment(MapObject);
	MapObjectCol->SetCollisionGroup(ECollisionOrder::MapDoor);
	MapObjectCol->SetCollisionType(ECollisionType::RotRect);

	BossStageStartCol = CreateDefaultSubObject<UCollision>("BossStageStartCol");
	BossStageStartCol->SetupAttachment(Root);
	BossStageStartCol->SetCollisionGroup(ECollisionOrder::BossStageStart);
	BossStageStartCol->SetCollisionType(ECollisionType::RotRect);
	BossStageStartCol->SetScale(FVector(10.0f, 1000.0f, 10.0f));
	BossStageStartCol->SetPosition({ -576.0f, 0.0f });

	SetRoot(Root);
	InputOn(); // test
}

ALasleyStageBoss::~ALasleyStageBoss()
{
}

void ALasleyStageBoss::BeginPlay()
{
	Super::BeginPlay();

	float CSize = UContentsConstValue::AutoSizeValue; // const
	MapColRenderer->SetSprite("Boss_Stage_Col.png");
	MapColRenderer->SetAutoSize(CSize, true);
	MapColRenderer->SetOrder(ERenderOrder::MapCol);

	CreateMapImage();
	
	CreateAnimation();
	StateInit();
	float Up = (16.0f * 4.0f) * 4.0f;
	float Right = 30.0f;
	MapObject->SetPosition({ (-928.0f + Right), (-608.0f + Up) });
	MapObject->SetRotationDeg({ 1.0f, 1.0f, 90.0f });
}

void ALasleyStageBoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

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

void ALasleyStageBoss::CreateMapImage()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	Dir.Move("TileMapData");

	std::vector<std::vector<int>> TileData;
	std::string FileName = "";
	UEngineSerializer Ser;

	UEngineFile File = Dir.GetPathFromFile("DarkBoss_Stage.Data");
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

void ALasleyStageBoss::StateInit()
{
	State.CreateState("LasleyBossStateIn");
	State.CreateState("LasleyBossStageStart");
	State.CreateState("LasleyBossStageIng");
	State.CreateState("LasleyBossStageEnd");

	State.SetFunction("LasleyBossStateIn",
		std::bind(&ALasleyStageBoss::LasleyBossStageInBegin, this),
		std::bind(&ALasleyStageBoss::LasleyBossStageInTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBoss::LasleyBossStageInExit, this));

	State.SetFunction("LasleyBossStageStart",
		std::bind(&ALasleyStageBoss::LasleyBossStageStartBegin, this),
		std::bind(&ALasleyStageBoss::LasleyBossStageStartTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBoss::LasleyBossStageStartExit, this));

	State.SetFunction("LasleyBossStageIng",
		std::bind(&ALasleyStageBoss::LasleyBossStageIngBegin, this),
		std::bind(&ALasleyStageBoss::LasleyBossStageIngTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBoss::LasleyBossStageIngExit, this));

	State.SetFunction("LasleyBossStageEnd",
		std::bind(&ALasleyStageBoss::LasleyBossStageEndBegin, this),
		std::bind(&ALasleyStageBoss::LasleyBossStageEndTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageBoss::LasleyBossStageEndExit, this));

	State.ChangeState("LasleyBossStateIn");
}

void ALasleyStageBoss::CreateAnimation()
{
	MapObject->SetSprite("Stele");
	MapObject->CreateAnimation("Stele_CloseDoor", "Stele", 0.125f, false, 0, 8);
	MapObject->CreateAnimation("Stele_IdleDoor", "Stele", 0.125f, true, 8, 15);
	MapObject->CreateAnimation("Stele_OpenDoor", "Stele", 0.125f, false, 16, 23);

	MapObject->ChangeAnimation("Stele_CloseDoor");
}


#pragma region LasleyBossStageIn
void ALasleyStageBoss::LasleyBossStageInBegin()
{
	if (true == MapObject->IsActive())
	{
		MapObject->SetActive(false);
	}
}

void ALasleyStageBoss::LasleyBossStageInTick(float _DeltaTime)
{
	// 플레이어가 일정 거리 앞으로 가면, 다음 상태로 전환.
	StageStartCollisionCheck(_DeltaTime);
}

void ALasleyStageBoss::LasleyBossStageInExit()
{
	BossStageStartCol->SetActive(false);
	BossStageStart = true;
}
#pragma endregion

#pragma region LasleyBossStageStart
void ALasleyStageBoss::LasleyBossStageStartBegin()
{
	if (false == MapObject->IsActive())
	{
		MapObject->SetActive(true);
	}
	MapObject->ChangeAnimation("Stele_CloseDoor");
}

void ALasleyStageBoss::LasleyBossStageStartTick(float _DeltaTime)
{
	// 카메라가 라슬리에 포커스를 둬야 함.

}

void ALasleyStageBoss::LasleyBossStageStartExit()
{
}
#pragma endregion

#pragma region LasleyBossStageIng
void ALasleyStageBoss::LasleyBossStageIngBegin()
{
	MapObject->ChangeAnimation("Stele_IdleDoor");
}

void ALasleyStageBoss::LasleyBossStageIngTick(float _DeltaTime)
{
	if (true == IsDown('T'))
	{
		State.ChangeState("LasleyBossStageEnd");
		return;
	}
}

void ALasleyStageBoss::LasleyBossStageIngExit()
{
}
#pragma endregion

#pragma region LasleyBossStageEnd
void ALasleyStageBoss::LasleyBossStageEndBegin()
{
	MapObject->ChangeAnimation("Stele_OpenDoor");
}

void ALasleyStageBoss::LasleyBossStageEndTick(float _DeltaTime)
{
}

void ALasleyStageBoss::LasleyBossStageEndExit()
{
}
#pragma endregion


void ALasleyStageBoss::StageStartCollisionCheck(float _DeltaTime)
{
	BossStageStartCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			State.ChangeState("LasleyBossStageStart");
			return;
		});

}