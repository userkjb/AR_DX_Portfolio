#include "PreCompile.h"
#include "LasleyStageBoss.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TileRenderer.h>

#include "Player.h"

ALasleyStageBoss::ALasleyStageBoss()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");

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

	// 보스전 시작을 위한 Collision
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
	MapObjectLeftDoor->SetPosition({ (-928.0f + 30.0f), (-608.0f + Up) });
	MapObjectLeftDoor->SetRotationDeg({ 1.0f, 1.0f, 90.0f });
	MapObjectRightDoor->SetPosition({ (928.0f - 30.0f), (-608.0f + Up) });
	MapObjectRightDoor->SetRotationDeg({ 1.0f, 1.0f, -90.0f });

	FVector MapObjectScale = MapObjectLeftDoor->GetWorldScale();
	
	MapObjectLeftDoorCol->SetScale({ MapObjectScale.Y, MapObjectScale.X});
	MapObjectLeftDoorCol->SetPosition({ (-928.0f + 30.0f), (-608.0f + Up) });

	MapObjectRightDoorCol->SetScale({ MapObjectScale.Y, MapObjectScale.X });
	MapObjectRightDoorCol->SetPosition({ (928.0f - 30.0f), (-608.0f + Up) });
}

void ALasleyStageBoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

#ifdef _DEBUG
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
#endif
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
	MapObjectLeftDoor->SetSprite("Stele");
	MapObjectLeftDoor->CreateAnimation("Stele_CloseLeftDoor", "Stele", 0.125f, false, 0, 8);
	MapObjectLeftDoor->CreateAnimation("Stele_IdleLeftDoor", "Stele", 0.125f, true, 8, 15);
	MapObjectLeftDoor->CreateAnimation("Stele_OpenLeftDoor", "Stele", 0.125f, false, 16, 23);

	MapObjectLeftDoor->ChangeAnimation("Stele_CloseLeftDoor");

	MapObjectRightDoor->SetSprite("Stele");
	MapObjectRightDoor->CreateAnimation("Stele_CloseRightDoor", "Stele", 0.125f, false, 0, 8);
	MapObjectRightDoor->CreateAnimation("Stele_IdleRightDoor", "Stele", 0.125f, true, 8, 15);
	MapObjectRightDoor->CreateAnimation("Stele_OpenRightDoor", "Stele", 0.125f, false, 16, 23);

	MapObjectRightDoor->ChangeAnimation("Stele_CloseRightDoor");
}


#pragma region LasleyBossStageIn
void ALasleyStageBoss::LasleyBossStageInBegin()
{
	if (true == MapObjectLeftDoor->IsActive() && true == MapObjectRightDoor->IsActive())
	{
		MapObjectLeftDoor->SetActive(false);
		MapObjectRightDoor->SetActive(false);
		MapObjectLeftDoorCol->SetActive(false);
		MapObjectRightDoorCol->SetActive(false);
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
	if (false == MapObjectLeftDoor->IsActive() && false == MapObjectRightDoor->IsActive())
	{
		MapObjectLeftDoor->SetActive(true);
		MapObjectRightDoor->SetActive(true);
		MapObjectLeftDoorCol->SetActive(true);
		MapObjectRightDoorCol->SetActive(true);
	}
	MapObjectLeftDoor->ChangeAnimation("Stele_CloseLeftDoor");
	MapObjectRightDoor->ChangeAnimation("Stele_CloseRightDoor");
}

void ALasleyStageBoss::LasleyBossStageStartTick(float _DeltaTime)
{
	// 카메라가 라슬리에 포커스를 둬야 함.
	// test
	if (true == IsDown('T'))
	{
		State.ChangeState("LasleyBossStageIng");
		return;
	}
}

void ALasleyStageBoss::LasleyBossStageStartExit()
{
}
#pragma endregion

#pragma region LasleyBossStageIng
void ALasleyStageBoss::LasleyBossStageIngBegin()
{
	MapObjectLeftDoor->ChangeAnimation("Stele_IdleLeftDoor");
	MapObjectRightDoor->ChangeAnimation("Stele_IdleRightDoor");
}

void ALasleyStageBoss::LasleyBossStageIngTick(float _DeltaTime)
{
	if (true == IsDown('T'))
	{
		State.ChangeState("LasleyBossStageEnd");
		return;
	}
	PlayerStageOutCollisionCheck(_DeltaTime);
}

void ALasleyStageBoss::LasleyBossStageIngExit()
{
}
#pragma endregion

#pragma region LasleyBossStageEnd
void ALasleyStageBoss::LasleyBossStageEndBegin()
{
	MapObjectLeftDoor->ChangeAnimation("Stele_OpenLeftDoor");
	MapObjectRightDoor->ChangeAnimation("Stele_OpenRightDoor");
}

void ALasleyStageBoss::LasleyBossStageEndTick(float _DeltaTime)
{
	if (MapObjectLeftDoor->IsCurAnimationEnd())
	{
		MapObjectLeftDoor->SetActive(false);
		MapObjectLeftDoorCol->SetActive(false);
	}
	if (MapObjectRightDoor->IsCurAnimationEnd())
	{
		MapObjectRightDoor->SetActive(false);
		MapObjectRightDoorCol->SetActive(false);
	}
}

void ALasleyStageBoss::LasleyBossStageEndExit()
{
}
#pragma endregion




// Collision
void ALasleyStageBoss::StageStartCollisionCheck(float _DeltaTime)
{
	BossStageStartCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			State.ChangeState("LasleyBossStageStart");
			return;
		});
}

void ALasleyStageBoss::PlayerStageOutCollisionCheck(float _DeltaTime)
{
	MapObjectLeftDoorCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			APlayer* Player = dynamic_cast<APlayer*>(_Collison->GetActor());
			if (true == IsPress('A') || true == IsDown('A') || true == IsUp('A'))
			{
				SendMapInDoor(Player, 0.0f);
			}
			else
			{
				SendMapInDoor(Player, 1.0f);
			}
		});

	MapObjectRightDoorCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			APlayer* Player = dynamic_cast<APlayer*>(_Collison->GetActor());
			if (true == IsPress('D') || true == IsDown('D') || true == IsUp('D'))
			{
				SendMapInDoor(Player, 0.0f);
			}
			else
			{
				SendMapInDoor(Player, 1.0f);
			}
		});
}

void ALasleyStageBoss::SendMapInDoor(APlayer* _Player, float _SendFloatValue)
{
	_Player->RecvMapInDoor(_SendFloatValue);
}
