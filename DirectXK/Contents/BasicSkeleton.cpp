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
	BasicSkeletonRenderer->SetDir(EEngineDir::Right);

	BasicSkeletonCollision = CreateDefaultSubObject<UCollision>("Collision");
	BasicSkeletonCollision->SetupAttachment(Root);
	BasicSkeletonCollision->SetCollisionGroup(ECollisionOrder::Monster_Attack);
	BasicSkeletonCollision->SetCollisionType(ECollisionType::RotRect);
	BasicSkeletonCollision->SetScale(FVector(66.0f, 60.0f));

	PlayerCheckCollision = CreateDefaultSubObject<UCollision>("Collision");
	PlayerCheckCollision->SetupAttachment(Root);
	PlayerCheckCollision->SetCollisionGroup(ECollisionOrder::Monster);
	PlayerCheckCollision->SetCollisionType(ECollisionType::RotRect);
	PlayerCheckCollision->SetScale(FVector(66.0f, 60.0f) * 4.0f); // 탐지 범위 설정.
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
			BasicSkeletonCollision->SetPosition(FVector(0.0f, 30.0f));
			PlayerCheckCollision->SetPosition(FVector(0.0f, 30.0f));
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



void ABasicSkeleton::IdleBegin()
{
	BasicSkeletonRenderer->ChangeAnimation("Idle");
	PlayerNotCatchTime = 0.0f;
}

void ABasicSkeleton::IdleTick(float _DeltaTime)
{
	PlayerNotCatchTime += _DeltaTime;
	CollisionCheck(PlayerNotCatchTime);

	if (3.0f <= PlayerNotCatchTime)
	{
		SKState.ChangeState("Run");
		return;
	}
}

void ABasicSkeleton::IdleExit()
{
	PlayerNotCatchTime = 0.0f;
	PreState = "Idle";
}



void ABasicSkeleton::RunBegin()
{
	BasicSkeletonRenderer->ChangeAnimation("Run");

	if (PreState == "Idle")
	{
		if (EEngineDir::Right == BasicSkeletonRenderer->GetDir())
		{
			BasicSkeletonRenderer->SetDir(EEngineDir::Left);
		}
		else
		{
			BasicSkeletonRenderer->SetDir(EEngineDir::Right);
		}
	}

	RunTime = 0.0f;
}

void ABasicSkeleton::RunTick(float _DeltaTime)
{
	RunTime += _DeltaTime;
	FVector V_Run = FVector::Zero;

	if (EEngineDir::Right == BasicSkeletonRenderer->GetDir())
	{
		V_Run = FVector::Right * RumSpeed * _DeltaTime;
		AddActorLocation(V_Run);
	}
	else
	{
		V_Run = FVector::Left * RumSpeed * _DeltaTime;
		AddActorLocation(V_Run);
	}
	
	if (3.0f <= RunTime)
	{
		SKState.ChangeState("Idle");
		return;
	}
}

void ABasicSkeleton::RunExit()
{
	RunTime = 0.0f;
	PreState = "Run";
}



void ABasicSkeleton::AttackBegin()
{
	BasicSkeletonRenderer->ChangeAnimation("Attack");
}

void ABasicSkeleton::AttackTick(float _DeltaTime)
{
	if (true == BasicSkeletonRenderer->IsCurAnimationEnd())
	{
		SKState.ChangeState("Idle");
		return;
	}
}

void ABasicSkeleton::AttackExit()
{
	PreState = "Attack";
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


void ABasicSkeleton::CollisionCheck(float _Time)
{
	PlayerCheckCollision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			SKState.ChangeState("Attack");
			return;
		}
	);
}
