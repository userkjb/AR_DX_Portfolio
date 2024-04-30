#include "PreCompile.h"
#include "Tentacle.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerStruct.h"

ATentacle::ATentacle()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("TentacleRenderer");
	SetRoot(Root);


	TentacleRenderer = CreateDefaultSubObject<USpriteRenderer>("TentacleRenderer");
	TentacleRenderer->SetupAttachment(Root);
	TentacleRenderer->SetOrder(ERenderOrder::BossSkill_B);
	TentacleRenderer->SetPosition(FVector(100.0f, 100.0f));
	TentacleRenderer->SetActive(false);

	TentacleCollision = CreateDefaultSubObject<UCollision>("TentacleCollision");
	TentacleCollision->SetupAttachment(Root);
	TentacleCollision->SetCollisionGroup(ECollisionOrder::BossSkill);
	TentacleCollision->SetCollisionType(ECollisionType::RotRect);
	TentacleCollision->SetPosition(TentacleRenderer->GetLocalPosition());
	TentacleCollision->SetScale(ThisScale);
}

ATentacle::~ATentacle()
{
}

void ATentacle::BeginPlay()
{
	Super::BeginPlay();

	//TentacleRenderer->CreateAnimation("Tentacle_Tick", "LasleyTentacle", { 0.125f }, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }, true);
	TentacleRenderer->CreateAnimation("Tentacle_Start", "LasleyTentacle", 0.125f, false, 0, 6);
	TentacleRenderer->CreateAnimation("Tentacle_Tick", "LasleyTentacle", 0.125f, true, 7, 13);
	TentacleRenderer->CreateAnimation("Tentacle_End", "LasleyTentacle", 0.125f, false, 14, 22);
	
	TentacleRenderer->ChangeAnimation("Tentacle_Start");

	StateInit();

	TentacleRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ATentacle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ATentacle::StateInit()
{
	State.CreateState("Tentacle_None");
	State.CreateState("Tentacle_Start");
	State.CreateState("Tentacle_Tick");
	State.CreateState("Tentacle_End");
	State.CreateState("Tentacle_Destroy");

	State.SetFunction("Tentacle_Start",
		std::bind(&ATentacle::StartBegin, this),
		std::bind(&ATentacle::StartTick, this, std::placeholders::_1),
		std::bind(&ATentacle::StartExit, this));
	State.SetFunction("Tentacle_Tick",
		std::bind(&ATentacle::TickBegin, this),
		std::bind(&ATentacle::TickTick, this, std::placeholders::_1),
		std::bind(&ATentacle::TickExit, this));
	State.SetFunction("Tentacle_End",
		std::bind(&ATentacle::EndBegin, this),
		std::bind(&ATentacle::EndTick, this, std::placeholders::_1),
		std::bind(&ATentacle::EndExit, this));

	State.SetStartFunction("Tentacle_Destroy", std::bind(&ATentacle::DestroyBegin, this));

	State.ChangeState("Tentacle_None");
}


void ATentacle::StartBegin()
{
	if (false == TentacleRenderer->IsActive())
	{
		TentacleRenderer->SetActive(true);
	}
	TentacleRenderer->ChangeAnimation("Tentacle_Start");
}

void ATentacle::StartTick(float _DeltaTime)
{
	if (true == TentacleRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Tentacle_Tick");
		return;
	}
}

void ATentacle::StartExit()
{
}



void ATentacle::TickBegin()
{
	TentacleRenderer->ChangeAnimation("Tentacle_Tick");
	LifeTime = 0.0f;
}

void ATentacle::TickTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;
	if (LifeTime >= 2.0f)
	{
		State.ChangeState("Tentacle_End");
		return;
	}
}

void ATentacle::TickExit()
{
	LifeTime = 0.0f;
}



void ATentacle::EndBegin()
{
	TentacleRenderer->ChangeAnimation("Tentacle_End");
}

void ATentacle::EndTick(float _DeltaTime)
{
	if (true == TentacleRenderer->IsCurAnimationEnd())
	{
		TentacleCollision->SetActive(false);
		TentacleRenderer->SetActive(false);
		Destroy();
	}
}

void ATentacle::EndExit()
{
	//TentacleRenderer->SetActive(false);
}


void ATentacle::DestroyBegin()
{
	Destroy();
}




void ATentacle::CollisionCheck(float _DeltaTime)
{
	
	TentacleCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			//APlayer* Player = dynamic_cast<APlayer*>(_Collison->GetActor());
			EPlayerStateValue::Hp -= 10;
		});
}
