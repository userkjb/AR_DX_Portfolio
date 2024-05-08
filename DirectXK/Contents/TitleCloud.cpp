#include "PreCompile.h"
#include "TitleCloud.h"
#include <EngineCore/DefaultSceneComponent.h>

ATitleCloud::ATitleCloud()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	CloudRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	CloudRenderer->SetupAttachment(Root);
}

ATitleCloud::~ATitleCloud()
{
}

void ATitleCloud::BeginPlay()
{
	Super::BeginPlay();

	StateInit();

	CloudRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ATitleCloud::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
}

void ATitleCloud::StateInit()
{
	State.CreateState("None");
	State.CreateState("Create");

	State.SetStartFunction("None", std::bind(&ATitleCloud::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ATitleCloud::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Create",
		std::bind(&ATitleCloud::CreateBegin, this),
		std::bind(&ATitleCloud::CreateTick, this, std::placeholders::_1),
		std::bind(&ATitleCloud::CreateExit, this));


	State.ChangeState("None");
}


void ATitleCloud::NoneBegin()
{
}

void ATitleCloud::NoneTick(float _DeltaTime)
{
}



void ATitleCloud::CreateBegin()
{
	if (0 == SpriteValue)
	{
		CloudRenderer->SetSprite("MidCloud0.png");
	}
	else
	{
		CloudRenderer->SetSprite("MidCloud1.png");
	}

	if (0 == RenderOrderValue)
	{
		CloudRenderer->SetOrder(ERenderOrder::Map);
	}
	else
	{
		CloudRenderer->SetOrder(ERenderOrder::MapCol);
	}

	SetActorLocation(CreateVector);

}

void ATitleCloud::CreateTick(float _DeltaTime)
{
	FVector CalMoveVector = FVector::Zero;
	CalMoveVector = FVector::Left * MoveSpeed * _DeltaTime;

	AddActorLocation(CalMoveVector);

	FVector CloudPosition = GetActorLocation();
	if (-1500.0f >= CloudPosition.X)
	{
		Destroy();
	}
}

void ATitleCloud::CreateExit()
{
}
