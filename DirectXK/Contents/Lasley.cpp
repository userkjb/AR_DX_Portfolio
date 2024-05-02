#include "PreCompile.h"
#include "Lasley.h"
#include <EngineCore/DefaultSceneComponent.h>


ALasley::ALasley()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
	
	// �󽽸� �̵� ��ġ ����.
	{
		float calValue = 64.0f;
		float PositionY_1 = 508.0f - calValue;
		float PositionY_2 = 892.0f - calValue;
		float PositionY_3 = 188.0f - calValue;
		LasleyMovePos.push_back(FVector(190.0f, PositionY_1));
		LasleyMovePos.push_back(FVector(702.0f, PositionY_1));

		LasleyMovePos.push_back(FVector(190.0f, PositionY_2));
		LasleyMovePos.push_back(FVector(702.0f, PositionY_2));

		LasleyMovePos.push_back(FVector(1150.0f, PositionY_1));
		LasleyMovePos.push_back(FVector(1662.0f, PositionY_1));

		LasleyMovePos.push_back(FVector(1150.0f, PositionY_2));
		LasleyMovePos.push_back(FVector(1662.0f, PositionY_2));

		LasleyMovePos.push_back(FVector(702.0f, PositionY_3));
		LasleyMovePos.push_back(FVector(1150.0f, PositionY_3));
	}
	
	// �ٴ� �� ��ȯ ��ġ ����.
	{
		// �������ڸ���, 1������
		// 27
		{
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
		}


		// 2������ 13��
		{
			std::vector<FVector> FVectorData;
			float StartValue = 542.0f;

			for (size_t i = 0; i < 6; i++)
			{
				FVectorData.push_back(FVector(StartValue, 188.0f));
				StartValue += 64.0f;
			}

			StartValue += 64.0f;

			for (size_t i = 0; i < 6; i++)
			{
				FVectorData.push_back(FVector(StartValue, 188.0f));
				StartValue += 64.0f;
			}

			TentacleSummonPos.push_back(FVectorData);
		}

		// �߾�
		{
			std::vector<FVector> FVectorData;
			FVectorData.push_back(FVector(926.0f, 188.0f));
			TentacleSummonPos.push_back(FVectorData);
		}
	}
	// TentacleSummonPos[0/1/2][FVector]


	// ��� �� ��ġ
	// TentacleSummonPos[3/4/5/6][FVector]
	{
		{
			std::vector<FVector> FVectorData;
			float StartValue = 158.0f;
			for (size_t i = 0; i < 10; i++)
			{
				FVectorData.push_back(FVector(StartValue, 508.0f));
				StartValue += 64.0f;
			}

			TentacleSummonPos.push_back(FVectorData);
		}
		{
			std::vector<FVector> FVectorData;
			float StartValue = 158.0f;
			for (size_t i = 0; i < 10; i++)
			{
				FVectorData.push_back(FVector(StartValue, 892.0f));
				StartValue += 64.0f;
			}

			TentacleSummonPos.push_back(FVectorData);
		}
		{
			std::vector<FVector> FVectorData;
			float StartValue = 1118.0f;
			for (size_t i = 0; i < 10; i++)
			{
				FVectorData.push_back(FVector(StartValue, 508.0f));
				StartValue += 64.0f;
			}

			TentacleSummonPos.push_back(FVectorData);
		}
		{
			std::vector<FVector> FVectorData;
			float StartValue = 1118.0f;
			for (size_t i = 0; i < 10; i++)
			{
				FVectorData.push_back(FVector(StartValue, 892.0f));
				StartValue += 64.0f;
			}

			TentacleSummonPos.push_back(FVectorData);
		}
	}
	// TentacleSummonPos[3/4/5/6][FVector]

	// X ��.
	// TentacleSummonPos[7/8/9][FVector]
	{
		// /
		{ 
			std::vector<FVector> FVectorData;
			float StartValue_X = 1054.f;
			float StartValue_Y = 828.0f;
			for (size_t i = 0; i < 5; i++)
			{
				FVectorData.push_back(FVector(StartValue_X, StartValue_Y));
				StartValue_X -= 64.0f;
				StartValue_Y -= 64.0f;
			}
			TentacleSummonPos.push_back(FVectorData);
		}
		//
		{
			std::vector<FVector> FVectorData;
			float StartValue_X = 1054.f;
			float StartValue_Y = 572.0f;
			for (size_t i = 0; i < 5; i++)
			{
				FVectorData.push_back(FVector(StartValue_X, StartValue_Y));
				StartValue_X -= 64.0f;
				StartValue_Y += 64.0f;
			}
			TentacleSummonPos.push_back(FVectorData);
		}
		// X
		{
			std::vector<FVector> FVectorData;
			float StartValue_X = 1118.0f;
			float StartValue_Y = 892.0f;
			for (size_t i = 0; i < 7; i++)
			{
				FVectorData.push_back(FVector(StartValue_X, StartValue_Y));
				StartValue_X -= 64.0f;
				StartValue_Y -= 64.0f;
			}
			float NextX = 734.0f;
			float NextY = 892.0f;
			for (size_t i = 0; i < 7; i++)
			{
				if (NextX == 926.0f && NextY == 700.0f)
				{
					NextX += 64.0f;
					NextY -= 64.0f;
					continue;
				}
				FVectorData.push_back(FVector(NextX, NextY));
				NextX += 64.0f;
				NextY -= 64.0f;
			}
			TentacleSummonPos.push_back(FVectorData);
		}
	}



	// �絵 ��ȯ ��ġ ����.
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

	// ��ȯ, ȸ�� �� ��Ȱ �� �� ����� ��.
	LasleyDemonSword = CreateDefaultSubObject<USpriteRenderer>("LasleyRenderer");
	LasleyDemonSword->SetupAttachment(Root);
	LasleyDemonSword->SetOrder(ERenderOrder::BossSubObject);
	LasleyDemonSword->SetDir(EEngineDir::Left);
	LasleyDemonSword->SetRotationDeg({ 0.0f, 0.0f, 180.0f });
	LasleyDemonSword->SetPosition({ 0.0f, 1000.0f });

	// ��Ȱ ����Ʈ
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

	//{
	//	Warlocks.reserve(4);
	//}
}

