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
	Weapon_Renderer->SetDir(EEngineDir::Right);

	Weapon_FX = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_FX->SetPivot(EPivot::BOT);
	Weapon_FX->SetOrder(ERenderOrder::Weapon_FX);
	Weapon_FX->SetupAttachment(Root);
	Weapon_FX->SetDir(EEngineDir::Right);
	Weapon_FX->SetActive(false);

	SetRoot(Root);

	InputOn();
}

APlayerWeapon::~APlayerWeapon()
{
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	{
		Weapon_Renderer->CreateAnimation("W_Idle", "GreatSword_Idle", 0.125f);
		Weapon_Renderer->CreateAnimation("W_FX", "GreatSword_FX", 0.125f);
		Weapon_Renderer->CreateAnimation("W_Swing", "GreatSword", 0.125f, false);

		Weapon_Renderer->ChangeAnimation("W_Idle");
	}
	{
		Weapon_FX->CreateAnimation("G_S_Idle", "GreatSword_FX", 0.125f, false, 2, 2);
		Weapon_FX->CreateAnimation("G_S_Attack", "GreatSword_FX", 0.125f, false, 0, 2);
		Weapon_FX->ChangeAnimation("G_S_Idle");
	}

	{
		State.CreateState("Weapon_Idle");
		State.CreateState("Weapon_Swing");

		State.SetFunction("Weapon_Idle",
			std::bind(&APlayerWeapon::IdleBegin, this),
			std::bind(&APlayerWeapon::IdleTick, this, std::placeholders::_1),
			std::bind(&APlayerWeapon::IdleEnd, this));
		State.SetFunction("Weapon_Swing",
			std::bind(&APlayerWeapon::SwingBegin, this),
			std::bind(&APlayerWeapon::SwingTick, this, std::placeholders::_1),
			std::bind(&APlayerWeapon::SwingEnd, this));


		State.ChangeState("Weapon_Idle");
	}

	Weapon_Renderer->SetAutoSize(2.0f, true);
	Weapon_FX->SetAutoSize(2.0f, true);
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

	WeaponRotControll(_DeltaTime);

#ifdef _DEBUG
	t_DebugFunction(_DeltaTime);
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

void APlayerWeapon::WeaponRotControll(float _DeltaTime)
{
	//FVector CalRotation = FVector::Zero;
	//CalRotation.Z = �⺻ ���� + ���ϴ� ����.
	FVector CurRotation = FVector::Zero;
	if (b_Attack == false)
	{
		CurRotation.Z = 90.0f;
	}
	else
	{
		CurRotation.Z = -90.0f;
	}

	if (PlayerDir == EEngineDir::Left)
	{
		Weapon_Renderer->SetDir(EEngineDir::Left);
	}
	else if (PlayerDir == EEngineDir::Right)
	{
		Weapon_Renderer->SetDir(EEngineDir::Right);
	}

	FVector F_Vector = CurRotation + WeaponRotation;
	Weapon_Renderer->SetRotationDeg(F_Vector);
	//SetActorRotation(F_Vector);
}


#pragma region Idle
void APlayerWeapon::IdleBegin()
{
	Weapon_Renderer->ChangeAnimation("W_Idle");
}

void APlayerWeapon::IdleTick(float _DeltaTime)
{
	if (true == IsDown(VK_LBUTTON))
	{
		State.ChangeState("Weapon_Swing");
		return;
	}
}

void APlayerWeapon::IdleEnd()
{
	
}
#pragma endregion

#pragma region Weapon_Swing
void APlayerWeapon::SwingBegin()
{
	Weapon_Renderer->ChangeAnimation("W_Swing");
	if (false == b_Attack)
	{
		//Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Prev);
	}
	else
	{
		//Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Next);
	}
	Weapon_FX->SetActive(true);
	Weapon_FX->ChangeAnimation("G_S_Attack");
	Weapon_FX->SetRotationDeg(WeaponRotation);
}

void APlayerWeapon::SwingTick(float _DeltaTime)
{
	if (true == Weapon_FX->IsCurAnimationEnd())
	{
		Weapon_FX->ChangeAnimation("G_S_Idle");
		Weapon_FX->SetActive(false);
	}
	if (true == Weapon_Renderer->IsCurAnimationEnd())
	{
		Weapon_FX->ChangeAnimation("G_S_Idle");
		Weapon_FX->SetActive(false);
		State.ChangeState("Weapon_Idle");
		return;
	}
}

void APlayerWeapon::SwingEnd()
{
	if (false == b_Attack)
	{
		b_Attack = true;
	}
	else
	{
		b_Attack = false;
	}
}
#pragma endregion


void APlayerWeapon::t_DebugFunction(float _DeltaTime)
{
	FVector Scale = GetActorScale3D();
	FVector LocalRenderScale = Weapon_Renderer->GetLocalScale();
	FVector WorldRenderScale = Weapon_Renderer->GetWorldScale();


	std::string s_PlayerDir = "";
	if (PlayerDir == EEngineDir::Left)
	{
		s_PlayerDir = "Left";
	}
	else if (PlayerDir == EEngineDir::Right)
	{
		s_PlayerDir = "Right";
	}

	std::string Msg1 = std::format("Weapon Actor Scale : {}\n", Scale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg1);

	std::string Msg2 = std::format("Weapon L_Render Scale : {}\n", LocalRenderScale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg2);
	std::string Msg3 = std::format("Weapon W_Render Scale : {}\n", WorldRenderScale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg3);

	std::string Msg4 = std::format("Weapon PlayerDir: {}\n", s_PlayerDir);
	UEngineDebugMsgWindow::PushMsg(Msg4);
}