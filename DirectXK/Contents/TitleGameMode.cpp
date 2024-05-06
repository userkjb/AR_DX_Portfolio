#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/Camera.h>

#include "GameLogo.h"
#include "GameStartText.h"
#include "GameTitleBG.h"

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

	// ��ѱ� ������ �ؾ� ��.

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	}
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
	GetWorld()->SpawnActor<AGameStartText>("GameStartText");
	GetWorld()->SpawnActor<AGameTitleBG>("GameTitleBG");
}
