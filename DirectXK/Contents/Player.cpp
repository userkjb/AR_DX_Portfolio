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

	CreateAnimation();
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayer::CreateAnimation()
{
	PlayerRenderer->CreateAnimation("Idle", "Idle", 0.125f);
	PlayerRenderer->CreateAnimation("Jump", "Jump", 0.125f);
	PlayerRenderer->CreateAnimation("Run", "Run", 0.125f);
	PlayerRenderer->CreateAnimation("Die", "Die", 0.125f);

	PlayerRenderer->ChangeAnimation("Idle");
}

void APlayer::StateInit()
{
	State.CreateState("Idle");
	State.CreateState("Jump");
	State.CreateState("Run");
	State.CreateState("Die");


	State.ChangeState("Idle");
}
