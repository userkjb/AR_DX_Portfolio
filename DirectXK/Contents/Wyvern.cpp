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

	WyvernCollision = CreateDefaultSubObject<UCollision>("Renderer");
	WyvernCollision->SetupAttachment(Root);
	WyvernCollision->SetCollisionGroup(ECollisionOrder::Monster_Attack);
	WyvernCollision->SetCollisionType(ECollisionType::RotRect);
	WyvernCollision->SetScale((FVector(72.f, 74.0f)) * 4.0f);

	InputOn(); // Test
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
	
	InputOn(); // test
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


	State.ChangeState("None");
}

void AWyvern::IdleBegin()
{
	WyvernRenderer->SetPosition(InPos);
	if (false == WyvernRenderer->IsActive())
	{
		WyvernRenderer->SetActive(true);
	}

	WyvernCollision->SetPosition(WyvernRenderer->GetWorldPosition());
}

void AWyvern::IdleTick(float _DeltaTime)
{
	int a = 0;
}

void AWyvern::IdleExit()
{
}
