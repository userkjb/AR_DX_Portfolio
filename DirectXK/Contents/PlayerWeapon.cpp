#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"

// �⺻������ ��.
// �����ϸ� �Ʒ�. ��. �Ʒ� �� �ݺ��Ѵ�.
// ���� ���� ���� �÷��̾� �ڷ� ����,
// �Ʒ� ���� ���� �÷��̾� ������ �´�.

APlayerWeapon::APlayerWeapon()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponRootRenderer");

	
	Weapon_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_Renderer->SetPivot(EPivot::BOT);
	Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Next);
	Weapon_Renderer->SetupAttachment(Root);
	

	SetRoot(Root);

	InputOn();
}

APlayerWeapon::~APlayerWeapon()
{
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	Weapon_Renderer->CreateAnimation("W_Idle", "GreatSword", 0.125f);

	Weapon_Renderer->ChangeAnimation("W_Idle");

	{
		State.CreateState("Weapon_Idle");

		State.SetFunction("Weapon_Idle",
			std::bind(&APlayerWeapon::IdleBegin, this),
			std::bind(&APlayerWeapon::IdleTick, this, std::placeholders::_1),
			std::bind(&APlayerWeapon::IdleEnd, this));

		State.ChangeState("Weapon_Idle");
	}

	Weapon_Renderer->SetAutoSize(2.0f, true);
	//Weapon_One_Renderer->SetScale({ 1.0f, 1.0f, 1.0f });
	//Weapon_One_Renderer->SetAutoSize(1.0f, true);
	//Weapon_One_Renderer->SetOrder(ERenderOrder::Weapon_Prev);
	//Weapon_One_Renderer->SetSprite("BasicShortSword.png");
}

void APlayerWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	GetPlayerToMouseDir();


	//if (true == IsDown(VK_LBUTTON))
	if (true == IsDown('Z'))
	{
		AttackState(_DeltaTime);
	}



	WeaponRotControll(_DeltaTime);

#ifdef _DEBUG
	FVector Scale = GetActorScale3D();

	std::string Msg1 = std::format("Scale : {}\n", Scale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg1);
#endif	
}

void APlayerWeapon::GetPlayerToMouseDir()
{
	if (nullptr == PlayerActor)
	{
		MsgBoxAssert("Player Actor �� �����ϴ�.");
		return;
	}

	PlayerToMouseDir = PlayerActor->GetPlayerToMouseDir();
}

void APlayerWeapon::AttackState(float _DeltaTime)
{
	//float4 x = PlayerToMouseDir;

	FVector Scale = GetActorScale3D();
	Scale.X *= -1.0f;
	Scale.Y *= -1.0f;
	SetActorScale3D(Scale);

	int a = 0;
}

void APlayerWeapon::WeaponRotControll(float _DeltaTime)
{
	SetActorRotation(WeaponRotation);
}



void APlayerWeapon::IdleBegin()
{
	Weapon_Renderer->ChangeAnimation("W_Idle");
}

void APlayerWeapon::IdleTick(float _DeltaTime)
{
	int a = 0;
}

void APlayerWeapon::IdleEnd()
{
	int a = 0;
}
