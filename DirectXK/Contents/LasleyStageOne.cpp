#include "PreCompile.h"
#include "LasleyStageOne.h"
#include <EngineCore/DefaultSceneComponent.h>

#include <EngineCore/TileRenderer.h>

ALasleyStageOne::ALasleyStageOne()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");

	StageDoor = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	StageDoor->SetupAttachment(Root);

	LeftMapCol = CreateDefaultSubObject<UCollision>("StartMapCollision");
	LeftMapCol->SetupAttachment(Root);
	LeftMapCol->SetScale(FVector{ 64.0, 280.0, 1.0f });
	LeftMapCol->SetCollisionGroup(ECollisionOrder::NextMap);
	LeftMapCol->SetCollisionType(ECollisionType::RotRect);
	LeftMapCol->SetPosition(FVector{ -608.0f, -250.0f, 0.0f });

	SetRoot(Root);
}

ALasleyStageOne::~ALasleyStageOne()
{
}

void ALasleyStageOne::BeginPlay()
{
	Super::BeginPlay();

	float CSize = UContentsConstValue::AutoSizeValue; // const

	MapColRenderer->SetSprite("StartStageCol.png");
	MapColRenderer->SetAutoSize(CSize, true); // const Size
	MapColRenderer->SetOrder(ERenderOrder::MapCol);

	StageDoor->SetAutoSize(CSize, true);
	StageDoor->SetOrder(ERenderOrder::StageDoor);
	StageDoor->SetPosition({ 380.0f, 18.0f, 0.0f });

	CreateAnimation();

	CreateMapImage();

#ifdef _DEBUG
	InputOn(); // test
#endif
}

void ALasleyStageOne::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CollisionCheck(_DeltaTime);

#ifdef _DEBUG
	if (true == IsDown('O'))
	{
		if (false == MapColRenderer->IsActive())
		{
			//MapRenderer->SetActive(false);
			MapColRenderer->SetActive(true);
		}
		else
		{
			//MapRenderer->SetActive(true);
			MapColRenderer->SetActive(false);
		}
	}
#endif
}

void ALasleyStageOne::CreateMapImage()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	Dir.Move("TileMapData");

	std::vector<std::vector<int>> TileData;
	std::string FileName = "";
	UEngineSerializer Ser;

	UEngineFile File = Dir.GetPathFromFile("DarkStageStart.Data");
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

void ALasleyStageOne::CreateAnimation()
{
	StageDoor->CreateAnimation("StartDoor", "Stage_Start_Door", 0.125f, false);

	StageDoor->ChangeAnimation("StartDoor");
}

void ALasleyStageOne::CollisionCheck(float _DeltaTime)
{
	LeftMapCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			//FVector PlayerLocation = _Collision->GetActor()->GetActorLocation();
			
			b_LeftMapCol = true;
		}
	);
}
