#include "PreCompile.h"
#include "TownGameMode.h"
#include "TownMap.h"

ATownGameMode::ATownGameMode()
{
}

ATownGameMode::~ATownGameMode()
{
}

void ATownGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\TownStage");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\TownStage\\Town");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Sound\\Town");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}

		Sound = UEngineSound::SoundPlay("Town.mp3");
		Sound.Loop(30);
		Sound.Off();
	}
}

void ATownGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATownGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Town_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Map
	{
		std::shared_ptr<ATownMap> TownMap = GetWorld()->SpawnActor<ATownMap>("TownMap");
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		TownMap->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}

	// Camera
	{
		Camera = GetWorld()->GetMainCamera();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}

	Sound.On();
}

void ATownGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
