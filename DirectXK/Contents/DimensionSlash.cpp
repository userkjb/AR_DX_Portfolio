#include "PreCompile.h"
#include "DimensionSlash.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "LasleyStageGUI.h"
#include "Player.h"
#include "PlayerStruct.h"

ADimensionSlash::ADimensionSlash()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Render");
	SetRoot(Root);

	//SetActorLocation(FVector(0.0f, 0.0f, 1.0f));

	DimensionSlashRenderer_B = CreateDefaultSubObject<USpriteRenderer>("SlashRenderer");
	DimensionSlashRenderer_B->SetupAttachment(Root);
	DimensionSlashRenderer_B->SetPivot(EPivot::MAX);
	DimensionSlashRenderer_B->SetOrder(ERenderOrder::BossSkill_B);
	DimensionSlashRenderer_B->SetPosition(FVector(200.0f, 200.0f));
	DimensionSlashRenderer_B->SetActive(true);

	DimensionSlashRenderer_F = CreateDefaultSubObject<USpriteRenderer>("SlashRenderer");
	DimensionSlashRenderer_F->SetupAttachment(Root);
	DimensionSlashRenderer_F->SetOrder(ERenderOrder::BossSkill_F);
	DimensionSlashRenderer_F->SetPosition(FVector(200.0f, 200.0f));
	DimensionSlashRenderer_F->SetActive(false);


	SlashCollision = CreateDefaultSubObject<UCollision>("SlashCollision");
	SlashCollision->SetupAttachment(Root);
	SlashCollision->SetCollisionGroup(ECollisionOrder::BossSkill);
	SlashCollision->SetCollisionType(ECollisionType::RotRect);
	SlashCollision->SetPosition(DimensionSlashRenderer_B->GetLocalPosition());
	SlashCollision->SetScale(FVector(60.0f, 1032.0f, 1.0f, 1.0f));
}

ADimensionSlash::~ADimensionSlash()
{
}

void ADimensionSlash::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	InitState();

	DimensionSlashRenderer_B->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	DimensionSlashRenderer_F->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ADimensionSlash::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);


#ifdef _DEBUG
	{
		FVector LocalPos = DimensionSlashRenderer_B->GetLocalPosition();
		FVector WorldPos = DimensionSlashRenderer_B->GetWorldPosition();
		FVector LocalScl = DimensionSlashRenderer_B->GetLocalScale();
		FVector WorldScl = DimensionSlashRenderer_B->GetWorldScale();
		//FVector Col_L_Pos = SlashCollision->GetLocalPosition();
		//FVector Col_W_Pos = SlashCollision->GetWorldPosition();
		FVector ColLScale = SlashCollision->GetLocalScale();
		FVector ColWScale = SlashCollision->GetWorldScale();
		
		std::string LoclaPos_str = std::format("FX L Pos : {}\n", LocalPos.ToString());
		std::string WorldPos_str = std::format("FX W Pos : {}\n", WorldPos.ToString());
		std::string LoclaScl_str = std::format("FX L Scl : {}\n", LocalScl.ToString());
		std::string WorldScl_str = std::format("FX W Scl : {}\n", WorldScl.ToString());
		//std::string ColLoclaPos_str = std::format("Col L Pos : {}\n", Col_L_Pos.ToString());
		//std::string ColWorldPos_str = std::format("Col W Pos : {}\n", Col_W_Pos.ToString());
		std::string ColLoclaScl_str = std::format("Col L Pos : {}\n", ColLScale.ToString());
		std::string ColWorldScl_str = std::format("Col W Pos : {}\n", ColWScale.ToString());

		LasleyStageGUI::PushMsg(LoclaPos_str);
		LasleyStageGUI::PushMsg(WorldPos_str);
		LasleyStageGUI::PushMsg(LoclaScl_str);
		LasleyStageGUI::PushMsg(WorldScl_str);
		//LasleyStageGUI::PushMsg(ColLoclaPos_str);
		//LasleyStageGUI::PushMsg(ColWorldPos_str);
		LasleyStageGUI::PushMsg(ColLoclaScl_str);
		LasleyStageGUI::PushMsg(ColWorldScl_str);

		if (true == DimensionSlashRenderer_B->IsActive())
		{
			std::string t = "true";
			LasleyStageGUI::PushMsg(t);
		}
		else if (false == DimensionSlashRenderer_B->IsActive())
		{
			std::string t = "false";
			LasleyStageGUI::PushMsg(t);
		}

		
	}
#endif

}

void ADimensionSlash::CreateAnimation()
{
	DimensionSlashRenderer_B->CreateAnimation("DimensionSlashBack", "DimensionSlashBack.png", 0.125f, false);

	DimensionSlashRenderer_F->CreateAnimation("DimensionSlashFront", "DimensionSlashFront.png", 0.125f, false);


	DimensionSlashRenderer_B->ChangeAnimation("DimensionSlashBack");
	DimensionSlashRenderer_F->ChangeAnimation("DimensionSlashFront");
}

void ADimensionSlash::InitState()
{
	State.CreateState("Create");

	State.SetFunction("Create",
		std::bind(&ADimensionSlash::CreateBegin, this),
		std::bind(&ADimensionSlash::CreateTick, this, std::placeholders::_1),
		std::bind(&ADimensionSlash::CreateExit, this));

	State.ChangeState("Create");
}


#pragma region Create
void ADimensionSlash::CreateBegin()
{
	if (false == DimensionSlashRenderer_B->IsActive())
	{
		DimensionSlashRenderer_B->SetActive(true);
	}

	DimensionSlashRenderer_B->ChangeAnimation("DimensionSlashBack");
	DimensionSlashRenderer_F->ChangeAnimation("DimensionSlashFront");
}

void ADimensionSlash::CreateTick(float _DeltaTime)
{
	int a = 0;
	DimensionSlashRenderer_B->SetFrameCallback("DimensionSlashBack", 12, std::bind(&ADimensionSlash::FrameCallBack, this));
	if (true == DimensionSlashRenderer_F->IsCurAnimationEnd())
	{
		int a = 0; // 여기 안탄 이유는 Super 미 선언 때문이였고.
		DimensionSlashRenderer_F->SetActive(false);
	}
	if (true == DimensionSlashRenderer_B->IsCurAnimationEnd())
	{
		int a = 0; // 여기 안탄 이유는 Super 미 선언 때문이였고.
		SlashCollision->SetActive(false);
		DimensionSlashRenderer_B->SetActive(false);
		Destroy();
	}

	CollisionCallBack(_DeltaTime);
}

void ADimensionSlash::CreateExit()
{
	//Destroy();
}

void ADimensionSlash::FrameCallBack()
{
	int a = 0; // USpriteRenderer를 전방선언 하니 이건 탐.
	DimensionSlashRenderer_F->SetActive(true);
	SlashCollision->SetActive(true);
}
#pragma endregion


void ADimensionSlash::CollisionCallBack(float _DeltaTime)
{
	SlashCollision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			//APlayer* Player = dynamic_cast<APlayer*>(_Collison->GetActor());
			EPlayerStateValue::Hp -= 10;
		});

}