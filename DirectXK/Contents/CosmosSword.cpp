#include "PreCompile.h"
#include "CosmosSword.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CosmosSwordFX.h"

ACosmosSword::ACosmosSword()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	WeaponRenderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	WeaponRenderer->SetupAttachment(Root);
	WeaponRenderer->SetPivot(EPivot::BOT);
	WeaponRenderer->SetOrder(ERenderOrder::Weapon_Prev);
}

ACosmosSword::~ACosmosSword()
{
}

void ACosmosSword::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	StateInit();

	WeaponRenderer->SetSprite("CosmosSwordDefault.png");
	//WeaponRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	WeaponRenderer->SetScale(FVector(44.0f, 132.0f));

	InputOn();
}

void ACosmosSword::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
}

void ACosmosSword::CreateAnimation()
{
	WeaponRenderer->CreateAnimation("Idle", "CosmosSwordIdle", 0.125f, true);

	WeaponRenderer->ChangeAnimation("Idle");
}

void ACosmosSword::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");

	State.SetStartFunction("None", std::bind(&ACosmosSword::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ACosmosSword::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Idle",
		std::bind(&ACosmosSword::IdleBegin, this),
		std::bind(&ACosmosSword::IdleTick, this, std::placeholders::_1),
		std::bind(&ACosmosSword::IdleExit, this));

	State.ChangeState("None");
	PreState = "None";
}

void ACosmosSword::NoneBegin()
{}

void ACosmosSword::NoneTick(float _DeltaTime)
{}

void ACosmosSword::IdleBegin()
{
	FVector WeaponScale = WeaponRenderer->GetLocalScale();
	WeaponScale.Y /= 2.0f;
	WeaponRenderer->SetPosition(FVector(0.0f, WeaponScale.Y));

	PreState = "Idle";
}

void ACosmosSword::IdleTick(float _DeltaTime)
{
	float4 WeaponActorPos = GetActorLocation();
	float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
	float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);
	float4 Leng = MousePosWorld - WeaponActorPos;
	float4 WeaponToMouseDir = Leng.Normalize2DReturn();
	float Rot = atan2((MousePosWorld.Y - WeaponActorPos.Y), (MousePosWorld.X - WeaponActorPos.X));
	Rot *= UEngineMath::RToD;

	FVector WeaponRotation = FVector::Zero;	

	FVector DefaultMove = SetActorPos;
	DefaultMove.Y -= 40.0f;

	FVector AttackRotationFX = FVector::Zero;
	if (EEngineDir::Right == SetPlayerDir)
	{
		DefaultMove.X += 30.0f;
		SetActorLocation(DefaultMove);
		WeaponRotation.Z = 0.0f;
		//AttackRotationFX.X += 0.0f;
	}
	else if (EEngineDir::Left == SetPlayerDir)
	{
		DefaultMove.X -= 30.0f;
		SetActorLocation(DefaultMove);
		WeaponRotation.Z = -180.0f;
		AttackRotationFX.X -= 180.0f;
	}

	if (true == IsDown(VK_LBUTTON))
	{
		if (true == b_Attack)
		{
			AttackRotation.X += 180.0f;
			b_Attack = false;
		}
		else
		{
			AttackRotation.X -= 180.0f;
			b_Attack = true;
		}

		std::shared_ptr<ACosmosSwordFX> WeaponFXActor = GetWorld()->SpawnActor<ACosmosSwordFX>("WeaponFX", ERenderOrder::Weapon_FX);
		//WeaponFXActor->SetFXScale(WeaponRenderer->GetLocalScale());
		FVector WeaponCollisionPos = FVector::Zero;
		FVector WeaponCollisionRot = WeaponRotation + AttackRotationFX;
		WeaponCollisionRot.Z += Rot;
		WeaponCollisionPos = GetActorLocation();
		WeaponCollisionPos += WeaponToMouseDir * WeaponRenderer->GetLocalScale().hY();
		WeaponCollisionPos.Z = 0.0f;
		WeaponCollisionPos.W = 1.0f;
		WeaponFXActor->SetCreatePosition(WeaponCollisionPos);
		WeaponCollisionRot.Z -= 90.0f;
		WeaponFXActor->SetCreateRotation(WeaponCollisionRot);

		WeaponFXActor->CreateWeaponFX();
	}

	WeaponRotation += AttackRotation;
	WeaponRotation.Z += Rot;
	SetActorRotation(WeaponRotation);



	{
		FVector ActorLocation = GetActorLocation();
		FVector CosmosScale1 = WeaponRenderer->GetWorldScale();
		FVector CosmosScale2 = WeaponRenderer->GetLocalScale();

		std::string ActorLot = std::format("Actor : {}\n", ActorLocation.ToString());
		std::string WorldRender = std::format("World : {}\n", CosmosScale1.ToString());
		std::string LocalRender = std::format("Local : {}\n", CosmosScale2.ToString());
		std::string RotationValue = std::format("Rotation : {}\n", WeaponRotation.ToString());

		UEngineDebugMsgWindow::PushMsg(ActorLot);
		UEngineDebugMsgWindow::PushMsg(WorldRender);
		UEngineDebugMsgWindow::PushMsg(LocalRender);
		UEngineDebugMsgWindow::PushMsg(RotationValue);
	}
}

void ACosmosSword::IdleExit()
{
}
