#include "PreCompile.h"
#include "LasleyGameMode.h"
#include <EngineCore/Camera.h>

#include "Lasley.h"

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
		// CuttingTest.png texture�ε� ������ �ε尡 �ư�
		// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
		UEngineTexture::Load(File.GetFullPath());
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

	GetWorld()->SpawnActor<ALasley>("Lasley");
}
