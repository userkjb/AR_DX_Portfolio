#include "PreCompile.h"
#include "Lasley.h"

ALasley::ALasley()
{
	LasleyRenderer = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
}

ALasley::~ALasley()
{
}

void ALasley::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(45.0f, 44.0f, 0.0f) * 2.0f);

	CreateAnimation();

	StateChange(ELasleyState::None);
}

void ALasley::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ALasley::StateChange(ELasleyState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ELasleyState::None:
			NoneBegin();
			break;
		case ELasleyState::DevilEye:
			DevilEyeBegin();
			break;
		case ELasleyState::Idle:
			IdleBegin();
			break;
		case ELasleyState::Wake:
			WakeBegin();
			break;
		case ELasleyState::DemonicBlade:
			DemonicBladeBegin();
			break;
		case ELasleyState::DimensionCutter:
			DimensionCutterBegin();
			break;
		case ELasleyState::DoubleDimensionCutter:
			DoubleDimensionCutterBegin();
			break;
		case ELasleyState::Down:
			DownBegin();
			break;
		default :
			break;
		}
	}

	State = _State;
}

void ALasley::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ELasleyState::None:
		NoneTick(_DeltaTime);
		break;
	case ELasleyState::DevilEye:
		DevilEyeTick(_DeltaTime);
		break;
	case ELasleyState::Idle:
		IdleTick(_DeltaTime);
		break;
	case ELasleyState::Wake:
		WakeTick(_DeltaTime);
		break;
	case ELasleyState::DemonicBlade:
		DemonicBladeTick(_DeltaTime);
		break;
	case ELasleyState::DimensionCutter:
		DimensionCutterTick(_DeltaTime);
		break;
	case ELasleyState::DoubleDimensionCutter:
		DoubleDimensionCutterTick(_DeltaTime);
		break;
	case ELasleyState::Down:
		DownTick(_DeltaTime);
		break;
	default:
		break;
	}
}

void ALasley::CreateAnimation()
{
	// State
	LasleyRenderer->CreateAnimation("DevilEye", "LasleyDevilEye", 0.125f);
	LasleyRenderer->CreateAnimation("Idle", "LasleyIdle", 0.125f);
	LasleyRenderer->CreateAnimation("Wake", "LasleyWake", 0.125f);
	LasleyRenderer->CreateAnimation("Down", "LasleyDown", 0.125f);

	// Skill
	LasleyRenderer->CreateAnimation("DemonicBlade", "LasleyDemonicBlade", 0.125f);
	LasleyRenderer->CreateAnimation("DimensionCutter", "LasleyDimensionCutter", 0.125f);
	LasleyRenderer->CreateAnimation("DoubleDimensionCutter", "LasleyDoubleDimensionCutter", 0.125f);

	LasleyRenderer->ChangeAnimation("DevilEye");
}


// --- State ---
void ALasley::NoneBegin()
{
}

void ALasley::NoneTick(float _DeltaTime)
{
}

void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("DevilEye");
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
}

void ALasley::IdleBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
}

void ALasley::IdleTick(float _DeltaTime)
{
}

void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
}

void ALasley::WakeTick(float _DeltaTime)
{
}

void ALasley::DemonicBladeBegin()
{
	LasleyRenderer->ChangeAnimation("DemonicBlade");
}

void ALasley::DemonicBladeTick(float _DeltaTime)
{
}

void ALasley::DimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DimensionCutter");
}

void ALasley::DimensionCutterTick(float _DeltaTime)
{
}

void ALasley::DoubleDimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DoubleDimensionCutter");
}

void ALasley::DoubleDimensionCutterTick(float _DeltaTime)
{
}

void ALasley::DownBegin()
{
	LasleyRenderer->ChangeAnimation("Down");
}

void ALasley::DownTick(float _DeltaTime)
{
}
