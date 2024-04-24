#include "PreCompile.h"
#include "WeaponFX.h"
#include <EngineCore/DefaultSceneComponent.h>

AWeaponFX::AWeaponFX()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponFXRenderer");

	Weapon_FX = CreateDefaultSubObject<USpriteRenderer>("WeaponFXRenderer");
	Weapon_FX->SetPivot(EPivot::BOT);
	Weapon_FX->SetOrder(ERenderOrder::Weapon_FX);
	Weapon_FX->SetupAttachment(Root);
	Weapon_FX->SetDir(EEngineDir::Right);
	Weapon_FX->SetActive(false);

	Collision = CreateDefaultSubObject<UCollision>("WeaponFXCollision");
	Collision->SetupAttachment(Root);
	//Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	// 콜리전은 무조건 오더를 지정해줘야 한다.
	Collision->SetCollisionGroup(ECollisionOrder::WeaponFX);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

AWeaponFX::~AWeaponFX()
{
}

void AWeaponFX::BeginPlay()
{
	Super::BeginPlay();

	{
		Weapon_FX->CreateAnimation("G_S_Idle", "GreatSword_FX", 0.125f, false, 2, 2);
		Weapon_FX->CreateAnimation("G_S_Attack", "GreatSword_FX", 0.125f, false, 0, 2);
		
		Weapon_FX->ChangeAnimation("G_S_Idle");
	}

	Weapon_FX->SetAutoSize(2.0f, true);
}

void AWeaponFX::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
