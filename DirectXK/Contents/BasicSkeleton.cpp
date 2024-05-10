#include "PreCompile.h"
#include "BasicSkeleton.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "Player.h"
#include "PlayerStruct.h"

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
	PlayerCheckCollision->SetCollisionGroup(ECollisionOrder::Monster_Search);
	PlayerCheckCollision->SetCollisionType(ECollisionType::RotRect);
	PlayerCheckCollision->SetScale(FVector(66.0f, 60.0f) * 4.0f); // 탐지 범위 설정.

	AttackCol = CreateDefaultSubObject<UCollision>("Collision");
	AttackCol->SetupAttachment(Root);
	AttackCol->SetCollisionGroup(ECollisionOrder::Monster_Attack);
	AttackCol->SetCollisionType(ECollisionType::RotRect);
	AttackCol->SetScale(FVector(100.0f, 60.0f));
	AttackCol->SetActive(false);
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
	SKState.SetStartFunction("Die", [=]()
		{
			UEngineSound::SoundPlay("MonsterDie.mp3");
			Destroy();
		}
	);


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
	CollisionCheck(_DeltaTime);

	if (3.0f <= PlayerNotCatchTime)
	{
		SKState.ChangeState("Run");
		return;
	}
}

void ABasicSkeleton::IdleExit()
{
	if (PreState == "Run")
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

	PlayerNotCatchTime = 0.0f;
	PreState = "Idle";
}



void ABasicSkeleton::RunBegin()
{
	BasicSkeletonRenderer->ChangeAnimation("Run");

	RunTime = 0.0f;
}

void ABasicSkeleton::RunTick(float _DeltaTime)
{
	RunTime += _DeltaTime;
	CollisionCheck(_DeltaTime);
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
	PlayerCheckCollision->SetActive(false);
}

void ABasicSkeleton::AttackTick(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	BasicSkeletonRenderer->SetFrameCallback("Attack", 2, [=]()
		{
			AttackCol->SetActive(true);
			if (EEngineDir::Right == BasicSkeletonRenderer->GetDir())
			{
				AttackCol->SetPosition(FVector(50.0f, 0.0f));
			}
			else
			{
				AttackCol->SetPosition(FVector(-50.0f, 0.0f));
			}
		}
	);

	if (true == BasicSkeletonRenderer->IsCurAnimationEnd())
	{
		AttackCol->SetActive(false);
		SKState.ChangeState("Idle");
		return;
	}
}

void ABasicSkeleton::AttackExit()
{
	PreState = "Attack";
	PlayerCheckCollision->SetActive(true);
}



void ABasicSkeleton::CollisionCheck(float _DeltaTime)
{
	BasicSkeletonCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			Hp -= 10;
			if (Hp >= 0)
			{
				SKState.ChangeState("Die");
				return;
			}
		}
	);

	AttackCol->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			EPlayerStateValue::Hp -= 15;
		}
	);


	PlayerCheckCollision->CollisionEnter(ECollisionOrder::MapDoor, [=](std::shared_ptr<UCollision> _Collision)
		{
			SKState.ChangeState("Idle");
			return;
		});

	PlayerCheckCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());

			FVector PlayerPos = Player->GetActorLocation();
			FVector SkeletonPos = PlayerCheckCollision->GetWorldPosition();

			if (SkeletonPos.X <= PlayerPos.X)
			{
				BasicSkeletonRenderer->SetDir(EEngineDir::Right);
			}
			else
			{
				BasicSkeletonRenderer->SetDir(EEngineDir::Left);
			}

			SKState.ChangeState("Attack");
			return;
		}
	);
}
