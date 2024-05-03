#include "PreCompile.h"
#include "LasleyStageTwoGM.h"

#include "LasleyStageTwoMap.h"
#include "Player.h"
#include "Wyvern.h"
#include "BackGround.h"
#include "BasicSkeleton.h"

ALasleyStageTwoGM::ALasleyStageTwoGM()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image\\LasleyStage\\Stage_Monster");
	std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
	for (size_t i = 0; i < Directorys.size(); i++)
	{
		std::string Name = Directorys[i].GetFolderName();
		UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
	}

	InputOn(); // test
}

ALasleyStageTwoGM::~ALasleyStageTwoGM()
{
}

void ALasleyStageTwoGM::BeginPlay()
{
	Super::BeginPlay();

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\GlobalMonster\\Skeleton");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
		UEngineSprite::CreateCutting("sk_Attack.png", 6, 2);
		UEngineSprite::CreateCutting("sk_Idle.png", 5, 1);
		UEngineSprite::CreateCutting("sk_Run.png", 4, 2);
	}

	{
		Camera = GetWorld()->GetMainCamera();
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}
}

void ALasleyStageTwoGM::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	LevelState.Update(_DeltaTime);

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
}

void ALasleyStageTwoGM::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Stage_2_Col.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Player
	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation({ 1550.0f,  190.0f, 0.0f });
	}

	{
		MapActor = GetWorld()->SpawnActor<ALasleyStageTwoMap>("StageTwoMap", ERenderOrder::Map);
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		MapActor->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}

	// BG
	{
		std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		BackGournd->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, -200.0f });
	}


	InitState();
}

void ALasleyStageTwoGM::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Player->LevelIsDestroy();
	Player->Destroy();
	MapActor->Destroy();
}

void ALasleyStageTwoGM::InitState()
{
	LevelState.CreateState("Idle");
	LevelState.CreateState("Battle");

	LevelState.SetFunction("Idle",
		std::bind(&ALasleyStageTwoGM::IdleBegin, this),
		std::bind(&ALasleyStageTwoGM::IdleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoGM::IdleExit, this));

	LevelState.SetFunction("Battle",
		std::bind(&ALasleyStageTwoGM::BattleBegin, this),
		std::bind(&ALasleyStageTwoGM::BattleTick, this, std::placeholders::_1),
		std::bind(&ALasleyStageTwoGM::BattleExit, this));


	LevelState.ChangeState("Idle");
}


void ALasleyStageTwoGM::IdleBegin()
{
}

void ALasleyStageTwoGM::IdleTick(float _DeltaTime)
{
	CameraMove(_DeltaTime);

	if (true == MapActor->IsRightMapCol())
	{
		GEngine->ChangeLevel("LasleyLevel");
	}

	if (true == MapActor->IsLeftMapCol())
	{
		GEngine->ChangeLevel("LasleyLevelBoss");
	}

	if (true == IsOne)
	{
		MapActor->SetIsOne(IsOne);
		LevelState.ChangeState("Battle");
		return;
	}
}

void ALasleyStageTwoGM::IdleExit()
{
	IsOne = false;
}



void ALasleyStageTwoGM::BattleBegin()
{
}

void ALasleyStageTwoGM::BattleTick(float _DeltaTime)
{
	CameraMove(_DeltaTime);

	if (true == MapActor->IsBattleEnd())
	{
		LevelState.ChangeState("Idle");
		return;
	}

	if (true == IsDown('L'))
	{
		//float4 SetPosValue = UContentsConstValue::MapTexScale.Half2D() * 4.0f;
		//std::shared_ptr<AWyvern> BlackSphere = GetWorld()->SpawnActor<AWyvern>("Wyvern");
		//BlackSphere->SetWyvernWorldPos(FVector(SetPosValue.X, SetPosValue.Y));
		//BlackSphere->SetWyvernLocalPos(FVector(-300.0f, 0.0f));
		//BlackSphere->SettingPosition();
		//BlackSphere->CreateWyvern();

		std::shared_ptr<ABasicSkeleton> BasicSkeleton = GetWorld()->SpawnActor<ABasicSkeleton>("BasicSkeleton");
		BasicSkeleton->SetBasicSkeletonPos(FVector(800.0f, 192.0f));
		BasicSkeleton->CreateBasicSkeleton();
	}
}

void ALasleyStageTwoGM::BattleExit()
{
}





void ALasleyStageTwoGM::CameraMove(float _DeltaTime)
{
	if (!FreeCamera) // false
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