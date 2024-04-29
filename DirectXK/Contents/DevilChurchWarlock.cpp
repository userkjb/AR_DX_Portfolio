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
	WarlockRenderer->CreateAnimation("WarlockIdle", "DevilChurchWarlock.png", 0.125f, false, 0, 14);
	WarlockRenderer->CreateAnimation("WarlockSkill", "DevilChurchWarlock.png", 0.125f, true, 15, 23);

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



void ADevilChurchWarlock::SummonBegin()
{
	int a = 0;
}

void ADevilChurchWarlock::SummonTick(float _DeltaTime)
{
	int a = 0;
}

void ADevilChurchWarlock::SummonExit()
{
}

void ADevilChurchWarlock::AttackBegin()
{
}

void ADevilChurchWarlock::AttackTick(float _DeltaTime)
{
}

void ADevilChurchWarlock::AttackExit()
{
}

void ADevilChurchWarlock::DieBegin()
{
}

void ADevilChurchWarlock::DieTick(float _DeltaTime)
{
}

void ADevilChurchWarlock::DieExit()
{
}
