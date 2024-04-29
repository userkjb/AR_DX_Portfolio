#include "PreCompile.h"
#include "DevilChurchWarlock.h"
#include <EngineCore/DefaultSceneComponent.h>

ADevilChurchWarlock::ADevilChurchWarlock()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	WarlockRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	WarlockRenderer->SetupAttachment(Root);
	WarlockRenderer->SetOrder(ERenderOrder::Enemy);
}

ADevilChurchWarlock::~ADevilChurchWarlock()
{
}


void ADevilChurchWarlock::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimtaion();

	StateInit();

	WarlockRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ADevilChurchWarlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ADevilChurchWarlock::CreateAnimtaion()
{
	WarlockRenderer->CreateAnimation("WarlockIdle", "DevilChurchWarlock.png", 0.125f, false, 0, 16);
	WarlockRenderer->CreateAnimation("WarlockSkill", "DevilChurchWarlock.png", 0.125f, true, 17, 23);

	WarlockRenderer->ChangeAnimation("WarlockIdle");
}

void ADevilChurchWarlock::StateInit()
{
	State.CreateState("WarlockNone");
	State.CreateState("WarlockSummon");
	State.CreateState("WarlockAttack");
	State.CreateState("WarlockDie");

	State.SetFunction("WarlockSummon",
		std::bind(&ADevilChurchWarlock::SummonBegin, this),
		std::bind(&ADevilChurchWarlock::SummonTick, this, std::placeholders::_1),
		std::bind(&ADevilChurchWarlock::SummonExit, this));
	State.SetFunction("WarlockAttack",
		std::bind(&ADevilChurchWarlock::AttackBegin, this),
		std::bind(&ADevilChurchWarlock::AttackTick, this, std::placeholders::_1),
		std::bind(&ADevilChurchWarlock::AttackExit, this));
	State.SetFunction("WarlockDie",
		std::bind(&ADevilChurchWarlock::DieBegin, this),
		std::bind(&ADevilChurchWarlock::DieTick, this, std::placeholders::_1),
		std::bind(&ADevilChurchWarlock::DieExit, this));

	State.ChangeState("WarlockNone");
}


#pragma region Summon
void ADevilChurchWarlock::SummonBegin()
{
	WarlockRenderer->ChangeAnimation("WarlockIdle");
	WarlockRenderer->SetPosition(SummonPos);
}

void ADevilChurchWarlock::SummonTick(float _DeltaTime)
{
	if (true == WarlockRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("WarlockAttack");
		return;
	}
}

void ADevilChurchWarlock::SummonExit()
{
}
#pragma endregion


#pragma region Attack
void ADevilChurchWarlock::AttackBegin()
{
	WarlockRenderer->ChangeAnimation("WarlockSkill");
}

void ADevilChurchWarlock::AttackTick(float _DeltaTime)
{
	// 备眉 积己.

	// 妮府傈.
	int a = 0;
}

void ADevilChurchWarlock::AttackExit()
{
}
#pragma endregion

void ADevilChurchWarlock::DieBegin()
{
}

void ADevilChurchWarlock::DieTick(float _DeltaTime)
{
}

void ADevilChurchWarlock::DieExit()
{
}
