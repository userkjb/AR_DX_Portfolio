#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/Camera.h>

#include "GameLogo.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image\\GameTitle");
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

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->SpawnActor<AGameLogo>("GameLogo");
}
