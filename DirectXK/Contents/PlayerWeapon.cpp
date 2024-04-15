#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>

// �⺻������ ��.
// �����ϸ� �Ʒ�. ��. �Ʒ� �� �ݺ��Ѵ�.
// ���� ���� ���� �÷��̾� �ڷ� ����,
// �Ʒ� ���� ���� �÷��̾� ������ �´�.

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
}

void APlayerWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_LBUTTON))
	{
		AttackState(_DeltaTime);
	}
}

void APlayerWeapon::AttackState(float _DeltaTime)
{
	float4 x = PlayerToMouseDir;

	int a = 0;
}
