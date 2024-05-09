#include "PreCompile.h"
#include "CosmosSwordFX.h"
#include <EngineCore/DefaultSceneComponent.h>


ACosmosSwordFX::ACosmosSwordFX()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	Weapon_FX_Render = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	Weapon_FX_Render->SetPivot(EPivot::BOT);
	Weapon_FX_Render->SetOrder(ERenderOrder::Weapon_FX);
	Weapon_FX_Render->SetupAttachment(Root);
	Weapon_FX_Render->SetDir(EEngineDir::Right);
	Weapon_FX_Render->SetActive(false);

	Weapon_FX_Collision = CreateDefaultSubObject<UCollision>("WeaponFXCollision");
	Weapon_FX_Collision->SetupAttachment(Root);
	Weapon_FX_Collision->SetCollisionGroup(ECollisionOrder::WeaponFX);
	Weapon_FX_Collision->SetCollisionType(ECollisionType::RotRect);
	Weapon_FX_Collision->SetActive(false);
}

ACosmosSwordFX::~ACosmosSwordFX()
{
}

void ACosmosSwordFX::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	StateInit();

	Weapon_FX_Render->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	//Weapon_FX_Collision->SetScale(FVector(10.0f, 10.0f, 10.0f));
}

void ACosmosSwordFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ACosmosSwordFX::StateInit()
{
	State.CreateState("None");
	State.CreateState("Swing");

	State.SetFunction("Swing",
		std::bind(&ACosmosSwordFX::SwingBegin, this),
		std::bind(&ACosmosSwordFX::SwingTick, this, std::placeholders::_1),
		std::bind(&ACosmosSwordFX::SwingExit, this));

	State.ChangeState("None");
}

void ACosmosSwordFX::CreateAnimation()
{
	Weapon_FX_Render->CreateAnimation("Attack", "CosmosSwingFX", 0.125f, false, 0, 2);

	Weapon_FX_Render->ChangeAnimation("Attack");
}

void ACosmosSwordFX::SwingBegin()
{
	Weapon_FX_Render->ChangeAnimation("Attack");
	Weapon_FX_Render->SetPosition(InPosition);
	Weapon_FX_Render->SetRotationDeg(InRotation);
	//Weapon_FX_Collision->SetScale(InScale);
	Weapon_FX_Collision->SetScale(FVector(240.0f, 188.0f));
	InPosition.Y += 94.0f;
	Weapon_FX_Collision->SetPosition(InPosition);
	Weapon_FX_Collision->SetRotationDeg(InRotation);

	if (false == Weapon_FX_Render->IsActive())
	{
		Weapon_FX_Render->SetActive(true);
	}
	if (false == Weapon_FX_Collision->IsActive())
	{
		Weapon_FX_Collision->SetActive(true);
	}
}

void ACosmosSwordFX::SwingTick(float _DeltaTime)
{
	if (true == Weapon_FX_Render->IsCurAnimationEnd())
	{
		Weapon_FX_Render->SetActive(false);
		Weapon_FX_Collision->SetActive(false);
		Destroy();
	}
}

void ACosmosSwordFX::SwingExit()
{
}
