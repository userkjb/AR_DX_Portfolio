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

	WeaponRotControll(_DeltaTime);
}

void APlayerWeapon::AttackState(float _DeltaTime)
{
	//float4 x = PlayerToMouseDir;

	FVector Scale = GetActorScale3D();
	Scale.X *= -1.0f;
	SetActorScale3D(Scale);

	int a = 0;
}

void APlayerWeapon::WeaponRotControll(float _DeltaTime)
{

	SetActorRotation(WeaponRotation);
}
