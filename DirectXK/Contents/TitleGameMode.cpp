#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/Camera.h>
#include <EngineBase/EngineRandom.h>

#include "GameLogo.h"
#include "GameStartText.h"
#include "GameTitleBG.h"
#include "Bird.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\TitleLevel");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture로도 한장이 로드가 됐고
			// 스프라이트로도 1장짜리로 로드가 된 상황이야.
			UEngineSprite::Load(File.GetFullPath());
		}

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
		Dir.Move("Sound\\Title");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
		
		Sound = UEngineSound::SoundPlay("title.mp3");
		Sound.Off();
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Sound\\Player");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
	}

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation(FVector(0.0f, 0.0f, -500.0f));
	}

#ifdef _DEBUG
	InputOn();
#endif
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->SpawnActor<AGameTitleBG>("GameTitleBG", EObjectOrder::Map_BackGround);
	GetWorld()->SpawnActor<AGameStartText>("GameStartText", EObjectOrder::Text);
	GetWorld()->SpawnActor<AGameLogo>("GameLogo", EObjectOrder::Game_Title);

	Sound.On();
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	CreateBird(_DeltaTime);
}

void ATitleGameMode::CreateBird(float _DeltaTime)
{
	BirdTime += _DeltaTime;

	int CreateTime = static_cast<int>(BirdTime);
	if (0 == CreateTime % 2 && 1.0f <= BirdTime)
	{
		float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();
		ScreenScale.X *= 2.0f;
		float PositionX = UEngineRandom::MainRandom.RandomFloat(-ScreenScale.X, 0.0f);
		std::shared_ptr<ABird> Bird = GetWorld()->SpawnActor<ABird>("Bird", EObjectOrder::Map_Object);
		Bird->SetMoveDir(FVector(1.0f, 0.25f, 0.0f, 0.0f));
		Bird->SetCreateActorPos(FVector(PositionX, -ScreenScale.hY()));
		Bird->SetMoveSpeed(500.0f);
		Bird->BirdCreate();

		BirdTime = 0.0f;
	}
}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	Sound.Off();
}


