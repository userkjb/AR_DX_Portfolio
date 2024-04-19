#include "PreCompile.h"
#include "LasleyStageOne.h"
#include <EngineCore/DefaultSceneComponent.h>

#include <EngineCore/TileRenderer.h>

ALasleyStageOne::ALasleyStageOne()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
		
	//MapRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//MapRenderer->SetupAttachment(Root);
	//MapRenderer->SetActive(true);
	
	MapColRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MapColRenderer->SetupAttachment(Root);
	MapColRenderer->SetActive(false);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");

	SetRoot(Root);

	InputOn(); // test
}

ALasleyStageOne::~ALasleyStageOne()
{
}

void ALasleyStageOne::BeginPlay()
{
	Super::BeginPlay();

	float Size = UContentsConstValue::AutoSizeValue; // const
	//MapRenderer->SetSprite("StartStage.png");
	//MapRenderer->SetAutoSize(Size, true); // 
	//MapRenderer->SetOrder(ERenderOrder::Map);

	MapColRenderer->SetSprite("StartStageCol.png");
	MapColRenderer->SetAutoSize(Size, true); // 
	MapColRenderer->SetOrder(ERenderOrder::MapCol);

	CreateMapImage();
}

void ALasleyStageOne::Tick(float _DeltaTime)
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

	
	/////
	float Speed = 100.0f;

	if (true == IsPress('U'))
	{
		AddActorLocation(FVector::Up * 100.0f * _DeltaTime);
	}
	if (true == IsPress('J'))
	{
		AddActorLocation(FVector::Down * 100.0f * _DeltaTime);
	}
	if (true == IsPress('H'))
	{
		AddActorLocation(FVector::Left * 100.0f * _DeltaTime);
	}
	if (true == IsPress('K'))
	{
		AddActorLocation(FVector::Right * 100.0f * _DeltaTime);
	}
}

void ALasleyStageOne::CreateMapImage()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	Dir.Move("TileMapData");

	std::vector<std::vector<int>> TileData;
	std::string FileName = "";
	UEngineSerializer Ser;

	UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
	File.Open(EIOOpenMode::Read, EIODataType::Binary);
	File.Load(Ser);

	Ser >> FileName;
	Ser >> TileData;

	File.Close();

	size_t ImageXSize = TileData[0].size();
	size_t ImageYSize = TileData.size();

	TileRenderer->CreateTileMap("Map4X(64).png", { 64, 64 }, static_cast<int>(TileData[0].size()), static_cast<int>(TileData.size()), 0);
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
