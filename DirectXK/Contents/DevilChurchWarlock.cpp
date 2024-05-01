#include "PreCompile.h"
#include "DevilChurchWarlock.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineBase/EngineRandom.h>
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
	WarlockCollision->SetScale(FVector(88.0f, 84.0f));
	WarlockCollision->SetPosition({ SummonPos.X, (SummonPos.Y + 42.0f) });
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
	BlackSphereTime = 0.0f;
}

void ADevilChurchWarlock::AttackTick(float _DeltaTime)
{
	BlackSphereTime += _DeltaTime;

	// 구체 생성.
	if(2.0f <= BlackSphereTime)
	{
		int CreateCount = UEngineRandom::MainRandom.RandomInt(1, 3);
		for (size_t i = 0; i < CreateCount; i++)
		{
			int PositionX = UEngineRandom::MainRandom.RandomInt(170, 1680);
			int PositionY = UEngineRandom::MainRandom.RandomInt(170, 1040);

			std::shared_ptr<AWarlockBlackSphere> BlackSphere = GetWorld()->SpawnActor<AWarlockBlackSphere>("BlackSphere");
			BlackSphere->SetSummonBlackSpherePos(FVector(PositionX, PositionY));
			BlackSphere->SummonBlackSphere();

			BlackSpheres.push_back(BlackSphere);
		}

		BlackSphereTime = 0.0f;
	}

	
	// 워록 콜리전.
	CollisionCheck(_DeltaTime);

	//if (true == IsDown('P'))
	if (0 >= Hp)
	{
		State.ChangeState("WarlockDie");
		return;
	}
}

void ADevilChurchWarlock::AttackExit()
{
}
#pragma endregion


#pragma region WarlockDie
void ADevilChurchWarlock::DieBegin()
{
	WarlockRenderer->SetActive(false);
	// 다크 볼 지우기
	size_t Count = BlackSpheres.size();
	for (size_t i = 0; i < Count; i++)
	{
		BlackSpheres[i]->Destroy();
	}
	BlackSpheres.clear();
}

void ADevilChurchWarlock::DieTick(float _DeltaTime)
{
	WarlockCollision->SetActive(false);
	Destroy();
}

void ADevilChurchWarlock::DieExit()
{
}
#pragma endregion


void ADevilChurchWarlock::CollisionCheck(float _DeltaTime)
{
	WarlockCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			Hp -= 20;
			if (0 >= Hp)
			{
				State.ChangeState("WarlockDie");
				return;
			}
		});
}