void ALasley::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	CollisionCheck(_DeltaTime);

	if (Life != 3 )
	{
		Large = true;
	}

	if (true == b_DoorTentacle)
	{
		if (State.GetCurStateName() != "Die")
		{
			DoorTentacle(_DeltaTime);
		}
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

	std::string LasleyHP = std::format("Lasley HP : {}\n", Hp);
	std::string LasyeyLife = std::format("Lasley Life : {}\n", Life);

	LasleyStageGUI::PushMsg(LasleyHP);
	LasleyStageGUI::PushMsg(LasyeyLife);
#endif
}

void ALasley::CreateAnimation()
{
	LasleyRenderer->CreateAnimation("Summons", "LasleyDown", 0.125f, false, 9, 9);
	// State
	LasleyRenderer->CreateAnimation("Idle", "LasleyIdle.png", 0.0625f, true, 0, 23); // Pivot MAX
	LasleyRenderer->CreateAnimation("Wake", "LasleyWake", 0.0625f, false);
	LasleyRenderer->CreateAnimation("Down", "LasleyDown", 0.0625f, false);

	// Skill
	LasleyRenderer->CreateAnimation("LasleyDemonicBlade", "LasleyDemonicBlade.png", 0.0625f, true, 0, 18); // ���� ������ ���� ����.
	LasleyRenderer->CreateAnimation("LasleyDevilEye", "LasleyDevilEye", 0.0625f, false); // Pivot BOT
	LasleyRenderer->CreateAnimation("LasleyDimensionCutter", "LasleyDimensionCutter.png", 0.0625f, false);
	LasleyRenderer->CreateAnimation("LasleyDoubleDimensionCutter", "LasleyDoubleDimensionCutter.png", 0.0625f, false, 0, 28);

	LasleyDemonSword->CreateAnimation("LasleyDemonSword", "LasleyDemonSword", 1.0625f, true);

	LasleySummonFX->CreateAnimation("LasleySummonFX", "LasleySummonsFX", 0.0625f, false, 0, 12);
	LasleySummonFX->SetLastFrameCallback("LasleySummonFX", std::bind(&ALasley::LasleySummonEndCallBack, this));

	// End
	LasleyRenderer->ChangeAnimation("Summons");
	LasleySummonFX->ChangeAnimation("LasleySummonFX");
	LasleyDemonSword->ChangeAnimation("LasleyDemonSword");
}
