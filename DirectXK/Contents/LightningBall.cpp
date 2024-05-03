#include "PreCompile.h"
#include "LightningBall.h"
#include <EngineCore/DefaultSceneComponent.h>

ALightningBall::ALightningBall()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	LightningBallRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	LightningBallRenderer->SetupAttachment(Root);
	LightningBallRenderer->SetOrder(ERenderOrder::Enemy);
}

ALightningBall::~ALightningBall()
{
}

void ALightningBall::BeginPlay()
{
	Super::BeginPlay();
	CreateAnimation();
	StateInit();

	LightningBallRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ALightningBall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ALightningBall::CreateAnimation()
{
	LightningBallRenderer->CreateAnimation("LightningBall", "ConditionParticle_Shock", 0.125f, true);

	LightningBallRenderer->ChangeAnimation("LightningBall");
}

void ALightningBall::StateInit()
{
	State.CreateState("None");
	State.CreateState("Setting");
	State.CreateState("Create");

	State.SetStartFunction("Setting", [=]()
		{
			SetActorLocation(CreatePos);
		}
	);

	State.SetFunction("Create",
		std::bind(&ALightningBall::CreateBegin, this),
		std::bind(&ALightningBall::CreateTick, this, std::placeholders::_1),
		std::bind(&ALightningBall::CreateExit, this));

	State.ChangeState("None");
}


void ALightningBall::CreateBegin()
{
	LightningBallRenderer->ChangeAnimation("LightningBall");
}
void ALightningBall::CreateTick(float _DeltaTime)
{
	int a = 0;
}
void ALightningBall::CreateExit()
{
}
// ConditionParticle_Shock