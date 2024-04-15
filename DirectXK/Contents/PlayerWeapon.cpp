#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>

// 기본적으로 위.
// 공격하면 아래. 위. 아래 를 반복한다.
// 위에 있을 때는 플레이어 뒤로 가며,
// 아래 있을 때는 플레이어 앞으로 온다.

APlayerWeapon::APlayerWeapon()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponRootRenderer");

	
	Weapon_One_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_One_Renderer->SetupAttachment(Root);
	Weapon_One_Renderer->SetActive(true);

	Weapon_Two_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_Two_Renderer->SetupAttachment(Root);
	Weapon_Two_Renderer->SetActive(false);

	SetRoot(Root);

	InputOn();
}

APlayerWeapon::~APlayerWeapon()
{
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	Weapon_One_Renderer->SetSprite("BasicShortSword.png");
	Weapon_One_Renderer->SetAutoSize(1.0f, true);
	Weapon_One_Renderer->SetOrder(ERenderOrder::Map);
}

void APlayerWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == IsDown(VK_LBUTTON))
	if (true == IsDown('Z'))
	{
		AttackState(_DeltaTime);
	}

	//AddActorRotation(PlayerToMouseDir);
	if (true == IsPress('R'))
	{
		//FVector Rot = FVector::Zero;
		//PlayerToMouseDir.Z
		////Rot.Z = PlayerToMouseDir.
		//AddActorRotation(Rot);
	}
}

void APlayerWeapon::AttackState(float _DeltaTime)
{
	float4 x = PlayerToMouseDir;

	int a = 0;
}
