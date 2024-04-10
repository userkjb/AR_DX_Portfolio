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

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
}

void AGameStartGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AGameStartGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AGameStartGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}
