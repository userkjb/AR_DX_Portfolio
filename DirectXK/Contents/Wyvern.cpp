#include "PreCompile.h"
#include "Wyvern.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"
#include "LightningBall.h"

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

#ifdef _DEBUG
	InputOn(); // Test
#endif
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
	WyvernRenderer->CreateAnimation("Attack_Ready", "Wyvern", 0.0625f, false, 0, 8);
	WyvernRenderer->CreateAnimation("Attack_Down", "Wyvern", 0.0625f, true, 9, 12);
	WyvernRenderer->CreateAnimation("Attack_Up_One", "Wyvern", 0.0625f, false, 13, 16);
	WyvernRenderer->CreateAnimation("Attack_Up", "Wyvern", 0.0625f, true, 17, 20);

	WyvernRenderer->ChangeAnimation("Idle");
}

void AWyvern::StateInit()
{
	State.CreateState("None");
	State.CreateState("Setting");
	State.CreateState("Idle");
	State.CreateState("Attack");
	State.CreateState("Die");

	State.SetStartFunction("Setting", std::bind(&AWyvern::SettingBegin, this));

	State.SetFunction("Idle",
		std::bind(&AWyvern::IdleBegin, this),
		std::bind(&AWyvern::IdleTick, this, std::placeholders::_1),
		std::bind(&AWyvern::IdleExit, this));

	State.SetFunction("Attack",
		std::bind(&AWyvern::AttackBegin, this),
		std::bind(&AWyvern::AttackTick, this, std::placeholders::_1),
		std::bind(&AWyvern::AttackExit, this));

	State.SetStartFunction("Die", [=]()
		{
			Destroy();
		}
	);

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

	WyvernRenderer->ChangeAnimation("Idle");
	AttackDelayTime = 0.0f;
}

void AWyvern::IdleTick(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);


#ifdef _DEBUG
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

	std::string WorldPos = std::format("Wyvern World Pos : {}", WyvernCollision->GetWorldPosition().ToString());
	std::string LocalPos = std::format("Wyvern Local Pos : {}", WyvernCollision->GetLocalPosition().ToString());
	std::string WorldRot = std::format("Wyvern World Rot : {}", WyvernCollision->GetWorldRotation().ToString());
	std::string LocalRot = std::format("Wyvern Local Rot : {}", WyvernCollision->GetLocalRotation().ToString());
	UEngineDebugMsgWindow::PushMsg(WorldPos);
	UEngineDebugMsgWindow::PushMsg(LocalPos);
	UEngineDebugMsgWindow::PushMsg(WorldRot);
	UEngineDebugMsgWindow::PushMsg(LocalRot);
#endif
}

void AWyvern::IdleExit()
{
	AttackDelayTime = 0.0f;
}



void AWyvern::AttackBegin()
{
	WyvernRenderer->ChangeAnimation("Attack_Ready");
	ChangeAnimation_One = false;
}

