#include "PreCompile.h"
#include "Wyvern.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"
#include "LightningBall.h"

AWyvern::AWyvern()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

#ifdef _DEBUG
	ActorRender = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ActorRender->SetupAttachment(Root);
	ActorRender->SetOrder(ERenderOrder::Enemy);
#endif
	
	WyvernRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	WyvernRenderer->SetupAttachment(Root);
	WyvernRenderer->SetOrder(ERenderOrder::Enemy);

	WyvernCollision = CreateDefaultSubObject<UCollision>("Renderer");
	WyvernCollision->SetupAttachment(Root);
	WyvernCollision->SetCollisionGroup(ECollisionOrder::Monster_Attack);
	WyvernCollision->SetCollisionType(ECollisionType::RotRect);
	WyvernCollision->SetScale((FVector(72.f, 74.0f)) * 4.0f);

	PlayerCheckCol = CreateDefaultSubObject<UCollision>("Renderer");
	PlayerCheckCol->SetupAttachment(Root);
	PlayerCheckCol->SetCollisionGroup(ECollisionOrder::Monster_Search);
	PlayerCheckCol->SetCollisionType(ECollisionType::RotRect);
	PlayerCheckCol->SetScale((FVector(72.f, 74.0f)) * 8.0f);
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

#ifdef _DEBUG
	ActorRender->SetSprite("TestPointImage.png");
	ActorRender->SetAutoSize(UContentsConstValue::AutoSizeValue, true);

	InputOn(); // Test
#endif
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
			UEngineSound::SoundPlay("MonsterDie.mp3");
			Destroy();
		}
	);

	State.ChangeState("None");
}

void AWyvern::SettingBegin()
{
	SetActorLocation(InActorPos);
	if (EEngineDir::Right == InRenderDir)
	{
		InRenderPos *= -1.0f;
		WyvernRenderer->SetDir(InRenderDir);
		WyvernRenderer->SetPosition(InRenderPos);
		WyvernCollision->SetPosition(InRenderPos);
		PlayerCheckCol->SetPosition(InRenderPos);
	}
	else if (EEngineDir::Left == InRenderDir)
	{
		WyvernRenderer->SetDir(InRenderDir);
		WyvernRenderer->SetPosition(InRenderPos);
		WyvernCollision->SetPosition(InRenderPos);
		PlayerCheckCol->SetPosition(InRenderPos);
	}
}




