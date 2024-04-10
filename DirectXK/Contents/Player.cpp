#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>

APlayer::APlayer()
{
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayer::CreateAnimation()
{
}

void APlayer::StateInit()
{
}
