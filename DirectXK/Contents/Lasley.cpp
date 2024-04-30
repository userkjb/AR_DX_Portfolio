#include "PreCompile.h"
#include "Lasley.h"
#include <EngineCore/DefaultSceneComponent.h>


ALasley::ALasley()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
	
	{// 라슬리 이동 위치 설정.
		//MovePos.push_back(FVector(100.0f, 100.0f));
		//.....
	}
	
	//불 소환 위치 설정.
	{
		// 시작하자마자.
		// 27
		std::vector<FVector> FVectorData;
		float StartValue = 94.0f;
		for (size_t i = 0; i < 7; i++)
		{
			FVectorData.push_back(FVector(StartValue, 188.0f));
			StartValue += 64.0f;
		}

		// 542
		StartValue += 64.0f * 13.0f;

		for (size_t i = 0; i < 7; i++)
		{
			FVectorData.push_back(FVector(StartValue, 188.0f));
			StartValue += 64.0f;
		}

		TentacleSummonPos.push_back(FVectorData);

		// 1페이즈

		// 2페이즈

		// 3페이즈
	}

	// 사도 소환 위치 설정.
	{
		WarlockSummonPos.push_back(FVector(530.0f, 830.0f));
		WarlockSummonPos.push_back(FVector(530.0f, 430.0f));
		WarlockSummonPos.push_back(FVector(1300.0f, 830.0f));
		WarlockSummonPos.push_back(FVector(1300.0f, 430.0f));
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

	// 소환, 회복 및 부활 할 때 사용할 검.
	LasleyDemonSword = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleyDemonSword->SetupAttachment(Root);
	LasleyDemonSword->SetOrder(ERenderOrder::BossSubObject);
	LasleyDemonSword->SetDir(EEngineDir::Left);
	LasleyDemonSword->SetRotationDeg({ 0.0f, 0.0f, 180.0f });
	LasleyDemonSword->SetPosition({ 0.0f, 1000.0f });

	// 부활 이펙트
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

	if (Life == 0 && Hp <= 20)
	{
		Large = true;
	}

	if (true == b_DoorTentacle)
	{
		DoorTentacle(_DeltaTime);
	}

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
	LasleyRenderer->CreateAnimation("Wake", "LasleyWake", 0.125f, false);
	LasleyRenderer->CreateAnimation("Down", "LasleyDown", 0.125f, false);

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