void AWyvern::IdleBegin()
{
	if (false == WyvernRenderer->IsActive())
	{
		WyvernRenderer->SetActive(true);
		WyvernCollision->SetActive(true);
		PlayerCheckCol->SetActive(true);
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
	if (true == IsDown('I'))
	{
		if (EEngineDir::Right == WyvernRenderer->GetDir())
		{
			WyvernRenderer->SetDir(EEngineDir::Left);
		}
		else
		{
			WyvernRenderer->SetDir(EEngineDir::Right);
		}
	}

	std::string ActorPos = std::format("Actor Position : {}\n", GetActorLocation().ToString());
	std::string ActorRot = std::format("Actor Rot : {}\n", GetActorForwardVector().ToString());
	std::string WorldPos = std::format("Wyvern World Pos : {}\n", WyvernCollision->GetWorldPosition().ToString());
	std::string LocalPos = std::format("Wyvern Local Pos : {}\n", WyvernCollision->GetLocalPosition().ToString());
	std::string WorldRot = std::format("Wyvern World Rot : {}\n", WyvernCollision->GetWorldRotation().ToString());
	std::string LocalRot = std::format("Wyvern Local Rot : {}\n", WyvernCollision->GetLocalRotation().ToString());
	UEngineDebugMsgWindow::PushMsg(ActorPos);
	UEngineDebugMsgWindow::PushMsg(ActorRot);
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
	AttackDelayTime = 0.0f;
	PlayerCheckCol->SetActive(false);
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
		FVector Value = FVector::Zero;
		float RotationSpeed = 100.0f;
		Value.Z = RotationSpeed * _DeltaTime;

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
		if (-90.0f >= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Down)
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

	if (EEngineDir::Right == WyvernRenderer->GetDir() && 0.0f >= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Up)
	{
		State.ChangeState("Idle");
		return;
	}
	else if (EEngineDir::Left == WyvernRenderer->GetDir() && 0.0f <= WyvernCollision->GetWorldRotation().Z && true == b_Attack_Up)
	{
		State.ChangeState("Idle");
		return;
	}


#ifdef _DEBUG
	std::string ActorPos = std::format("Actor Position : {}\n", GetActorLocation().ToString());
	std::string ActorRot = std::format("Actor Rot : {}\n", GetActorForwardVector().ToString());
	std::string WorldPos = std::format("Wyvern World Pos : {}\n", WyvernCollision->GetWorldPosition().ToString());
	std::string LocalPos = std::format("Wyvern Local Pos : {}\n", WyvernCollision->GetLocalPosition().ToString());
	std::string WorldRot = std::format("Wyvern World Rot : {}\n", WyvernCollision->GetWorldRotation().ToString());
	std::string LocalRot = std::format("Wyvern Local Rot : {}\n", WyvernCollision->GetLocalRotation().ToString());
	UEngineDebugMsgWindow::PushMsg(ActorPos);
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
	PlayerCheckCol->SetActive(true);
	
	// Actor 초기화.
	SetActorRotation(FVector::Zero);
	WyvernRenderer->SetRotationDeg(FVector::Zero);
	{
		WyvernRenderer->SetPosition(FVector::Zero);
		WyvernCollision->SetPosition(FVector::Zero);
		PlayerCheckCol->SetPosition(FVector::Zero);

		if (EEngineDir::Right == WyvernRenderer->GetDir())
		{
			FVector DefaultPosition = GetActorLocation();
			DefaultPosition += InRenderPos * 2.0f;
			SetActorLocation(DefaultPosition);

			// Z축이 돌았잖아!!!
			WyvernRenderer->SetPosition(-InRenderPos);
			WyvernCollision->SetPosition(-InRenderPos);
			PlayerCheckCol->SetPosition(-InRenderPos);
		}
		else if (EEngineDir::Left == WyvernRenderer->GetDir())
		{
			FVector DefaultPosition = GetActorLocation();
			DefaultPosition -= InRenderPos * 2.0f;
			SetActorLocation(DefaultPosition);

			WyvernRenderer->SetPosition(InRenderPos);
			WyvernCollision->SetPosition(InRenderPos);
			PlayerCheckCol->SetPosition(InRenderPos);
		}
	}
}

void AWyvern::RenderAndCollisionPosSetting()
{
	WyvernRenderer->SetPosition(FVector::Zero);
	WyvernCollision->SetPosition(FVector::Zero);
	PlayerCheckCol->SetPosition(FVector::Zero);

	if (EEngineDir::Right != WyvernRenderer->GetDir())
	{
		WyvernRenderer->SetDir(EEngineDir::Right);

		FVector DefaultPosition = GetActorLocation();
		DefaultPosition += InRenderPos * 2.0f;
		SetActorLocation(DefaultPosition);

		WyvernRenderer->SetPosition(-InRenderPos);
		WyvernCollision->SetPosition(-InRenderPos);
		PlayerCheckCol->SetPosition(-InRenderPos);
	}
	else if (EEngineDir::Left != WyvernRenderer->GetDir())
	{
		WyvernRenderer->SetDir(EEngineDir::Left);

		FVector DefaultPosition = GetActorLocation();
		DefaultPosition -= InRenderPos * 2.0f;
		SetActorLocation(DefaultPosition);

		WyvernRenderer->SetPosition(InRenderPos);
		WyvernCollision->SetPosition(InRenderPos);
		PlayerCheckCol->SetPosition(InRenderPos);
	}
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

	PlayerCheckCol->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			AttackDelayTime += _DeltaTime;
			
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());

			FVector PlayerPos = Player->GetActorLocation();
			FVector WyvernPos = PlayerCheckCol->GetWorldPosition();

			if (WyvernPos.X <= PlayerPos.X)
			{
				if (EEngineDir::Right != WyvernRenderer->GetDir())
				{
					RenderAndCollisionPosSetting();
				}
			}
			else // Left
			{
				if (EEngineDir::Left != WyvernRenderer->GetDir())
				{
					RenderAndCollisionPosSetting();
				}
			}

			if (3.0f <= AttackDelayTime)
			{
				State.ChangeState("Attack");
				AttackDelayTime = 0.0f;
				return;
			}
		}
	);
}
