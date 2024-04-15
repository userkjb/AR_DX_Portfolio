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
		PlayerPos = GetActorLocation();
		//PlayerPos = PlayerRenderer->GetWorldPosition();
		float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
		CulMousPos.Y *= -1.0f;
		//float4 ScreenScale = GEngine->EngineWindow.GetWindowScale().Half2D();
		//ScreenScale.Z = 0.0f;

		//MouseCenter = CulMousPos - ScreenScale;
		//MouseCenter.Y *= -1.0f;
		
		float4 Leng = CulMousPos - PlayerPos;
		PlayerToMouseDir = Leng.Normalize3DReturn();

		////
		// 라디안 각도.
		float Rot = atan2((CulMousPos.Y - PlayerPos.Y), (CulMousPos.X - PlayerPos.X));
		Rot *= UEngineMath::RToD; // 디그리( 0 ~ 180)
		FVector x = FVector::Zero;
		x.RotationZToDeg(Rot);
		////
#ifdef _DEBUG
		//std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
		//std::string Msg2 = std::format("Player Pos : {}\n", PlayerPos.ToString());
		//std::string Msg3 = std::format("Mouses Pos : {}\n", CulMousPos.ToString());
		//std::string Msg4 = std::format("Leng : {}\n", Leng.ToString());
		std::string Msg5 = std::format("PlayerToMouseDir : {}\n", PlayerToMouseDir.ToString());
		std::string Msg6 = std::format("Leng : {}\n", Leng.ToString());
		std::string Msg7 = std::format("Rot : {}\n", x.ToString());
		std::string Msg8 = std::format("CalVectors : {}\n", CalVectors.ToString());

		//UEngineDebugMsgWindow::PushMsg(Msg1);
		//UEngineDebugMsgWindow::PushMsg(Msg2);
		//UEngineDebugMsgWindow::PushMsg(Msg3);
		//UEngineDebugMsgWindow::PushMsg(Msg4);
		UEngineDebugMsgWindow::PushMsg(Msg5);
		UEngineDebugMsgWindow::PushMsg(Msg6);
		UEngineDebugMsgWindow::PushMsg(Msg7);
		UEngineDebugMsgWindow::PushMsg(Msg8);
#endif
	}

	{
		Weapone->SetActorLocation(PlayerPos); // 무기 위치 = 플레이어 위치
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