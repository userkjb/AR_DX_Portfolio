#include "PreCompile.h"
#include "DemonicBlade.h"
#include <EngineCore/DefaultSceneComponent.h>

ADemonicBlade::ADemonicBlade()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	DemonicBladeRenderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	DemonicBladeRenderer->SetupAttachment(Root);
}

ADemonicBlade::~ADemonicBlade()
{
}

void ADemonicBlade::BeginPlay()
{
	Super::BeginPlay();

	InitState();
}

void ADemonicBlade::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ADemonicBlade::InitState()
{
	State.CreateState("Create"); // 생성 및 이동
	State.CreateState("Disappear"); // 소멸

	State.SetFunction("Create",
		std::bind(&ADemonicBlade::CreateBegin, this),
		std::bind(&ADemonicBlade::CreateTick, this, std::placeholders::_1),
		std::bind(&ADemonicBlade::CreateExit, this));

	State.SetFunction("Disappear",
		std::bind(&ADemonicBlade::DisappearBegin, this),
		std::bind(&ADemonicBlade::DisappearTick, this, std::placeholders::_1),
		std::bind(&ADemonicBlade::DisappearExit, this));


	State.ChangeState("Create");
}

void ADemonicBlade::CreateAnimation()
{
}


void ADemonicBlade::CreateBegin()
{
}

void ADemonicBlade::CreateTick(float _DeltaTime)
{
}

void ADemonicBlade::CreateExit()
{
}

void ADemonicBlade::DisappearBegin()
{
}

void ADemonicBlade::DisappearTick(float _DeltaTime)
{
}

void ADemonicBlade::DisappearExit()
{
}
