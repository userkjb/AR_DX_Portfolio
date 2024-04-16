#include "PreCompile.h"
#include "TestGameMode.h"
#include "TestActor.h"
#include <EngineCore/Camera.h>

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<ATestActor>("Player");

	// Å¸ÀÏ¸Ê Base »ý¼º

}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}