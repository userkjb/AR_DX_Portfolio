#include "PreCompile.h"
#include "Lasley.h"
#include <EngineCore/SpriteRenderer.h>

ALasley::ALasley()
{
	LasleyRenderer = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	InputOn();
}

ALasley::~ALasley()
{
}

void ALasley::BeginPlay()
{
	Super::BeginPlay();

	//SetActorScale3D(FVector(45.0f, 44.0f, 0.0f));

	CreateAnimation();

	StateInit();

	LasleyRenderer->SetAutoSize(5.0f, true);
	LasleyRenderer->SetOrder(ERenderOrder::Boss);
}

void ALasley::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ALasley::CreateAnimation()
{
	LasleyRenderer->CreateAnimation("None", "LasleyNone", 0.25);
	// State
	LasleyRenderer->CreateAnimation("DevilEye", "LasleyDevilEye", 0.125f);
	LasleyRenderer->CreateAnimation("Idle", "LasleyIdle", 0.125f);
	LasleyRenderer->CreateAnimation("Wake", "LasleyWake", 0.125f);
	LasleyRenderer->CreateAnimation("Down", "LasleyDown", 0.125f);

	// Skill
	LasleyRenderer->CreateAnimation("DemonicBlade", "LasleyDemonicBlade", 0.125f);
	LasleyRenderer->CreateAnimation("DimensionCutter", "LasleyDimensionCutter", 0.125f);
	LasleyRenderer->CreateAnimation("DoubleDimensionCutter", "LasleyDoubleDimensionCutter", 0.125f);

	LasleyRenderer->ChangeAnimation("None");
}

void ALasley::StateInit()
{
	// Create
	State.CreateState("Idle");
	State.CreateState("Wake");

	State.CreateState("DevilEye");
	State.CreateState("DemonicBlade");
	State.CreateState("DimensionCutter");
	State.CreateState("DoubleDimensionCutter");

	State.CreateState("Down");

	// Set Function
	State.SetStartFunction("Idle", std::bind(&ALasley::IdleBegin, this));
	State.SetUpdateFunction("Idle", std::bind(&ALasley::IdleTick, this, std::placeholders::_1));

	State.SetStartFunction ("DevilEye", std::bind(&ALasley::DevilEyeBegin, this));
	State.SetUpdateFunction("DevilEye", std::bind(&ALasley::DevilEyeTick, this, std::placeholders::_1));
	State.SetStartFunction ("Wake", std::bind(&ALasley::WakeBegin, this));
	State.SetUpdateFunction("Wake", std::bind(&ALasley::WakeTick, this, std::placeholders::_1));
	State.SetStartFunction ("DemonicBlade", std::bind(&ALasley::DemonicBladeBegin, this));
	State.SetUpdateFunction("DemonicBlade", std::bind(&ALasley::DemonicBladeTick, this, std::placeholders::_1));
	State.SetStartFunction ("DimensionCutter", std::bind(&ALasley::DimensionCutterBegin, this));
	State.SetUpdateFunction("DimensionCutter", std::bind(&ALasley::DimensionCutterTick, this, std::placeholders::_1));
	State.SetStartFunction ("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterBegin, this));
	State.SetUpdateFunction("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterTick, this, std::placeholders::_1));
	State.SetStartFunction ("Down", std::bind(&ALasley::DownBegin, this));
	State.SetUpdateFunction("Down", std::bind(&ALasley::DownTick, this, std::placeholders::_1));


	// Change
	State.ChangeState("Idle");
}


// --- State ---
//void ALasley::NoneBegin()
//{
//}
//
//void ALasley::NoneTick(float _DeltaTime)
//{
//	if (true == IsDown('A'))
//	{
//		StateChange(ELasleyState::DevilEye);
//		return;
//	}
//}

void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("DevilEye");
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("Idle");
		return;
	}
}

void ALasley::IdleBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
}

void ALasley::IdleTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("Wake");
		return;
	}
}

void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
}

void ALasley::WakeTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("DemonicBlade");
		return;
	}
}

void ALasley::DemonicBladeBegin()
{
	LasleyRenderer->ChangeAnimation("DemonicBlade");
}

void ALasley::DemonicBladeTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("DimensionCutter");
		return;
	}
}

void ALasley::DimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DimensionCutter");
}

void ALasley::DimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("DoubleDimensionCutter");
		return;
	}
}

void ALasley::DoubleDimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DoubleDimensionCutter");
}

void ALasley::DoubleDimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("Down");
		return;
	}
}

void ALasley::DownBegin()
{
	LasleyRenderer->ChangeAnimation("Down");
}

void ALasley::DownTick(float _DeltaTime)
{
	if (true == IsDown('A'))
	{
		State.ChangeState("Idle");
		return;
	}
}
