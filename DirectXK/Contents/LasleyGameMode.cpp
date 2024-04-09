#include "PreCompile.h"
#include "LasleyGameMode.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineSprite.h>

#include "Lasley.h"
#include "LasleyStageMap.h"
#include "BackGround.h"

ALasleyGameMode::ALasleyGameMode()
{
}

ALasleyGameMode::~ALasleyGameMode()
{
}

void ALasleyGameMode::BeginPlay()
{
	Super::BeginPlay();

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

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
}

void ALasleyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ALasleyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALasleyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("BGLayer.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	{
		std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
		float TileSize = UContentsConstValue::TileSize; // 64.0f 
		float4 TexScale = UContentsConstValue::MapTexScale;
		float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		BackGournd->SetActorScale3D(ImageScale);
		BackGournd->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

	{
		std::shared_ptr<ALasley> Lasley = GetWorld()->SpawnActor<ALasley>("Lasley");
		//Lasley->SetActorScale3D();
		Lasley->SetActorLocation({ 0.0f, 0.0f, 200.0f });
		// Actor의 위치, 크기는 여기서 Set 해주는 것이 좋다.
		//float TileSize = UContentsConstValue::TileSize;
		//float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
		//Lasley->SetActorScale3D(ImageScale);
		//Lasley->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

	{
		std::shared_ptr<ALasleyStageMap> BackGround = GetWorld()->SpawnActor<ALasleyStageMap>("LasleyStageMap");
		//float TileSize = UContentsConstValue::TileSize;
		//float4 TexScale = UContentsConstValue::MapTexScale;
		//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
		//BackGround->SetActorScale3D(ImageScale);
		//BackGround->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}
}
