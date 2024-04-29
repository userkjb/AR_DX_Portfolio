#include "PreCompile.h"
#include "Lasley.h"
#include <EngineCore/DefaultSceneComponent.h>


ALasley::ALasley()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
	
	{// 불 소환 위치 설정.
		MovePos.assign(12, FVector::Zero);
		MovePos.push_back(FVector(100.0f, 100.0f));
		//.....
	}
	
	
	LasleyRenderer = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleyRenderer->SetupAttachment(Root);
	LasleyRenderer->SetPivot(EPivot::BOT);
	LasleyRenderer->SetOrder(ERenderOrder::Boss);
	LasleyRenderer->SetDir(EEngineDir::Left);

	LasleyCollision = CreateDefaultSubObject<UCollision>("LasleyCollision");
	LasleyCollision->SetupAttachment(Root);
	LasleyCollision->SetCollisionGroup(ECollisionOrder::Boss);
	LasleyCollision->SetCollisionType(ECollisionType::RotRect);
	//LasleyCollision->SetScale();

	LasleyDemonSword = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleyDemonSword->SetupAttachment(Root);
	LasleyDemonSword->SetOrder(ERenderOrder::BossSubObject);
	LasleyDemonSword->SetDir(EEngineDir::Left);
	LasleyDemonSword->SetRotationDeg({ 0.0f, 0.0f, 180.0f });
	LasleyDemonSword->SetPosition({ 0.0f, 1000.0f });

	LasleySummonFX = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleySummonFX->SetupAttachment(Root);
	LasleySummonFX->SetPivot(EPivot::BOT);
	LasleySummonFX->SetOrder(ERenderOrder::BossBodyFX);
	LasleySummonFX->SetActive(false);
	

	InputOn(); // test
}

ALasley::~ALasley()
{
}

void ALasley::BeginPlay()
{
	Super::BeginPlay();

	//SetActorScale3D(FVector(45.0f, 44.0f, 0.0f));

	CreateAnimation();

	StateInit();

	LasleyRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	LasleySummonFX->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	LasleyDemonSword->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
}

void ALasley::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

#ifdef _DEBUG
	if (true == IsDown('I'))
	{
		if (LasleyRenderer->GetDir() == EEngineDir::Right)
		{
			LasleyRenderer->SetDir(EEngineDir::Left);
		}
		else if (LasleyRenderer->GetDir() == EEngineDir::Left)
		{
			LasleyRenderer->SetDir(EEngineDir::Right);
		}
	}
#endif
}

void ALasley::CreateAnimation()
{
	LasleyRenderer->CreateAnimation("Summons", "LasleyDown", 0.125f, false, 9, 9);
	// State
	//LasleyRenderer->CreateAnimation("Idle", "LasleyIdle", 0.125f);
	LasleyRenderer->CreateAnimation("Idle", "LasleyIdle.png", 0.125f, true, 0, 23); // Pivot MAX
	LasleyRenderer->CreateAnimation("Wake", "LasleyWake", 0.125f);
	LasleyRenderer->CreateAnimation("Down", "LasleyDown", 0.125f);

	// Skill
	//LasleyRenderer->CreateAnimation("DemonicBlade", "LasleyDemonicBlade", 0.125f);
	//LasleyRenderer->CreateAnimation("DimensionCutter", "LasleyDimensionCutter", 0.125f);
	//LasleyRenderer->CreateAnimation("DoubleDimensionCutter", "LasleyDimensionCutter", 0.125f);

	LasleyRenderer->CreateAnimation("LasleyDemonicBlade", "LasleyDemonicBlade.png", 0.0625f, true, 0, 18); // 공란 때문에 범위 지정.
	LasleyRenderer->CreateAnimation("LasleyDevilEye", "LasleyDevilEye", 0.0625f, true); // Pivot BOT
	LasleyRenderer->CreateAnimation("LasleyDimensionCutter", "LasleyDimensionCutter.png", 0.0625f, true);
	LasleyRenderer->CreateAnimation("LasleyDoubleDimensionCutter", "LasleyDoubleDimensionCutter.png", 0.0625f, true, 0, 28);



	LasleyDemonSword->CreateAnimation("LasleyDemonSword", "LasleyDemonSword", 0.125f, true);

	LasleySummonFX->CreateAnimation("LasleySummonFX", "LasleySummonsFX", 0.0625f, false, 0, 12);
	LasleySummonFX->SetLastFrameCallback("LasleySummonFX", std::bind(&ALasley::LasleySummonEndCallBack, this));

	// End
	LasleyRenderer->ChangeAnimation("Summons");

	LasleySummonFX->ChangeAnimation("LasleySummonFX");
	LasleyDemonSword->ChangeAnimation("LasleyDemonSword");
}
