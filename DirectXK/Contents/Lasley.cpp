#include "PreCompile.h"
#include "Lasley.h"
#include <EngineCore/DefaultSceneComponent.h>

ALasley::ALasley()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
	
	LasleyRenderer = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleyRenderer->SetupAttachment(Root);
	LasleyRenderer->SetPivot(EPivot::BOT);
	LasleyRenderer->SetOrder(ERenderOrder::Boss);
	LasleyRenderer->SetDir(EEngineDir::Left);

	LasleySummonFX = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleySummonFX->SetupAttachment(Root);
	LasleySummonFX->SetPivot(EPivot::BOT);
	LasleySummonFX->SetOrder(ERenderOrder::BossSkill);
	

	InputOn(); // test
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

	LasleyRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	LasleySummonFX->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
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

	LasleySummonFX->CreateAnimation("LasleySummonFX", "LasleySummonsFX", 0.125f, false, 0, 12);
	LasleySummonFX->SetLastFrameCallback("LasleySummonFX", std::bind(&ALasley::LasleySummonEnd, this));

	// End
	LasleyRenderer->ChangeAnimation("None");
	LasleySummonFX->ChangeAnimation("LasleySummonFX");
}

void ALasley::StateInit()
{
	// Create
	State.CreateState("Summons");
	State.CreateState("Idle");
	State.CreateState("Wake");

	State.CreateState("DevilEye");
	State.CreateState("DemonicBlade");
	State.CreateState("DimensionCutter");
	State.CreateState("DoubleDimensionCutter");

	State.CreateState("Down");

	// Set Function

	State.SetFunction("Summons",
		std::bind(&ALasley::SummonsBegin, this),
		std::bind(&ALasley::SummonsTick, this, std::placeholders::_1),
		std::bind(&ALasley::SummonsEnd, this));

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

#pragma region Summons
void ALasley::SummonsBegin()
{
}

void ALasley::SummonsTick(float _DeltaTime)
{
}

void ALasley::SummonsEnd()
{
}
#pragma endregion

void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("DevilEye");
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
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
	if (true == IsDown('X'))
	{
		State.ChangeState("Idle");
		return;
	}
}

void ALasley::LasleySummonEnd()
{
	LasleySummonFX->SetActive(false);
}
