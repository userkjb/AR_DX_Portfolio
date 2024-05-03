#include "PreCompile.h"
#include "Wyvern.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"

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

	PlayerCheck = CreateDefaultSubObject<UCollision>("Renderer");
	PlayerCheck->SetupAttachment(Root);
	PlayerCheck->SetCollisionGroup(ECollisionOrder::Monster);
	PlayerCheck->SetCollisionType(ECollisionType::RotRect);
	PlayerCheck->SetScale((FVector(72.f, 74.0f)) * 8.0f);

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
	State.CreateState("Setting");
	State.CreateState("Idle");

	State.SetStartFunction("Setting", std::bind(&AWyvern::SettingBegin, this));

	State.SetFunction("Idle",
		std::bind(&AWyvern::IdleBegin, this),
		std::bind(&AWyvern::IdleTick, this, std::placeholders::_1),
		std::bind(&AWyvern::IdleExit, this));


	State.ChangeState("None");
}

void AWyvern::SettingBegin()
{
	SetActorLocation(InActorPos);
	WyvernRenderer->SetPosition(InRenderPos);
	WyvernCollision->SetPosition(InRenderPos);
	PlayerCheck->SetPosition(InRenderPos);
}



void AWyvern::IdleBegin()
{
	if (false == WyvernRenderer->IsActive())
	{
		WyvernRenderer->SetActive(true);
		WyvernCollision->SetActive(true);
		PlayerCheck->SetActive(true);
	}
}

void AWyvern::IdleTick(float _DeltaTime)
{
	

	if (true == IsPress('N'))
	{
		FVector Value = FVector(-2.0f, 0.0f, 0.0f);
		AddActorLocation(Value);
	}
	if (true == IsPress('M'))
	{
		FVector Value = FVector(2.0f, 0.0f, 0.0f);
		AddActorLocation(Value);
	}
	if (true == IsPress('B'))
	{
		FVector Value = FVector(0.0f, 0.0f, 1.0f);
		AddActorRotation(Value);
		WyvernRenderer->AddRotationDeg(-Value);
	}
	if (true == IsPress('H'))
	{
		FVector Value = FVector(0.0f, 0.0f, -1.0f);
		AddActorRotation(Value);
		WyvernRenderer->AddRotationDeg(-Value);
	}

	std::string WorldPos = std::format("World Pos : {}", WyvernCollision->GetWorldPosition().ToString());
	std::string LocalPos = std::format("Local Pos : {}", WyvernCollision->GetLocalPosition().ToString());
	std::string WorldRot = std::format("World Rot : {}", WyvernCollision->GetWorldRotation().ToString());
	std::string LocalRot = std::format("Local Rot : {}", WyvernCollision->GetLocalRotation().ToString());
	UEngineDebugMsgWindow::PushMsg(WorldPos);
	UEngineDebugMsgWindow::PushMsg(LocalPos);
	UEngineDebugMsgWindow::PushMsg(WorldRot);
	UEngineDebugMsgWindow::PushMsg(LocalRot);
}

void AWyvern::IdleExit()
{
}

void AWyvern::CollisionCheck(float _DeltaTime)
{
	WyvernCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{

		}
	);


	PlayerCheck->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());

		}
	);
}
