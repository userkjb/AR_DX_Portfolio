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
	State.CreateState("Setting");
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
}

void ATitleCloud::CreateTick(float _DeltaTime)
{
}

void ATitleCloud::CreateExit()
{
}
