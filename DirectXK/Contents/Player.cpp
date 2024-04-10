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

	PlayerRenderer->SetAutoSize(5.0f, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
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
	PlayerRenderer->ChangeAnimation("Idle");
}

void APlayer::IdleTick(float _DeltaTime)
{
	if (true == IsDown('A') || true == IsDown('D'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsDown(VK_LBUTTON))
	{
		// 공격
	}

	if (true == IsDown(VK_RBUTTON))
	{
		// 대쉬
	}
}

void APlayer::IdleEnd()
{
	int a = 0;
}

void APlayer::RunBegin()
{
	PlayerRenderer->ChangeAnimation("Run");
}

void APlayer::RunTick(float _DeltaTime)
{
	if (true == IsFree('A') && true == IsFree('D'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress('A'))
	{
		FVector Dir = GetActorScale3D();
		
		AddActorLocation(float4::Left * RunSpeed * _DeltaTime);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(float4::Right * RunSpeed * _DeltaTime);
	}
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
