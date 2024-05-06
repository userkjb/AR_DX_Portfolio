#include "PreCompile.h"
#include "GameStartText.h"
#include "TitleWidget.h"
#include <EngineCore/DefaultSceneComponent.h>

AGameStartText::AGameStartText()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
}

AGameStartText::~AGameStartText()
{
}

void AGameStartText::BeginPlay()
{
	Super::BeginPlay();
	Widget = CreateWidget<UTitleWidget>(GetWorld(), "GameStartUI");
}

void AGameStartText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
