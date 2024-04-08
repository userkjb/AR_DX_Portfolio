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

