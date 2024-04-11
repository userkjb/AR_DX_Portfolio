#include "PreCompile.h"
#include "LasleyStateStartMode.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineSprite.h>


ALasleyStateStartMode::ALasleyStateStartMode()
{
}

ALasleyStateStartMode::~ALasleyStateStartMode()
{
}

void ALasleyStateStartMode::BeginPlay()
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

	Dir.Move("Map_Lasley");
	std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
	for (size_t i = 0; i < Directorys.size(); i++)
	{
		std::string Name = Directorys[i].GetFolderName();
		UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
	}

	Dir.Move("..\\Stage_Monster");
	for (size_t i = 0; i < Directorys.size(); i++)
	{
		std::string Name = Directorys[i].GetFolderName();
		UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
	}

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
}

void ALasleyStateStartMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ALasleyStateStartMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ALasleyStateStartMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UContentsConstValue::MapTex = UEngineTexture::FindRes("BGLayer.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	//{
	//	std::shared_ptr<ABackGround> BackGournd = GetWorld()->SpawnActor<ABackGround>("BackGround");
	//	float TileSize = UContentsConstValue::TileSize; // 64.0f 
	//	float4 TexScale = UContentsConstValue::MapTexScale;
	//	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

	//	BackGournd->SetActorScale3D(ImageScale);
	//	BackGournd->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	//}
}
