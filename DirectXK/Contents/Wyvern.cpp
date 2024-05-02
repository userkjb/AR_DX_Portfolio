#include "PreCompile.h"
#include "Wyvern.h"
#include <EngineCore/DefaultSceneComponent.h>

AWyvern::AWyvern()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	WyvernRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	WyvernRenderer->SetupAttachment(Root);
	WyvernRenderer->SetOrder(ERenderOrder::Enemy);


}

AWyvern::~AWyvern()
{
}

void AWyvern::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	CreateAnimation();

	WyvernRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void AWyvern::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AWyvern::CreateAnimation()
{
	WyvernRenderer->CreateAnimation("Idle", "Wyvern", 0.0625f, true, 21, 29);

	WyvernRenderer->ChangeAnimation("Idle");
}

void AWyvern::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");

	State.SetFunction("Idle",
		std::bind(&AWyvern::IdleBegin, this),
		std::bind(&AWyvern::IdleTick, this, std::placeholders::_1),
		std::bind(&AWyvern::IdleExit, this));


	State.ChangeState("Idle");
}

void AWyvern::IdleBegin()
{
}

void AWyvern::IdleTick(float _DeltaTime)
{
	int a = 0;
}

void AWyvern::IdleExit()
{
}
