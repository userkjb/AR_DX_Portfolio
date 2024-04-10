#include "PreCompile.h"
#include "GameStartGameMode.h"

AGameStartGameMode::AGameStartGameMode()
{
}

AGameStartGameMode::~AGameStartGameMode()
{
}

void AGameStartGameMode::BeginPlay()
{
	Super::BeginPlay();
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
