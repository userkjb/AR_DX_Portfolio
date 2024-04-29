#include "PreCompile.h"
#include "DemonicBlade.h"
#include <EngineCore/DefaultSceneComponent.h>

ADemonicBlade::ADemonicBlade()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	DemonicBladeRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	DemonicBladeRenderer->SetupAttachment(Root);
	DemonicBladeRenderer->SetPivot(EPivot::BOT);
	DemonicBladeRenderer->SetOrder(ERenderOrder::BossSkill_B);
	DemonicBladeRenderer->SetActive(false);
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


	DemonicBladeRenderer->ChangeAnimation("CreateDemonicBlade");
}


void ADemonicBlade::CreateBegin()
{
	if (false == Lasley_Large)
	{
		DemonicBladeRenderer->SetPosition(StartPos);
		DemonicBladeRenderer->SetDir(Dir);
		DemonicBladeRenderer->ChangeAnimation("CreateDemonicBlade");
	}
	else
	{

	}
}

void ADemonicBlade::CreateTick(float _DeltaTime)
{
	float Speed = 500.0f;
	FVector MoveBlade = FVector::Zero;
	// 벽에 닿으면,
	if (Dir == EEngineDir::Right)
	{
		MoveBlade = FVector::Right * Speed * _DeltaTime;
	}
	else if (Dir == EEngineDir::Left)
	{
		MoveBlade = FVector::Left * Speed * _DeltaTime;
	}
	AddActorLocation(MoveBlade);
}

void ADemonicBlade::CreateExit()
{
}




void ADemonicBlade::DisappearBegin()
{
}

void ADemonicBlade::DisappearTick(float _DeltaTime)
{
}

void ADemonicBlade::DisappearExit()
{
}
