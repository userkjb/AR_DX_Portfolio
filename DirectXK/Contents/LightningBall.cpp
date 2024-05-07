#include "PreCompile.h"
#include "LightningBall.h"
#include <EngineCore/DefaultSceneComponent.h>

ALightningBall::ALightningBall()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	LightningBallRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	LightningBallRenderer->SetupAttachment(Root);
	LightningBallRenderer->SetOrder(ERenderOrder::Enemy);

	LightningBallCollision = CreateDefaultSubObject<UCollision>("Collision");
	LightningBallCollision->SetupAttachment(Root);
	LightningBallCollision->SetCollisionGroup(ECollisionOrder::Monster_Attack);
	LightningBallCollision->SetCollisionType(ECollisionType::CirCle);
	LightningBallCollision->SetScale(FVector(38.0f, 41.0f));
}

ALightningBall::~ALightningBall()
{
}

void ALightningBall::BeginPlay()
{
	Super::BeginPlay();
	CreateAnimation();
	StateInit();

	LightningBallRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ALightningBall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	CollisionCheck(_DeltaTime);
}

void ALightningBall::CreateAnimation()
{
	LightningBallRenderer->CreateAnimation("LightningBall", "ConditionParticle_Shock", 0.125f, true);

	LightningBallRenderer->ChangeAnimation("LightningBall");
}

void ALightningBall::StateInit()
{
	State.CreateState("None");
	State.CreateState("Setting");
	State.CreateState("Create");
	State.CreateState("Die");

	State.SetStartFunction("Setting", [=]()
		{
			SetActorLocation(CreatePos);
		}
	);

	State.SetFunction("Create",
		std::bind(&ALightningBall::CreateBegin, this),
		std::bind(&ALightningBall::CreateTick, this, std::placeholders::_1),
		std::bind(&ALightningBall::CreateExit, this));

	State.SetStartFunction("Die",
		std::bind(&ALightningBall::DieBegin, this));

	State.ChangeState("None");
}


void ALightningBall::CreateBegin()
{
	LightningBallRenderer->ChangeAnimation("LightningBall");
	LifeTime = 0.0f;
}
void ALightningBall::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;

	FVector ShotVector = MovePlayerDir * Speed * _DeltaTime;

	AddActorLocation(ShotVector);

	if (LifeIsTime <= LifeTime)
	{
		State.ChangeState("Die");
		return;
	}
}
void ALightningBall::CreateExit()
{
}


void ALightningBall::DieBegin()
{
	Destroy();
}


void ALightningBall::CollisionCheck(float _DeltaTime)
{
	LightningBallCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			State.ChangeState("Die");
			return;
		}
	);
}
