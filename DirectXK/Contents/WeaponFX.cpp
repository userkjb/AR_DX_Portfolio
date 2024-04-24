#include "PreCompile.h"
#include "WeaponFX.h"
#include <EngineCore/DefaultSceneComponent.h>

AWeaponFX::AWeaponFX()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponFXRenderer");

	Weapon_FX_Render = CreateDefaultSubObject<USpriteRenderer>("WeaponFXRenderer");
	Weapon_FX_Render->SetPivot(EPivot::BOT);
	Weapon_FX_Render->SetOrder(ERenderOrder::Weapon_FX);
	Weapon_FX_Render->SetupAttachment(Root);
	Weapon_FX_Render->SetDir(EEngineDir::Right);
	Weapon_FX_Render->SetActive(false);

	Weapon_FX_Collision = CreateDefaultSubObject<UCollision>("WeaponFXCollision");
	Weapon_FX_Collision->SetupAttachment(Root);
	//Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	// 콜리전은 무조건 오더를 지정해줘야 한다.
	Weapon_FX_Collision->SetCollisionGroup(ECollisionOrder::WeaponFX);
	Weapon_FX_Collision->SetCollisionType(ECollisionType::RotRect);

	SetRoot(Root);
}

AWeaponFX::~AWeaponFX()
{
}

void AWeaponFX::BeginPlay()
{
	Super::BeginPlay();

	{
		Weapon_FX_Render->CreateAnimation("G_S_Idle", "GreatSword_FX", 0.125f, false, 2, 2);
		Weapon_FX_Render->CreateAnimation("G_S_Attack", "GreatSword_FX", 0.125f, false, 0, 2);
		
		Weapon_FX_Render->ChangeAnimation("G_S_Attack");
	}

	Weapon_FX_Render->SetAutoSize(2.0f, true);
	Weapon_FX_Collision->SetScale(FVector(10.0f, 10.0f, 10.0f));
}

void AWeaponFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
