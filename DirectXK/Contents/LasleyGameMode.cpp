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
			// CuttingTest.png texture로도 한장이 로드가 됐고
			// 스프라이트로도 1장짜리로 로드가 된 상황이야.
			UEngineSprite::Load(File.GetFullPath());
		}

		Dir.Move("Boss_Lasley");
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

	// test 무기
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
		
	if (true == UEngineInput::IsDown(0x30)) // 키보드 0
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


	// 플레이어가 다음 스테이지로 넘어가는 Map의 Collision에 충돌 했을 때,
	// -> 플레이어의 키 입력을 막아야 한다.
	// -> 화면이 어두워져야 한다.
	bool IsLeftCol = StageMap_One->IsLeftMapCol(); // 왼쪽 포탈에 충돌 함.

	if (true == IsLeftCol)
	{
		int a = 0;

		GEngine->ChangeLevel("LasleyLevelBoss");
	}

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