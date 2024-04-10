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
	PlayerRenderer->CreateAnimation("Run", "Run", 0.125f);
	PlayerRenderer->CreateAnimation("Jump", "Jump", 0.125f);
	PlayerRenderer->CreateAnimation("Die", "Die", 0.125f);

	PlayerRenderer->ChangeAnimation("Idle");
}

void APlayer::StateInit()
{
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Die");

	State.SetFunction("Idle",
		std::bind(&APlayer::IdleBegin, this),
		std::bind(&APlayer::IdleTick, this, std::placeholders::_1),
		std::bind(&APlayer::IdleEnd, this));
	State.SetFunction("Run",
		std::bind(&APlayer::RunBegin, this),
		std::bind(&APlayer::RunTick, this, std::placeholders::_1),
		std::bind(&APlayer::RunEnd, this));
	State.SetFunction("Jump",
		std::bind(&APlayer::JumpBegin, this),
		std::bind(&APlayer::JumpTick, this, std::placeholders::_1),
		std::bind(&APlayer::JumpEnd, this));
	State.SetFunction("Die",
		std::bind(&APlayer::DieBegin, this),
		std::bind(&APlayer::DieTick, this, std::placeholders::_1),
		std::bind(&APlayer::DieEnd, this));

	State.ChangeState("Idle");
}

void APlayer::IdleBegin()
{
}

void APlayer::IdleTick(float _DeltaTime)
{
}

void APlayer::IdleEnd()
{
}

void APlayer::RunBegin()
{
}

void APlayer::RunTick(float _DeltaTime)
{
}

void APlayer::RunEnd()
{
}

void APlayer::JumpBegin()
{
}

void APlayer::JumpTick(float _DeltaTime)
{
}

void APlayer::JumpEnd()
{
}

void APlayer::DieBegin()
{
}

void APlayer::DieTick(float _DeltaTime)
{
}

void APlayer::DieEnd()
{
}
