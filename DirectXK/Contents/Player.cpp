#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerWeapon.h"
#include <math.h>

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	PlayerRenderer->SetPivot(EPivot::BOT);
	PlayerRenderer->SetupAttachment(Root);

	TestRenderer_1 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	TestRenderer_1->SetPivot(EPivot::BOT);
	TestRenderer_1->SetupAttachment(Root);

	TestRenderer_2 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	TestRenderer_2->SetPivot(EPivot::BOT);
	TestRenderer_2->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	// �ݸ����� ������ ������ ��������� �Ѵ�.
	Collision->SetCollisionGroup(ECollisionOrder::Player);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	StateInit();

	float Size = UContentsConstValue::AutoSizeValue; // const
	PlayerRenderer->SetAutoSize(Size, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);

	TestRenderer_1->SetAutoSize(Size, true);
	TestRenderer_1->SetOrder(ERenderOrder::Player);
	TestRenderer_1->SetSprite("TestPointImage.png");
	TestRenderer_1->SetActive(false);
	TestRenderer_2->SetAutoSize(Size, true);
	TestRenderer_2->SetOrder(ERenderOrder::Player);
	TestRenderer_2->SetSprite("TestPointImage.png");
	TestRenderer_2->SetActive(false);

	Weapone = GetWorld()->SpawnActor<APlayerWeapon>("Weapon");
	//Weapone->Weapon_Renderer->SetDir(EEngineDir::Right);
	//std::shared_ptr<APlayerWeapon> Weapone = GetWorld()->SpawnActor<APlayerWeapon>("Weapon");
	//Weapone->SetActorScale3D({2.0f, 2.0f, 2.0f});
	Weapone->SetPlayerActor(shared_from_this());

}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DashCountTime(_DeltaTime);
	DashSpectrumCalPos(_DeltaTime);

	//PixelCheck(_DeltaTime);

	{
		PlayerPos = GetActorLocation();
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);

		FVector ScreenScale = GEngine->EngineWindow.GetWindowScale();
		
		float4 Leng = MousePosWorld - PlayerPos;
		PlayerToMouseDir = Leng.Normalize3DReturn();

		float Rot = atan2((MousePosWorld.Y - PlayerPos.Y), (MousePosWorld.X - PlayerPos.X));
		Rot *= UEngineMath::RToD;
		WeaponDir.Z = Rot;
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
	if (DashCount != DashCountMax)
	{
		DashCreationTime += _DeltaTime;
	}

	if (DashCreationTime >= DashCountUp)
	{
		DashCount++;
		DashCreationTime = 0.0f;
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

