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

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	// 콜리전은 무조건 오더를 지정해줘야 한다.
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

	PixelCheck(_DeltaTime);

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
		////
	}
#ifdef _DEBUG
		t_DeBugFunction(_DeltaTime);
#endif

	{
		Weapone->SetActorLocation(PlayerPos); // 무기 위치 = 플레이어 위치 // 이건 여기서 해주는 것이 맞다.
		Weapone->SetPlayerToMouseDir(PlayerToMouseDir);
		Weapone->SetWeaponRotation(WeaponDir); // 무기에 회전 값을 넘겨줌.
	}
#ifdef _DEBUG
	
#endif
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

void APlayer::t_DeBugFunction(float _DeltaTime)
{
	PlayerPos = GetActorLocation();
	FVector PlayerScale = GetActorScale3D();
	float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
	float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);

	FVector ScreenScale = GEngine->EngineWindow.GetWindowScale();
	//CulMousPos.Y -= ScreenScale.Y;
	//CulMousPos.Y *= -1.0f;

	//float4 Leng = CulMousPos - PlayerPos;
	float4 Leng = MousePosWorld - PlayerPos;
	PlayerToMouseDir = Leng.Normalize3DReturn();

	float Rot = atan2((MousePosWorld.Y - PlayerPos.Y), (MousePosWorld.X - PlayerPos.X));
	Rot *= UEngineMath::RToD; // 디그리( 0 ~ 180)
	WeaponDir.Z = Rot;

	std::string StateName = State.GetCurStateName();
	//std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
	//std::string Msg2 = std::format("Player_World Pos : {}\n", PlayerPos.ToString());
	std::string Msg3 = std::format("Player_World Scale : {}\n", PlayerScale.ToString());
	//std::string Msg4 = std::format("Mouses_World Pos : {}\n", MousePosWorld.ToString());
	//std::string Msg5 = std::format("Mouses_World Pos : {}\n", MousePosWorld.ToString());
	//std::string Msg6 = std::format("Leng : {}\n", Leng.ToString());
	//std::string Msg7 = std::format("PlayerToMouseDir : {}\n", PlayerToMouseDir.ToString());
	//std::string Msg8 = std::format("Leng : {}\n", Leng.ToString());
	//std::string Msg9 = std::format("Rot : {}\n", Rot);
	//std::string Msg10 = std::format("CalVectors : {}\n", CalVectors.ToString());

	//UEngineDebugMsgWindow::PushMsg(Msg1);
	//UEngineDebugMsgWindow::PushMsg(Msg2);
	UEngineDebugMsgWindow::PushMsg(Msg3);
	//UEngineDebugMsgWindow::PushMsg(Msg4);
	//UEngineDebugMsgWindow::PushMsg(Msg5);
	//UEngineDebugMsgWindow::PushMsg(Msg6);
	//UEngineDebugMsgWindow::PushMsg(Msg7);
	//UEngineDebugMsgWindow::PushMsg(Msg8);
	//UEngineDebugMsgWindow::PushMsg(Msg9);
	//UEngineDebugMsgWindow::PushMsg(Msg10);
	UEngineDebugMsgWindow::PushMsg(StateName);
}
