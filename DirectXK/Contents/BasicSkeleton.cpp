#include "PreCompile.h"
#include "BasicSkeleton.h"
#include <EngineCore/DefaultSceneComponent.h>

ABasicSkeleton::ABasicSkeleton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	BasicSkeletonRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BasicSkeletonRenderer->SetupAttachment(Root);
	BasicSkeletonRenderer->SetOrder(ERenderOrder::Enemy);


}

ABasicSkeleton::~ABasicSkeleton()
{
}

void ABasicSkeleton::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	StateInit();

	BasicSkeletonRenderer->SetAutoSize(1.0f, true);
}

void ABasicSkeleton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SKState.Update(_DeltaTime);
}

void ABasicSkeleton::CreateAnimation()
{
	BasicSkeletonRenderer->CreateAnimation("Idle", "sk_Idle.png", 0.125f, true);
	BasicSkeletonRenderer->CreateAnimation("Run", "sk_Run.png", 0.125f, true, 0, 6);
	BasicSkeletonRenderer->CreateAnimation("Attack", "sk_Attack.png", 0.125f, true);

	BasicSkeletonRenderer->ChangeAnimation("Idle");
}

void ABasicSkeleton::StateInit()
{
	SKState.CreateState("None");
	SKState.CreateState("Setting");
	SKState.SetStartFunction("Setting", [=]()
		{
			SetActorLocation(InPos);
		}
	);

	SKState.CreateState("Idle");
	SKState.CreateState("Run");
	SKState.CreateState("Attack");
	SKState.CreateState("Die");

	SKState.SetFunction("Idle",
		std::bind(&ABasicSkeleton::IdleBegin, this),
		std::bind(&ABasicSkeleton::IdleTick, this, std::placeholders::_1),
		std::bind(&ABasicSkeleton::IdleExit, this));
	SKState.SetFunction("Run",
		std::bind(&ABasicSkeleton::RunBegin, this),
		std::bind(&ABasicSkeleton::RunTick, this, std::placeholders::_1),
		std::bind(&ABasicSkeleton::RunExit, this));
	SKState.SetFunction("Attack",
		std::bind(&ABasicSkeleton::AttackBegin, this),
		std::bind(&ABasicSkeleton::AttackTick, this, std::placeholders::_1),
		std::bind(&ABasicSkeleton::AttackExit, this));
	SKState.SetFunction("Die",
		std::bind(&ABasicSkeleton::DieBegin, this),
		std::bind(&ABasicSkeleton::DieTick, this, std::placeholders::_1),
		std::bind(&ABasicSkeleton::DieExit, this));


	SKState.ChangeState("None");
}

void ABasicSkeleton::SettingBegin()
{
}




void ABasicSkeleton::IdleBegin()
{
	BasicSkeletonRenderer->ChangeAnimation("Idle");
}

void ABasicSkeleton::IdleTick(float _DeltaTime)
{
}

void ABasicSkeleton::IdleExit()
{
}

void ABasicSkeleton::RunBegin()
{
}

void ABasicSkeleton::RunTick(float _DeltaTime)
{
}

void ABasicSkeleton::RunExit()
{
}

void ABasicSkeleton::AttackBegin()
{
}

void ABasicSkeleton::AttackTick(float _DeltaTime)
{
}

void ABasicSkeleton::AttackExit()
{
}

void ABasicSkeleton::DieBegin()
{
}

void ABasicSkeleton::DieTick(float _DeltaTime)
{
}

void ABasicSkeleton::DieExit()
{
}
