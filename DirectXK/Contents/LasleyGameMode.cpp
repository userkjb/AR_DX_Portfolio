#include "PreCompile.h"
#include "LasleyGameMode.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineSprite.h>

#include <EngineCore/EngineEditorGUI.h>
#include "LasleyStageGUI.h"

#include "Player.h"
#include "Lasley.h"
#include "BackGround.h"

// Map Image
#include "LasleyStageOne.h"


ALasleyGameMode::ALasleyGameMode()
{
}

ALasleyGameMode::~ALasleyGameMode()
{
}

void ALasleyGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\LasleyStage");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}

		Dir.Move("Boss_Lasley");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		UEngineSprite::CreateCutting("LasleyIdle.png", 5, 5);
		UEngineSprite::CreateCutting("LasleyDimensionCutter.png", 5, 5);
		UEngineSprite::CreateCutting("LasleyDoubleDimensionCutter.png", 5, 6);
		UEngineSprite::CreateCutting("LasleyDemonicBlade.png", 5, 4);
		UEngineSprite::CreateCutting("DimensionSlashBack.png", 9, 3);
		UEngineSprite::CreateCutting("DimensionSlashFront.png", 6, 2);
		UEngineSprite::CreateCutting("LasleyDemonicBladeFX.png", 8, 1);
		UEngineSprite::CreateCutting("LasleyDemonicBladeDisappearFX.png", 3, 3);
		UEngineSprite::CreateCutting("LasleyLargeDemonicBladeFX.png", 5, 1);
		UEngineSprite::CreateCutting("LasleyLargeDemonicBladeDisappearFX.png", 5, 2);
		UEngineSprite::CreateCutting("DevilChurchWarlock.png", 8, 3);
		UEngineSprite::CreateCutting("DevilChurchWarlockFX.png", 5, 5);
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\LasleyStage");
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
		Dir.Move("Image\\PlayerActor");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	// test ����
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\Item");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	// Camera
	{
		Camera = GetWorld()->GetMainCamera();
		//Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
		//Camera->SetActorLocation(FVector(ScreenScaleHalf.X, -ScreenScaleHalf.Y, -100.0f));
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		Camera->SetActorLocation(FVector(ScreenScaleHalf.X, ScreenScaleHalf.Y, -500.0f));
	}

	// GUI
	{
		UEngineEditorGUI::CreateEditorWindow<LasleyStageGUI>("Lasley Stage GUI");
	}
}

void ALasleyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	FVector PlayerPos = Player->GetPlayerPos();
		
	if (true == UEngineInput::IsDown(0x30)) // Ű���� 0
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
	if (!FreeCamera) // false
	{
		Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -100.0f });
	}


	// �÷��̾ ���� ���������� �Ѿ�� Map�� Collision�� �浹 ���� ��,
	// -> �÷��̾��� Ű �Է��� ���ƾ� �Ѵ�.
	// -> ȭ���� ��ο����� �Ѵ�.
	bool IsLeftCol = StageMap_One->IsLeftMapCol(); // ���� ��Ż�� �浹 ��.

	if (true == IsLeftCol)
	{
		int a = 0;

		GEngine->ChangeLevel("LasleyLevelBoss");
	}

	CameraMove();
#ifdef _DEBUG
	//FVector CameraPos = Camera->GetActorLocation();
	//std::string Msg1 = std::format("Level Player Pos : {}\n", PlayerPos.ToString());
	//std::string Msg2 = std::format("Level Camera Pos : {}\n", CameraPos.ToString());
	//UEngineDebugMsgWindow::PushMsg(Msg1);
	//UEngineDebugMsgWindow::PushMsg(Msg2);
#endif
}

void ALasleyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("StartStageCol.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	// Player
	{
		//float4 TexScale = UContentsConstValue::MapTexScale;
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation({ 1040.0f,  400.0f, 0.0f });
	}

	// Map
	{
		StageMap_One = GetWorld()->SpawnActor<ALasleyStageOne>("StageOneMap");
				
		float4 TexScale = UContentsConstValue::MapTexScale;
		float Size = UContentsConstValue::AutoSizeValue; // const
		StageMap_One->SetActorLocation({ TexScale.hX() * Size, TexScale.hY() * Size, 100.0f });
	}

	// Back Ground Image
	{
		//std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
		//float TileSize = UContentsConstValue::TileSize; // 64.0f 
		//float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		//BackGournd->SetActorScale3D(ImageScale);
		//BackGournd->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

}

void ALasleyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	StageMap_One->Destroy();

	int a = 0;
}

void ALasleyGameMode::CameraMove()
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