void AWyvern::AttackTick(float _DeltaTime)
{
	CollisionCheck(_DeltaTime);
	// 공격 준비가 끝나면,
	WyvernRenderer->SetLastFrameCallback("Attack_Ready", [=]()
		{
			// 내려가면서 공격.
			Attack_Ready = true;
			WyvernRenderer->ChangeAnimation("Attack_Down");
		}
	);

	if (true == Attack_Ready)
	{
		FVector Value = FVector(0.0f, 0.0f, 0.25f);
		if (EEngineDir::Right == WyvernRenderer->GetDir())
		{
			AddActorRotation(Value);
			WyvernRenderer->AddRotationDeg(-Value);
		}
		else if (EEngineDir::Left == WyvernRenderer->GetDir())
		{
			AddActorRotation(-Value);
			WyvernRenderer->AddRotationDeg(Value);
		}
	}

	WyvernRenderer->SetFrameCallback("Attack_Down", 0, [=]()
		{
			// 공격!
			//FVector BallPos = GetActorLocation();
			FVector BallPos = WyvernRenderer->GetWorldPosition();
			std::shared_ptr<ALightningBall> LightningBall = GetWorld()->SpawnActor<ALightningBall>("LightningBall");
			LightningBall->SetPlayerDir(SendPlayerDir);
			LightningBall->SettingActorPosition(BallPos);
			LightningBall->CreateLightningBool();
		}
	);
	WyvernRenderer->SetFrameCallback("Attack_Down", 2, [=]()
		{
			// 공격!
			FVector BallPos = WyvernRenderer->GetWorldPosition();
			std::shared_ptr<ALightningBall> LightningBall = GetWorld()->SpawnActor<ALightningBall>("LightningBall");
			LightningBall->SetPlayerDir(SendPlayerDir);
			LightningBall->SettingActorPosition(BallPos);
			LightningBall->CreateLightningBool();
			b_Attack_Down = true;
		}
	);

	if (EEngineDir::Right == WyvernRenderer->GetDir())
	{
		if (90.0f <= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Down)
		{
			if (false == ChangeAnimation_One)
			{
				WyvernRenderer->ChangeAnimation("Attack_Up_One");
				ChangeAnimation_One = true;
			}
		}
	}
	else if (EEngineDir::Left == WyvernRenderer->GetDir())
	{
		float testz = WyvernCollision->GetWorldRotation().Z;
		if (90.0f >= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Down)
		{
			if (false == ChangeAnimation_One)
			{
				WyvernRenderer->ChangeAnimation("Attack_Up_One");
				ChangeAnimation_One = true;
			}
		}
	}
	

	WyvernRenderer->SetLastFrameCallback("Attack_Up_One", [=]()
		{
			WyvernRenderer->ChangeAnimation("Attack_Up");
			b_Attack_Up = true;
		}
	);

	WyvernRenderer->SetFrameCallback("Attack_Up", 0, [=]()
		{
			// 공격!
			FVector BallPos = WyvernRenderer->GetWorldPosition();
			std::shared_ptr<ALightningBall> LightningBall = GetWorld()->SpawnActor<ALightningBall>("LightningBall");
			LightningBall->SetPlayerDir(SendPlayerDir);
			LightningBall->SettingActorPosition(BallPos);
			LightningBall->CreateLightningBool();
		}
	);
	WyvernRenderer->SetFrameCallback("Attack_Up", 2, [=]()
		{
			// 공격!
			FVector BallPos = WyvernRenderer->GetWorldPosition();
			std::shared_ptr<ALightningBall> LightningBall = GetWorld()->SpawnActor<ALightningBall>("LightningBall");
			LightningBall->SetPlayerDir(SendPlayerDir);
			LightningBall->SettingActorPosition(BallPos);
			LightningBall->CreateLightningBool();
		}
	);

	if (0.0f >= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Up)
	{
		State.ChangeState("Idle");
		return;
	}


#ifdef _DEBUG
	std::string ActorRot = std::format("Actor Rot : {}\n", GetActorForwardVector().ToString());
	std::string WorldPos = std::format("Wyvern World Pos : {}\n", WyvernCollision->GetWorldPosition().ToString());
	std::string LocalPos = std::format("Wyvern Local Pos : {}\n", WyvernCollision->GetLocalPosition().ToString());
	std::string WorldRot = std::format("Wyvern World Rot : {}\n", WyvernCollision->GetWorldRotation().ToString());
	std::string LocalRot = std::format("Wyvern Local Rot : {}\n", WyvernCollision->GetLocalRotation().ToString());
	
	UEngineDebugMsgWindow::PushMsg(ActorRot);
	UEngineDebugMsgWindow::PushMsg(WorldPos);
	UEngineDebugMsgWindow::PushMsg(LocalPos);
	UEngineDebugMsgWindow::PushMsg(WorldRot);
	UEngineDebugMsgWindow::PushMsg(LocalRot);
#endif
}

void AWyvern::AttackExit()
{
	Attack_Ready = false;
	b_Attack_Down = false;
	b_Attack_Up = false;
}

void AWyvern::CollisionCheck(float _DeltaTime)
{
	WyvernCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			Hp -= 10;
			if (Hp <= 0)
			{
				State.ChangeState("Die");
				return;
			}
		}
	);

	PlayerCheck->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			AttackDelayTime += _DeltaTime;
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());

			FVector PlayerPos = Player->GetActorLocation();
			FVector WyvernPos = PlayerCheck->GetWorldPosition();

			//float Value = PlayerPos.X - WyvernPos.X;
			if (WyvernPos.X <= PlayerPos.X)
			{
				WyvernRenderer->SetDir(EEngineDir::Right);
			}
			else
			{
				WyvernRenderer->SetDir(EEngineDir::Left);
			}

			if (3.0f <= AttackDelayTime)
			{
				State.ChangeState("Attack");
				return;
			}
		}
	);
}
