#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerWeapon.h"
#include <math.h>
#include "PlayerStruct.h"
#include "MyWidget.h"
#include <EngineCore/Image.h>

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	PlayerRenderer->SetPivot(EPivot::BOT);
	PlayerRenderer->SetupAttachment(Root);

	PlayerCollision = CreateDefaultSubObject<UCollision>("Collision");
	PlayerCollision->SetupAttachment(Root);
	PlayerCollision->SetScale(FVector(64.0f, 64.0f));
	PlayerCollision->AddPosition(FVector(0.0f, 32.0f));
	// �ݸ����� ������ ������ ��������� �Ѵ�.
	PlayerCollision->SetCollisionGroup(ECollisionOrder::Player);
	PlayerCollision->SetCollisionType(ECollisionType::RotRect);

	MouseRendere = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MouseRendere->SetupAttachment(Root);

	SetRoot(Root);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Widget = CreateWidget<MyWidget>(GetWorld(), "UIBase");
	CreateAnimation();
	StateInit();

	float Size = UContentsConstValue::AutoSizeValue; // const
	PlayerRenderer->SetAutoSize(Size, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);

	Weapone = GetWorld()->SpawnActor<APlayerWeapon>("Weapon", EObjectOrder::Player);

	MouseRendere->SetSprite("ShootingCursor2.png");
	MouseRendere->SetAutoSize(Size, true);
	MouseRendere->SetOrder(ERenderOrder::Mouse);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DashCountTime(_DeltaTime);
	CollisionCheck(_DeltaTime);
	if (false == IsCollision)
	{
		CollisionOff(_DeltaTime);
	}

	{
		PlayerPos = GetActorLocation();
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);

		FVector ScreenScale = GEngine->EngineWindow.GetWindowScale();
		
		float4 Leng = MousePosWorld - PlayerPos;
		PlayerToMouseDir = Leng.Normalize2DReturn(); // �÷��̾� ���� ���콺 ����.

		float Rot = atan2((MousePosWorld.Y - PlayerPos.Y), (MousePosWorld.X - PlayerPos.X));
		Rot *= UEngineMath::RToD;
		WeaponDir.Z = Rot;

		
	}
	
	// Ŀ��
	{
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);
		MousePosWorld.Z = 1.0f;

		FVector MousePosition = MousePosWorld - PlayerPos;

		MouseRendere->SetPosition(MousePosition);
	}

#ifdef _DEBUG
		t_DeBugFunction(_DeltaTime);
#endif

	{
		// ���� ��ġ = �÷��̾� ��ġ // �̰� ���⼭ ���ִ� ���� �´�.
		Weapone->AActor::SetActorLocation(PlayerPos);
		Weapone->SetPlayerToMouseDir(PlayerToMouseDir);
		Weapone->SetWeaponRotation(WeaponDir); // ���⿡ ȸ�� ���� �Ѱ���.
		Weapone->SetPlayerDir(ActorDir);
	}
}

void APlayer::CreateAnimation()
{
	PlayerRenderer->CreateAnimation("Idle", "Idle", 0.125f);
	PlayerRenderer->CreateAnimation("Run", "Run", 0.125f);
	PlayerRenderer->CreateAnimation("Jump", "Jump", 0.125f);
	PlayerRenderer->CreateAnimation("Die", "Die", 0.125f);

	PlayerRenderer->ChangeAnimation("Idle");
}

void APlayer::DashCountTime(float _DeltaTime)
{
	int DashCountIndex = EPlayerStateValue::DashCount;
	if (EPlayerStateValue::DashCount != EPlayerStateValue::DashCountMax)
	{
		DashCreationTime += _DeltaTime;
		Widget->GetDashBaseImageV()[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (DashCreationTime >= EPlayerStateValue::DashCountUpTime)
	{
		Widget->GetDashBaseImageV()[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));
		EPlayerStateValue::DashCount++;
		DashCreationTime = 0.0f;
	}
	else if (DashCreationTime >= EPlayerStateValue::DashCountUpTime / 2.0f)
	{
		Widget->GetDashBaseImageV()[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

void APlayer::DashSpectrumCalPos(float _DeltaTime)
{
	DashSpectrumPosSaveTime += _DeltaTime;

	if (State.GetCurStateName() == "Dash")
	{
		int a = 0; // Ÿ�� �� Ȯ��.
	}
}

void APlayer::LevelIsDestroy()
{
	Weapone->Destroy();
}