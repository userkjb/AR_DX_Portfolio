#include "PreCompile.h"
#include "DevilChurchWarlock.h"
#include <EngineCore/DefaultSceneComponent.h>

ADevilChurchWarlock::ADevilChurchWarlock()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);
}

ADevilChurchWarlock::~ADevilChurchWarlock()
{
}


void ADevilChurchWarlock::BeginPlay()
{
	Super::BeginPlay();

}

void ADevilChurchWarlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
