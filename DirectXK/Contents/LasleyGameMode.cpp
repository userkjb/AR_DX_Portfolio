#include "PreCompile.h"
#include "LasleyGameMode.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineSprite.h>

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
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\PlayerActor");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();

	Camera = GetWorld()->GetMainCamera();
	//Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	Camera->SetActorLocation(FVector(ScreenScaleHalf.X, -ScreenScaleHalf.Y, -100.0f));
}

void ALasleyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


#ifdef _DEBUG
	//FVector PlayerPos = Player->GetPlayerPos();
	FVector CameraPos = Camera->GetActorLocation();
	//std::string Msg1 = std::format("Level Player Pos : {}\n", PlayerPos.ToString());
	//std::string Msg2 = std::format("Level Camera Pos : {}\n", CameraPos.ToString());
	//UEngineDebugMsgWindow::PushMsg(Msg1);
	//UEngineDebugMsgWindow::PushMsg(Msg2);
#endif
	
	//Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -100.0f });
}

void ALasleyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("StartStageCol.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
	}

	{
		std::shared_ptr<ALasleyStageOne> StageMap_One = GetWorld()->SpawnActor<ALasleyStageOne>("StageOneMap");

		float TileSize = UContentsConstValue::TileSize;
		float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
		
		//StageMap_One->SetActorScale3D();
		StageMap_One->SetActorLocation({ TexScale.hX(), -TexScale.hY(), 100.0f });
	}

	{
		//std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
		//float TileSize = UContentsConstValue::TileSize; // 64.0f 
		//float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		//BackGournd->SetActorScale3D(ImageScale);
		//BackGournd->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

	{
		//std::shared_ptr<ALasley> Lasley = GetWorld()->SpawnActor<ALasley>("Lasley");
		//Lasley->SetActorScale3D();
		//Lasley->SetActorLocation({ 0.0f, 0.0f, 200.0f });
		// Actor�� ��ġ, ũ��� ���⼭ Set ���ִ� ���� ����.
		//float TileSize = UContentsConstValue::TileSize;
		//float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
		//Lasley->SetActorScale3D(ImageScale);
		//Lasley->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

}

void ALasleyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}