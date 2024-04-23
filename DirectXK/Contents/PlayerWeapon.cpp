#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"

// 기본적으로 위.
// 공격하면 아래. 위. 아래 를 반복한다.
// 위에 있을 때는 플레이어 뒤로 가며,
// 아래 있을 때는 플레이어 앞으로 온다.

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
		MsgBoxAssert("Player Actor 가 없습니다.");
		return;
	}

	PlayerToMouseDir = PlayerActor->GetPlayerToMouseDir();
}

void APlayerWeapon::WeaponRotControll(float _DeltaTime)
{
	//FVector CalRotation = FVector::Zero;
	//CalRotation.Z = 기본 각도 + 변하는 각도.
	FVector CurRotation = FVector::Zero;
	if (b_WeaponUpDownDir == false)
	{
		CurRotation.Z = 90.0f;
	}
	else
	{
		CurRotation.Z = -90.0f;
	}

	FVector CurPosition = FVector::Zero;
	if (PlayerDir == EEngineDir::Right)
	{
		CurPosition.X = 50.0f;
		Weapon_Renderer->SetPosition(CurPosition);
		Weapon_Renderer->SetDir(EEngineDir::Right);
	}
	else if (PlayerDir == EEngineDir::Left)
	{
		CurPosition.X = -50.0f;
		Weapon_Renderer->SetPosition(CurPosition);
		Weapon_Renderer->SetDir(EEngineDir::Left);
	}

	FVector F_Vector = CurRotation + WeaponRotation;
	Weapon_Renderer->SetRotationDeg(F_Vector);
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
	
	Weapon_FX->SetActive(true);
	// 이펙트는 그 자리에 남아 있어야 함.
	Weapon_FX->SetPosition(Weapon_Renderer->GetLocalPosition() * 1.5f);
	Weapon_FX->ChangeAnimation("G_S_Attack");

	FVector RotationValue_FX = FVector::Zero;
	if (EEngineDir::Right == Weapon_Renderer->GetDir())
	{
		RotationValue_FX.Z = -90.0f;
		Weapon_FX->SetRotationDeg(WeaponRotation + RotationValue_FX);
	}
	else if (EEngineDir::Left == Weapon_Renderer->GetDir())
	{
		RotationValue_FX.Z = -90.0f;
		Weapon_FX->SetRotationDeg(WeaponRotation + RotationValue_FX);
	}
	
	if (false == b_WeaponUpDownDir)
	{
		Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Prev);
	}
	else
	{
		Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Next);
	}
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
	if (false == b_WeaponUpDownDir)
	{
		b_WeaponUpDownDir = true;
	}
	else
	{
		b_WeaponUpDownDir = false;
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

	/*std::string Msg1 = std::format("Weapon Actor Scale : {}\n", Scale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg1);

	std::string Msg2 = std::format("Weapon L_Render Scale : {}\n", LocalRenderScale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg2);
	std::string Msg3 = std::format("Weapon W_Render Scale : {}\n", WorldRenderScale.ToString());
	UEngineDebugMsgWindow::PushMsg(Msg3);

	std::string Msg4 = std::format("Weapon PlayerDir: {}\n", s_PlayerDir);
	UEngineDebugMsgWindow::PushMsg(Msg4);*/
}