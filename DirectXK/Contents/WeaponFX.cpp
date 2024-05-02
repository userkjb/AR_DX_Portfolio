#include "PreCompile.h"
#include "WeaponFX.h"
#include <EngineCore/DefaultSceneComponent.h>

AWeaponFX::AWeaponFX()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponFXRenderer");
	SetRoot(Root);

	Weapon_FX_Render = CreateDefaultSubObject<USpriteRenderer>("WeaponFXRenderer");
	Weapon_FX_Render->SetPivot(EPivot::BOT);
	Weapon_FX_Render->SetOrder(ERenderOrder::Weapon_FX);
	Weapon_FX_Render->SetupAttachment(Root);
	Weapon_FX_Render->SetDir(EEngineDir::Right);
	Weapon_FX_Render->SetActive(false);

	Weapon_FX_Collision = CreateDefaultSubObject<UCollision>("WeaponFXCollision");
	Weapon_FX_Collision->SetupAttachment(Root);
	//Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	Weapon_FX_Collision->SetCollisionGroup(ECollisionOrder::WeaponFX);
	Weapon_FX_Collision->SetCollisionType(ECollisionType::RotRect);
	Weapon_FX_Collision->SetActive(false);
}

AWeaponFX::~AWeaponFX()
{
}

void AWeaponFX::BeginPlay()
{
	Super::BeginPlay();
	
	StateInit();
	CreateAnimation();

	Weapon_FX_Render->SetAutoSize(2.0f, true);
	Weapon_FX_Collision->SetScale(FVector(10.0f, 10.0f, 10.0f));
}

void AWeaponFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
}

void AWeaponFX::StateInit()
{
	State.CreateState("None");
	State.CreateState("Swing");

	State.SetFunction("Swing",
		std::bind(&AWeaponFX::SwingBegin, this),
		std::bind(&AWeaponFX::SwingTick, this, std::placeholders::_1),
		std::bind(&AWeaponFX::SwingExit, this));

	State.ChangeState("None");
}

void AWeaponFX::CreateAnimation()
{
	//Weapon_FX_Render->CreateAnimation("G_S_Idle", "GreatSword_FX", 0.125f, false, 2, 2);
	Weapon_FX_Render->CreateAnimation("G_S_Attack", "GreatSword_FX", 0.125f, false, 0, 2);

	Weapon_FX_Render->ChangeAnimation("G_S_Attack");
}




void AWeaponFX::SwingBegin()
{
	Weapon_FX_Render->ChangeAnimation("G_S_Attack");
	Weapon_FX_Render->SetPosition(InPosition);
	Weapon_FX_Render->SetRotationDeg(InRotation);
	Weapon_FX_Collision->SetScale(InScale);
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

void AWeaponFX::SwingTick(float _DeltaTime)
{
	if (true == Weapon_FX_Render->IsCurAnimationEnd())
	{
		Weapon_FX_Render->SetActive(false);
		Weapon_FX_Collision->SetActive(false);
		Destroy();
	}
}

void AWeaponFX::SwingExit()
{
	
}
