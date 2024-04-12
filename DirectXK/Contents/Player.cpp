#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	PlayerRenderer->SetupAttachment(Root);
	PlayerRenderer->SetPivot(EPivot::BOT);

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

	PlayerRenderer->SetAutoSize(3.0f, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DashCountTime(_DeltaTime);
	
	{
		PlayerPos = GetActorLocation();
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();
		ScreenScale /= 2;
		MouseCenter = CulMousPos - ScreenScale;
		MouseCenter.Y *= -1.0f;
		float4 Leng = MouseCenter - PlayerPos;
		PlayerToMouseDir = Leng.Normalize3DReturn();

#ifdef _DEBUG
		std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
		std::string Msg2 = std::format("Player Pos : {}\n", PlayerPos.ToString());
		std::string Msg3 = std::format("Mouses Pos : {}\n", CulMousPos.ToString());
		std::string Msg4 = std::format("Leng : {}\n", Leng.ToString());
		std::string Msg5 = std::format("PlayerToMouseDir : {}\n", PlayerToMouseDir.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg1);
		UEngineDebugMsgWindow::PushMsg(Msg2);
		UEngineDebugMsgWindow::PushMsg(Msg3);
		UEngineDebugMsgWindow::PushMsg(Msg4);
		UEngineDebugMsgWindow::PushMsg(Msg5);
#endif
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