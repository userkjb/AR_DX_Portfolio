#include "PreCompile.h"
#include "Tentacle.h"

ATentacle::ATentacle()
{
	TentacleRenderer = CreateDefaultSubObject<USpriteRenderer>("TentacleRenderer");
	
	InputOn(); // test
}

ATentacle::~ATentacle()
{
}

void ATentacle::BeginPlay()
{
	Super::BeginPlay();

	TentacleRenderer->CreateAnimation("Tentacle_Start", "LasleyTentacle", { 0.125f }, { 0, 1 }, false);
	TentacleRenderer->CreateAnimation("Tentacle_Tick", "LasleyTentacle", { 0.125f }, { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }, true);
	TentacleRenderer->CreateAnimation("Tentacle_End", "LasleyTentacle", { 0.125f }, { 14, 15, 16, 17, 18, 19, 20, 21, 22 }, false);

	TentacleRenderer->ChangeAnimation("Tentacle_Start");
	TentacleRenderer->SetActive(false);
}

void ATentacle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATentacle::StateInit()
{
	State.CreateState("Tentacle_Start");
	State.CreateState("Tentacle_Tick");
	State.CreateState("Tentacle_End");

	State.SetFunction("Tentacle_Start",
		std::bind(&ATentacle::StartBegin, this),
		std::bind(&ATentacle::StartTick, this, std::placeholders::_1),
		std::bind(&ATentacle::StartEnd, this));
	State.SetFunction("Tentacle_Tick",
		std::bind(&ATentacle::TickBegin, this),
		std::bind(&ATentacle::TickTick, this, std::placeholders::_1),
		std::bind(&ATentacle::TickEnd, this));
	State.SetFunction("Tentacle_End",
		std::bind(&ATentacle::EndBegin, this),
		std::bind(&ATentacle::EndTick, this, std::placeholders::_1),
		std::bind(&ATentacle::EndEnd, this));

	State.ChangeState("Tentacle_Start");
}

void ATentacle::StartBegin()
{
	TentacleRenderer->ChangeAnimation("Tentacle_Start");
}

void ATentacle::StartTick(float _DeltaTime)
{
	if (true == IsDown('H') && TentacleRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Tentacle_Tick");
		return;
	}
}

void ATentacle::StartEnd()
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

void ATentacle::TickEnd()
{
	LifeTime = 0.0f;
}

void ATentacle::EndBegin()
{
	TentacleRenderer->ChangeAnimation("Tentacle_End");
}

void ATentacle::EndTick(float _DeltaTime)
{
	if (true == IsDown('H') && TentacleRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("");////////////////////////////////////////
		return;
	}
}

void ATentacle::EndEnd()
{
	TentacleRenderer->SetActive(false);
}
