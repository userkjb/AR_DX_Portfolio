#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>

// 기본적으로 위.
// 공격하면 아래. 위. 아래 를 반복한다.
// 위에 있을 때는 플레이어 뒤로 가며,
// 아래 있을 때는 플레이어 앞으로 온다.

APlayerWeapon::APlayerWeapon()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponRootRenderer");

	
	Weapon_One_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_One_Renderer->SetPivot(EPivot::BOT);
	Weapon_One_Renderer->SetupAttachment(Root);
	Weapon_One_Renderer->SetActive(true);

	//Weapon_Two_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	//Weapon_Two_Renderer->SetupAttachment(Root);
	//Weapon_Two_Renderer->SetActive(false);

	//Weapon_Effect = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	//Weapon_Effect->SetupAttachment(Root);
	//Weapon_Effect->SetActive(false);

	SetRoot(Root);

	InputOn();
}

APlayerWeapon::~APlayerWeapon()
{
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Create Animation
	{
		Weapon_One_Renderer->CreateAnimation("Weapon_Idle", "GreatSword", { 0.125f }, {5, 6}, true);
		Weapon_One_Renderer->CreateAnimation("Weapon_Attack", "GreatSword", { 0.125f }, { 6, 7, 8, 9 }, false);


		Weapon_One_Renderer->ChangeAnimation("Weapon_Idle");
	}

	{
		State.CreateState("Weapon_Idle");

		State.SetFunction("Weapon_Idle",
			std::bind(&APlayerWeapon::IdleBegin, this),
			std::bind(&APlayerWeapon::IdleTick, this, std::placeholders::_1),
			std::bind(&APlayerWeapon::IdleEnd, this));

		State.ChangeState("Weapon_Idle");
	}


	Weapon_One_Renderer->SetScale({ 1.0f, 1.0f, 1.0f });
	//Weapon_One_Renderer->SetAutoSize(1.0f, true);
	Weapon_One_Renderer->SetOrder(ERenderOrder::Weapon_Prev);	
	//Weapon_One_Renderer->SetSprite("BasicShortSword.png");
}

void APlayerWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

#ifdef _DEBUG
	FVector Scale = GetActorScale3D();

	std::string Msg1 = std::format("Scale : {}\n", Scale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg1);
#endif
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
	Weapon_One_Renderer->ChangeAnimation("Weapon_Idle");
}

void APlayerWeapon::IdleTick(float _DeltaTime)
{
	int a = 0;
}

void APlayerWeapon::IdleEnd()
{
	int a = 0;
}
