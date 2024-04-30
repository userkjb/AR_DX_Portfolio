#include "PreCompile.h"
#include "WarlockBlackSphere.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerStruct.h"

AWarlockBlackSphere::AWarlockBlackSphere()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	BlackSphereRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	BlackSphereRenderer->SetupAttachment(Root);
	BlackSphereRenderer->SetOrder(ERenderOrder::Enemy);

	BlackSphereCollision = CreateDefaultSubObject<UCollision>("Collision");
	BlackSphereCollision->SetupAttachment(Root);
	BlackSphereCollision->SetCollisionGroup(ECollisionOrder::BossSkill);
	BlackSphereCollision->SetCollisionType(ECollisionType::CirCle);
	BlackSphereCollision->SetActive(false);
}

AWarlockBlackSphere::~AWarlockBlackSphere()
{
}

void AWarlockBlackSphere::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	StateInit();

	BlackSphereRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void AWarlockBlackSphere::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AWarlockBlackSphere::CreateAnimation()
{
	BlackSphereRenderer->CreateAnimation("DarkSphereSummon", "DevilChurchWarlockFX.png", 0.125f, false, 0, 15);
	BlackSphereRenderer->CreateAnimation("DarkSphereAttack", "DevilChurchWarlockFX.png", 0.125f, true, 16, 24);

	BlackSphereRenderer->ChangeAnimation("DarkSphereSummon");
}

void AWarlockBlackSphere::StateInit()
{
	State.CreateState("None");
	State.CreateState("DarkSphereSummon");
	State.CreateState("DarkSphereAttack");


	State.SetFunction("DarkSphereSummon",
		std::bind(&AWarlockBlackSphere::DarkSphereSummonBegin, this),
		std::bind(&AWarlockBlackSphere::DarkSphereSummonTick, this, std::placeholders::_1),
		std::bind(&AWarlockBlackSphere::DarkSphereSummonExit, this));

	State.SetFunction("DarkSphereAttack",
		std::bind(&AWarlockBlackSphere::DarkSphereAttackBegin, this),
		std::bind(&AWarlockBlackSphere::DarkSphereAttackTick, this, std::placeholders::_1),
		std::bind(&AWarlockBlackSphere::DarkSphereAttackExit, this));


	State.ChangeState("None");
}


#pragma region DarkSphereSummon
void AWarlockBlackSphere::DarkSphereSummonBegin()
{
	BlackSphereRenderer->ChangeAnimation("DarkSphereSummon");
	BlackSphereRenderer->SetPosition(SummonPos);
}

void AWarlockBlackSphere::DarkSphereSummonTick(float _DeltaTime)
{
	if (true == BlackSphereRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("DarkSphereAttack");
		return;
	}
}

void AWarlockBlackSphere::DarkSphereSummonExit()
{
}
#pragma endregion


#pragma region DarkSphereAttack
void AWarlockBlackSphere::DarkSphereAttackBegin()
{
	BlackSphereRenderer->ChangeAnimation("DarkSphereAttack");
	if (false == BlackSphereCollision->IsActive())
	{
		BlackSphereCollision->SetActive(true);
	}
	BlackSphereCollision->SetPosition(SummonPos);
	BlackSphereCollision->SetScale(FVector(100.0f, 100.0f));
	WaitingTime = 0.0f;
}

void AWarlockBlackSphere::DarkSphereAttackTick(float _DeltaTime)
{
	WaitingTime += _DeltaTime;


	// ÄÝ¸®Àü.
	CollisionCheck(_DeltaTime);
}

void AWarlockBlackSphere::DarkSphereAttackExit()
{
}
#pragma endregion

void AWarlockBlackSphere::CollisionCheck(float _DeltaTime)
{
	BlackSphereCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			EPlayerStateValue::Hp -= 5;
		});

	BlackSphereCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _WCollision)
		{
			BlackSphereRenderer->SetActive(false);
			BlackSphereCollision->SetActive(false);
		});
}
