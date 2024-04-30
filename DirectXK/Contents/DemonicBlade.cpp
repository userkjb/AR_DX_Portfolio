#include "PreCompile.h"
#include "DemonicBlade.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerStruct.h"

ADemonicBlade::ADemonicBlade()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	DemonicBladeRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	DemonicBladeRenderer->SetupAttachment(Root);
	DemonicBladeRenderer->SetPivot(EPivot::BOT);
	DemonicBladeRenderer->SetOrder(ERenderOrder::BossSkill_B);
	DemonicBladeRenderer->SetActive(false);

	DemonicBladeCollision = CreateDefaultSubObject<UCollision>("Collision");
	DemonicBladeCollision->SetupAttachment(Root);
	DemonicBladeCollision->SetCollisionGroup(ECollisionOrder::BossSkill);
	DemonicBladeCollision->SetCollisionType(ECollisionType::RotRect);
	DemonicBladeCollision->SetScale(FVector(108.0f, 212.0f));
}

ADemonicBlade::~ADemonicBlade()
{
}

void ADemonicBlade::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	InitState();

	DemonicBladeRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ADemonicBlade::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ADemonicBlade::InitState()
{
	State.CreateState("None");
	State.CreateState("Create"); // 생성 및 이동
	State.CreateState("Disappear"); // 소멸

	State.SetFunction("Create",
		std::bind(&ADemonicBlade::CreateBegin, this),
		std::bind(&ADemonicBlade::CreateTick, this, std::placeholders::_1),
		std::bind(&ADemonicBlade::CreateExit, this));

	State.SetFunction("Disappear",
		std::bind(&ADemonicBlade::DisappearBegin, this),
		std::bind(&ADemonicBlade::DisappearTick, this, std::placeholders::_1),
		std::bind(&ADemonicBlade::DisappearExit, this));


	State.ChangeState("None");
}

void ADemonicBlade::CreateAnimation()
{
	DemonicBladeRenderer->CreateAnimation("CreateDemonicBlade", "LasleyDemonicBladeFX.png", 0.0625f, true);
	DemonicBladeRenderer->CreateAnimation("DisappearDemonicBlade", "LasleyDemonicBladeDisappearFX.png", 0.0625f, false);
	DemonicBladeRenderer->CreateAnimation("LargeDemonicBlade", "LasleyLargeDemonicBladeFX.png", 0.0625f, true);
	DemonicBladeRenderer->CreateAnimation("LargeDemonicBladeDisappear", "LasleyLargeDemonicBladeDisappearFX.png", 0.0625f, true);


	DemonicBladeRenderer->ChangeAnimation("CreateDemonicBlade");
}


void ADemonicBlade::CreateBegin()
{
	if (false == Lasley_Large)
	{
		DemonicBladeRenderer->SetPosition(StartPos);
		DemonicBladeRenderer->SetDir(Dir);
		DemonicBladeRenderer->ChangeAnimation("CreateDemonicBlade");

		FVector StartPosition = StartPos;
		StartPosition.Y += 106.0f;
		DemonicBladeCollision->SetPosition(StartPosition);
	}
	else // 레이지 상태면!
	{
		DemonicBladeRenderer->SetPosition(StartPos);
		DemonicBladeRenderer->SetDir(Dir);
		DemonicBladeRenderer->ChangeAnimation("LargeDemonicBlade");

		FVector StartPosition = StartPos;
		StartPosition.Y += 106.0f;
		DemonicBladeCollision->SetPosition(StartPosition);
	}
	LifeTime = 0.0f;
}

void ADemonicBlade::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;
	float Speed = 500.0f;
	FVector MoveBlade = FVector::Zero;
	if (Dir == EEngineDir::Right)
	{
		MoveBlade = FVector::Right * Speed * _DeltaTime;
	}
	else if (Dir == EEngineDir::Left)
	{
		MoveBlade = FVector::Left * Speed * _DeltaTime;
	}
	AddActorLocation(MoveBlade);

	// 플레이어 체크
	CollisionCheck(_DeltaTime);

	if (2 <= LifeTime)
	{
		State.ChangeState("Disappear");
		return;
	}
}

void ADemonicBlade::CreateExit()
{
	LifeTime = 0.0f;
}




void ADemonicBlade::DisappearBegin()
{
	if (false == Lasley_Large)
	{
		DemonicBladeRenderer->ChangeAnimation("DisappearDemonicBlade");
	}
	else
	{
		DemonicBladeRenderer->ChangeAnimation("LargeDemonicBladeDisappear");
	}
}

void ADemonicBlade::DisappearTick(float _DeltaTime)
{
	FVector MoveVector = FVector::Zero;
	AddActorLocation(MoveVector); // 그 자리에 멈추고.

	// 플레이어 체크
	CollisionCheck(_DeltaTime);

	if (true == DemonicBladeRenderer->IsCurAnimationEnd())
	{
		DemonicBladeRenderer->SetActive(false);
		DemonicBladeCollision->SetActive(false);
		Destroy();
	}
}

void ADemonicBlade::DisappearExit()
{
}

void ADemonicBlade::CollisionCheck(float _DeltaTime)
{
	DemonicBladeCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			//APlayer* Player = dynamic_cast<APlayer*>(_Collison->GetActor());
			EPlayerStateValue::Hp -= 10;
		});

	// 벽.
	//DemonicBladeCollision->CollisionEnter(ECollisionOrder::MapDoor, [=](std::shared_ptr<UCollision> _Collison)
	//	{
	//		State.ChangeState("Disappear");
	//		return;
	//	});
}
