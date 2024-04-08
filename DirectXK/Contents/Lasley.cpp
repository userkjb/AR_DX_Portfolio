#include "PreCompile.h"
#include "Lasley.h"

ALasley::ALasley()
{
	LasleyRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ALasley::~ALasley()
{
}

void ALasley::BeginPlay()
{
	Super::BeginPlay();

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
