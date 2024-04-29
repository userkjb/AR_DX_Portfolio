#include "PreCompile.h"
#include "DevilChurchWarlock.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "WarlockBlackSphere.h"

ADevilChurchWarlock::ADevilChurchWarlock()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	WarlockRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	WarlockRenderer->SetupAttachment(Root);
	WarlockRenderer->SetOrder(ERenderOrder::Enemy);

	WarlockCollision = CreateDefaultSubObject<UCollision>("Collision");
	WarlockCollision->SetupAttachment(Root);
	WarlockCollision->SetCollisionGroup(ECollisionOrder::BossSkill);
	WarlockCollision->SetCollisionType(ECollisionType::RotRect);

	InputOn(); // test
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
	WarlockRenderer->CreateAnimation("WarlockIdle", "DevilChurchWarlock.png", 0.0625f, false, 0, 16);
	WarlockRenderer->CreateAnimation("WarlockSkill", "DevilChurchWarlock.png", 0.0625f, true, 17, 23);

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
	if(true == IsDown('K'))
	{
		std::shared_ptr<AWarlockBlackSphere> BlackSphere = GetWorld()->SpawnActor<AWarlockBlackSphere>("BlackSphere");
		BlackSphere->SummonBlackSphere();
		BlackSphere->SetSummonBlackSpherePos(FVector(100.0f, 100.0f));
	}

	// 妮府傈.
	CollisionCheck(_DeltaTime);
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



void ADevilChurchWarlock::CollisionCheck(float _DeltaTime)
{
	WarlockCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			Hp -= 5;
		});
}
