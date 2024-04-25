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
}

void ALasleyStageBoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

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
