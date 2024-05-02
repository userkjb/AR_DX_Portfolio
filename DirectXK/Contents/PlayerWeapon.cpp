#include "PreCompile.h"
#include "PlayerWeapon.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"
#include "WeaponFX.h"

// �⺻������ ��.
// �����ϸ� �Ʒ�. ��. �Ʒ� �� �ݺ��Ѵ�.
// ���� ���� ���� �÷��̾� �ڷ� ����,
// �Ʒ� ���� ���� �÷��̾� ������ �´�.

APlayerWeapon::APlayerWeapon()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("WeaponRootRenderer");
	SetRoot(Root);

	Weapon_Renderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRootRenderer");
	Weapon_Renderer->SetupAttachment(Root);
	Weapon_Renderer->SetPivot(EPivot::BOT);
	Weapon_Renderer->SetOrder(ERenderOrder::Weapon_Next);
	Weapon_Renderer->SetDir(EEngineDir::Right);

	InputOn();
}

APlayerWeapon::~APlayerWeapon()
{
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	CreateAnimation();
	StateInit();


	Weapon_Renderer->SetAutoSize(2.0f, true);
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

void APlayerWeapon::CreateAnimation()
{
	Weapon_Renderer->CreateAnimation("W_Idle", "GreatSword_Idle", 0.125f);
	Weapon_Renderer->CreateAnimation("W_FX", "GreatSword_FX", 0.125f);
	Weapon_Renderer->CreateAnimation("W_Swing", "GreatSword", 0.125f, false);

	Weapon_Renderer->ChangeAnimation("W_Idle");
}

void APlayerWeapon::StateInit()
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

	{
		std::shared_ptr<AWeaponFX> WeaponFXActor = GetWorld()->SpawnActor<AWeaponFX>("WeaponFX", ERenderOrder::Weapon_FX);
		WeaponFXActor->SetFXScale(FVector());
		FVector WeaponCollisionPos = FVector::Zero;
		FVector WeaponCollisionRot = WeaponRotation;
		WeaponCollisionPos = GetActorLocation();
		WeaponCollisionPos += PlayerToMouseDir * Range;
		WeaponCollisionPos.Z = 0.0f;
		WeaponCollisionPos.W = 1.0f;
		WeaponFXActor->SetCreatePosition(WeaponCollisionPos); // ���� ��ġ
		WeaponCollisionRot.Z -= 90.0f;
		WeaponFXActor->SetCreateTotation(WeaponCollisionRot); // ���� ����

		WeaponFXActor->CreateWeaponFX();
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
	if (true == Weapon_Renderer->IsCurAnimationEnd())
	{
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