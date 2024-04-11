#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

APlayer::APlayer()
{
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
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

	PlayerRenderer->SetAutoSize(5.0f, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	PlayerPos = GetActorLocation();
	DashCountTime(_DeltaTime);

	float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
	float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();
	ScreenScale /= 2;
	MouseCenter = CulMousPos - ScreenScale;
	MouseCenter.Y *= -1.0f;
	float4 Leng = MouseCenter - PlayerPos;
	PlayerToMouseDir = Leng.Normalize3DReturn();
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