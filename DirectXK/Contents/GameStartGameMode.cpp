#include "PreCompile.h"
#include "GameStartGameMode.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineSprite.h>

#include "Player.h"

AGameStartGameMode::AGameStartGameMode()
{
}

AGameStartGameMode::~AGameStartGameMode()
{
}

void AGameStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image\\PlayerActor");
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

	//StateInit();
}

void AGameStartGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//State.Update(_DeltaTime);
}

void AGameStartGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AGameStartGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	Player = GetWorld()->SpawnActor<APlayer>("Player");
}
