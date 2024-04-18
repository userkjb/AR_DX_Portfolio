#include "PreCompile.h"
#include "TestGameMode.h"

#include "TestActor.h"
#include <EngineCore/Camera.h>
#include <EngineCore/TileRenderer.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/Image.h>

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

// Save Data Ex
class MonsterData
{
public:
	int Att;
	int Hp;
};

class MySaveFile : public UEngineSerializeObject
{
public:
	ULevel* Test;
	std::string PlayerName;
	std::vector<int> Data;
	std::vector<std::vector<int>> TileData;

	void Serialize(UEngineSerializer& _Ser) override
	{
		// 저장순서랑 로드순서를 
		_Ser << PlayerName;
		_Ser << Data;
		_Ser << TileData;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		_Ser >> PlayerName;
		_Ser >> Data;
		_Ser >> TileData;
	}
};



// End Save Data Ex


void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Save Data Ex
	/*{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Save");

		{
			std::vector<std::vector<int>> TileData = { {4,3, 2}, {5,6, 7}, {7,6, 7} };

			UEngineSerializer Ser;
			Ser << TileData;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Write, EIODataType::Binary);
			File.Save(Ser);
		}

		{
			MySaveFile SaveData;

			std::vector<std::vector<int>> TileData;
			UEngineSerializer Ser;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Read, EIODataType::Binary);
			File.Load(Ser);

			Ser >> TileData;
		}
	}*/
	// End Save Data Ex

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\Tile\\MapTile");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture로도 한장이 로드가 됐고
			// 스프라이트로도 1장짜리로 로드가 된 상황이야.
			UEngineSprite::Load(File.GetFullPath());
		}

		UEngineSprite::CreateCutting("Map4X(64).png", 12, 4);
	}


	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	// UI 예제
	{
		// UI를 만들겠다.
		UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBar");

		// 언리얼 따라한것
		// 언리얼 안나옵니다.
		Image->AddToViewPort();
		Image->SetSprite("HPBar.png");
		Image->SetAutoSize(0.5f, true);
		Image->SetPosition({ -400, 300 });

		/*
		Image->SetUnHover([=]()
			{
				Image->SetSprite("HPBar.png");
				// UEngineDebugMsgWindow::PushMsg("Hover!!!");
			});

		Image->SetHover([=]()
			{
				Image->SetSprite("Back.png");
				Image->SetAutoSize(1.0f, false);
				// UEngineDebugMsgWindow::PushMsg("Hover!!!");
			});

		Image->SetDown([=]()
			{
				UEngineDebugMsgWindow::PushMsg("Down!!!");
			});
		*/

		// Image->SetScale({200, 200});

		// 화면에 떠야 한다.
		// Image->SetSprite("HPBar");
		// Image->SetScale();
	}
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
