#include "PreCompile.h"
#include "Bird.h"
#include <EngineCore/DefaultSceneComponent.h>

ABird::ABird()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	BirdRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BirdRenderer->SetupAttachment(Root);
	BirdRenderer->SetOrder(ERenderOrder::MapObject);
}

ABird::~ABird()
{
}

void ABird::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	CreateAnimation();

	BirdRenderer->SetAutoSize(4.0f, true);
}

void ABird::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABird::StateInit()
{
	State.CreateState("None");
	State.CreateState("Setting");
	State.CreateState("Create");

	State.SetStartFunction("None", std::bind(&ABird::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ABird::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Create",
		std::bind(&ABird::CreateBegin, this),
		std::bind(&ABird::CreateTick, this, std::placeholders::_1),
		std::bind(&ABird::CreateExit, this));


	State.ChangeState("None");
}

void ABird::CreateAnimation()
{
	BirdRenderer->CreateAnimation("Idle", "Bird", 0.125f, true);

	BirdRenderer->ChangeAnimation("Idle");
}

void ABird::NoneBegin()
{
}

void ABird::NoneTick(float _DeltaTime)
{
}




void ABird::CreateBegin()
{
	SetActorLocation(CreateVector);
	int a = 0;
}

void ABird::CreateTick(float _DeltaTime)
{
	FVector CalMoveVector = FVector::Zero;
	CalMoveVector = MoveDir * MoveSpeed * _DeltaTime;
	AddActorLocation(CalMoveVector);








	FVector ActorPositionVector = GetActorLocation();
	if (1900.0f <= ActorPositionVector.X)
	{
		//int a = 0;
		Destroy();
	}
}

void ABird::CreateExit()
{
}
