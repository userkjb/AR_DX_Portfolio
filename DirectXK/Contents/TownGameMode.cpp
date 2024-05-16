#include "PreCompile.h"
#include "TownGameMode.h"
#include "TownMap.h"
#include "Player.h"

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

	StateInit();
}

void ATownGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Town_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Map
	{
		TownMap = GetWorld()->SpawnActor<ATownMap>("TownMap");
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		TownMap->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
		TownMap->SetIdleTown();
	}

	{
		Player = GetWorld()->SpawnActor<APlayer>("Player", EObjectOrder::Player);
		Player->SetActorLocation({ 1040.0f,  400.0f, 0.0f });
		Player->SetPlayerStateIdle();
	}

	// Camera
	{
		Camera = GetWorld()->GetMainCamera();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}

	Sound.On();
}

void ATownGameMode::StateInit()
{
	LevelState.CreateState("Idle");
	LevelState.CreateState("InDungeon");

	LevelState.SetFunction("Idle",
		std::bind(&ATownGameMode::IdleBegin, this),
		std::bind(&ATownGameMode::IdleTick, this, std::placeholders::_1),
		std::bind(&ATownGameMode::IdleExit, this));
	LevelState.SetFunction("InDungeon",
		std::bind(&ATownGameMode::InDungeonBegin, this),
		std::bind(&ATownGameMode::InDungeonTick, this, std::placeholders::_1),
		std::bind(&ATownGameMode::InDungeonExit, this));

	LevelState.ChangeState("Idle");
}



void ATownGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CameraMove(_DeltaTime);

	LevelState.Update(_DeltaTime);

#ifdef _DEBUG
	if (true == UEngineInput::IsDown(0x30)) // Å°º¸µå 0
	{
		if (FreeCamera)
		{
			FreeCamera = false;
		}
		else
		{
			FreeCamera = true;
		}
	}
#endif
}


void ATownGameMode::IdleBegin()
{
}

void ATownGameMode::IdleTick(float _DeltaTime)
{
	std::string TownState = TownMap->GetTownState();

	if (TownState == "Up")
	{
		Player->SetPlayerStateIdleLock();
	}

	if (TownState == "Down")
	{
		LevelState.ChangeState("InDungeon");
		return;
	}
}

void ATownGameMode::IdleExit()
{
	Player->LevelIsDestroy();
	Player->Destroy();
}



void ATownGameMode::InDungeonBegin()
{
}

void ATownGameMode::InDungeonTick(float _DeltaTime)
{
	std::string TownState = TownMap->GetTownState();
	if (TownState == "Down")
	{
		if (true == TownMap->GoNextLevel())
		{
			GEngine->ChangeLevel("LasleyLevel");
			return;
		}
	}
}

void ATownGameMode::InDungeonExit()
{
}




void ATownGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	Sound.Off();
}

void ATownGameMode::CameraMove(float _DeltaTime)
{
	if (!FreeCamera)
	{
		float4 MapSize = UContentsConstValue::MapTexScale;
		float4 GameMapSize = MapSize * UContentsConstValue::AutoSizeValue;
		//float4 ScreenSize = GEngine->EngineWindow.GetWindowScale();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		FVector PlayerPos = Player->GetPlayerPos();

		FVector CameraPos = Camera->GetActorLocation();

		CameraPos.X = PlayerPos.X;
		CameraPos.Y = PlayerPos.Y;

		if (CameraPos.X <= ScreenScaleHalf.X)
		{
			CameraPos.X = ScreenScaleHalf.X;
		}
		else if (CameraPos.X >= (GameMapSize.X - ScreenScaleHalf.X))
		{
			CameraPos.X = (GameMapSize.X - ScreenScaleHalf.X);
		}


		if (CameraPos.Y <= ScreenScaleHalf.Y)
		{
			CameraPos.Y = ScreenScaleHalf.Y;
		}
		else if (CameraPos.Y >= (GameMapSize.Y - ScreenScaleHalf.Y))
		{
			CameraPos.Y = (GameMapSize.Y - ScreenScaleHalf.Y);
		}

		Camera->SetActorLocation({ CameraPos.X, CameraPos.Y, -500.0f });
	}
}
