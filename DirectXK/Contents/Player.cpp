#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "PlayerWeapon.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	PlayerRenderer->SetPivot(EPivot::BOT);
	PlayerRenderer->SetupAttachment(Root);

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

	PlayerRenderer->SetAutoSize(1.0f, true);
	PlayerRenderer->SetOrder(ERenderOrder::Player);

	Weapone = GetWorld()->SpawnActor<APlayerWeapon>("Weapon");
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DashCountTime(_DeltaTime);

	PixelCheck(_DeltaTime);

	{
		// Actor ¿Í Component À§Ä¡
		FVector MainActorPos = GetActorLocation();
		FVector LocalActorPos = PlayerRenderer->GetLocalPosition();
		FVector WorldActorPos = PlayerRenderer->GetWorldPosition();

		std::string Msg1 = std::format("Main  Pos : {}\n", MainActorPos.ToString());
		std::string Msg2 = std::format("Local Pos : {}\n", LocalActorPos.ToString());
		std::string Msg3 = std::format("World Pos : {}\n", WorldActorPos.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg1);
		UEngineDebugMsgWindow::PushMsg(Msg2);
		UEngineDebugMsgWindow::PushMsg(Msg3);
	}
	
	{
		PlayerPos = GetActorLocation();
		//PlayerPos = PlayerRenderer->GetWorldPosition();
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		CulMousPos.Y *= -1.0f;
		//float4 ScreenScale = GEngine->EngineWindow.GetWindowScale().Half2D();
		//ScreenScale.Z = 0.0f;

		//MouseCenter = CulMousPos - ScreenScale;
		//MouseCenter.Y *= -1.0f;
		
		float4 Leng = PlayerPos - CulMousPos;
		PlayerToMouseDir = Leng.Normalize3DReturn();
		PlayerToMouseDir.X *= -1.0f;
		PlayerToMouseDir.Y *= -1.0f;

#ifdef _DEBUG
		//std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
		//std::string Msg2 = std::format("Player Pos : {}\n", PlayerPos.ToString());
		//std::string Msg3 = std::format("Mouses Pos : {}\n", CulMousPos.ToString());
		//std::string Msg4 = std::format("Leng : {}\n", Leng.ToString());
		std::string Msg5 = std::format("PlayerToMouseDir : {}\n", PlayerToMouseDir.ToString());
		std::string Msg6 = std::format("CalVectors : {}\n", CalVectors.ToString());

		//UEngineDebugMsgWindow::PushMsg(Msg1);
		//UEngineDebugMsgWindow::PushMsg(Msg2);
		//UEngineDebugMsgWindow::PushMsg(Msg3);
		//UEngineDebugMsgWindow::PushMsg(Msg4);
		UEngineDebugMsgWindow::PushMsg(Msg5);
		UEngineDebugMsgWindow::PushMsg(Msg6);
#endif
	}

	{
		Weapone->SetPlayerToMouseDir(PlayerToMouseDir);
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

#ifdef _DEBUG
	std::string Msg1 = std::format("DashCount : {}\n", DashCount);

	UEngineDebugMsgWindow::PushMsg(Msg1);
#endif
}