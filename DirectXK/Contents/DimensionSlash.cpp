#include "PreCompile.h"
#include "DimensionSlash.h"
#include <EngineCore/DefaultSceneComponent.h>

ADimensionSlash::ADimensionSlash()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	DimensionSlashRenderer_B = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	DimensionSlashRenderer_B->SetupAttachment(Root);
	DimensionSlashRenderer_B->SetOrder(ERenderOrder::BossSkill_B);
	DimensionSlashRenderer_B->SetActive(false);

	DimensionSlashRenderer_F = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	DimensionSlashRenderer_F->SetupAttachment(Root);
	DimensionSlashRenderer_F->SetOrder(ERenderOrder::BossSkill_F);
	DimensionSlashRenderer_F->SetActive(false);
}

ADimensionSlash::~ADimensionSlash()
{
}

void ADimensionSlash::BeginPlay()
{
	DimensionSlashRenderer_B->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	DimensionSlashRenderer_F->SetAutoSize(UContentsConstValue::AutoSizeValue, true);

	CreateAnimation();
	InitState();
}

void ADimensionSlash::Tick(float _DeltaTime)
{
	State.Update(_DeltaTime);
}

void ADimensionSlash::InitState()
{
	State.CreateState("Create");
	//State.CreateState("Attack");
	//State.CreateState("Disppear");

	State.SetFunction("Create",
		std::bind(&ADimensionSlash::CreateBegin, this),
		std::bind(&ADimensionSlash::CreateTick, this, std::placeholders::_1),
		std::bind(&ADimensionSlash::CreateExit, this));





	State.ChangeState("Create");
}

void ADimensionSlash::CreateAnimation()
{
	DimensionSlashRenderer_B->CreateAnimation("DimensionSlashBack", "DimensionSlashBack.png", 0.125f, false);


	DimensionSlashRenderer_F->CreateAnimation("DimensionSlashFront", "DimensionSlashFront.png", 0.125f, false);


	DimensionSlashRenderer_B->ChangeAnimation("DimensionSlashBack");
	DimensionSlashRenderer_F->ChangeAnimation("DimensionSlashFront");
}



void ADimensionSlash::CreateBegin()
{
	DimensionSlashRenderer_B->SetActive(true);
	DimensionSlashRenderer_F->SetActive(true);

	DimensionSlashRenderer_B->ChangeAnimation("DimensionSlashBack");
	DimensionSlashRenderer_F->ChangeAnimation("DimensionSlashFront");
}

void ADimensionSlash::CreateTick(float _DeltaTime)
{
	int a = 0;
	DimensionSlashRenderer_B->SetFrameCallback("DimensionSlashBack", 4, std::bind(&ADimensionSlash::FrameCallBack, this));
}

void ADimensionSlash::CreateExit()
{
	//Destroy();
}

void ADimensionSlash::FrameCallBack()
{
	int a = 0;
}



