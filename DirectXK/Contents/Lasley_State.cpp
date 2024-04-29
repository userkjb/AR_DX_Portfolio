#include "PreCompile.h"
#include "Lasley.h"
#include <EngineBase/EngineRandom.h>
#include "Tentacle.h"
#include "DimensionSlash.h"
#include "DemonicBlade.h"
#include "DevilChurchWarlock.h"

void ALasley::StateInit()
{
	// Create
	State.CreateState("Summons");
	State.CreateState("Idle");
	State.CreateState("Wake");

	State.CreateState("DevilEye");
	State.CreateState("DemonicBlade");
	State.CreateState("DimensionCutter");
	State.CreateState("DoubleDimensionCutter");

	State.CreateState("Down");

	// Set Function

	State.SetFunction("Summons",
		std::bind(&ALasley::SummonsBegin, this),
		std::bind(&ALasley::SummonsTick, this, std::placeholders::_1),
		std::bind(&ALasley::SummonsEnd, this));

	State.SetFunction("Idle",
		std::bind(&ALasley::IdleBegin, this),
		std::bind(&ALasley::IdleTick, this, std::placeholders::_1),
		std::bind(&ALasley::IdleExit, this));

	State.SetFunction("DevilEye",
		std::bind(&ALasley::DevilEyeBegin, this),
		std::bind(&ALasley::DevilEyeTick, this, std::placeholders::_1),
		std::bind(&ALasley::DevilEyeExit, this));


	State.SetStartFunction("Wake", std::bind(&ALasley::WakeBegin, this));
	State.SetUpdateFunction("Wake", std::bind(&ALasley::WakeTick, this, std::placeholders::_1));
	
	State.SetStartFunction("DemonicBlade", std::bind(&ALasley::DemonicBladeBegin, this));
	State.SetUpdateFunction("DemonicBlade", std::bind(&ALasley::DemonicBladeTick, this, std::placeholders::_1));

	State.SetFunction("DimensionCutter",
		std::bind(&ALasley::DimensionCutterBegin, this),
		std::bind(&ALasley::DimensionCutterTick, this, std::placeholders::_1),
		std::bind(&ALasley::DimensionCutterExit, this));
	
	State.SetStartFunction("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterBegin, this));
	State.SetUpdateFunction("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterTick, this, std::placeholders::_1));
	
	State.SetFunction("Down",
		std::bind(&ALasley::DownBegin, this),
		std::bind(&ALasley::DownTick, this, std::placeholders::_1),
		std::bind(&ALasley::DownExit, this));


	// Change
	State.ChangeState("Summons");
}

#pragma region Summons
void ALasley::SummonsBegin()
{
	SummonTime = 0.0f;
}

void ALasley::SummonsTick(float _DeltaTime)
{
	// 그냥 내려오는 것 방지.
	if(true == LasleyRenderer->IsActive())
	{
		FVector MoveDemonSword = FVector::Zero;
		MoveDemonSword += FVector::Down * MovePower * _DeltaTime;

		if (52.0f >= LasleyDemonSword->GetLocalPosition().Y)
		{
			SummonTime += _DeltaTime;
			if (1.0f <= SummonTime)
			{
				State.ChangeState("Idle");
				return;
			}
		}
		else
		{
			LasleyDemonSword->AddPosition(MoveDemonSword);
		}
	}

	if (0 >= Hp)
	{
		State.ChangeState("Down");
		return;
	}

#ifdef _DEBUG
	{
		std::string LasleyDemonSword_Str = std::format("DemonSword L Pos : {}\n", LasleyDemonSword->GetLocalPosition().ToString());
		std::string LasleyState = "Summons";
		
		LasleyStageGUI::PushMsg(LasleyDemonSword_Str);
		LasleyStageGUI::PushMsg(LasleyState);
	}
#endif
}

void ALasley::SummonsEnd()
{
	SummonTime = 0.0f;
	LasleyDemonSword->SetActive(false);
	LasleySummonFX->SetActive(true);
}

void ALasley::LasleySummonEndCallBack()
{
	LasleySummonFX->SetActive(false);
}
#pragma endregion


#pragma region Idle
void ALasley::IdleBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
	LasleyRenderer->SetPivot(EPivot::MAX);
}

void ALasley::IdleTick(float _DeltaTime)
{
	// 보스전 시작을 알리면, -> UI -> 보스 소개 끝
	if (true == IsDown('X'))
	{
		// 정해진 첫 번째 패턴 DevilEye
		State.ChangeState("DevilEye");
		return;
	}


	// Slash Test
	if (true == IsDown('Y'))
	{
		std::shared_ptr<ADimensionSlash> Slash = GetWorld()->SpawnActor<ADimensionSlash>("Slash");
		Slash->SetActive(true);
		//Slash->SetActorLocation(FVector(100.0f, 100.0f, 10.0f));
		//Slash->SetActorLocation({100.0f, 100.0f});
	}


#ifdef _DEBUG
	{
		std::string LasleyState = "Lasley Idle";
		LasleyStageGUI::PushMsg(LasleyState);
	}
#endif
	//int Pattern = UEngineRandom::MainRandom.RandomInt(1, 12);
}

void ALasley::IdleExit()
{
}
#pragma endregion


#pragma region DevilEye
void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDevilEye");
	LasleyRenderer->SetPivot(EPivot::BOT);
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	// Tentacle 소환.
	if (true == IsDown('Y'))
	{
		std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
	}

	// 정해진 두 번째 패턴.
	// 오른쪽 상단으로 이동해서
	// double slash 패턴.
	if (true == IsDown('X'))
	{
		State.ChangeState("DemonicBlade");
		return;
	}

#ifdef _DEBUG
	{
		std::string LasleyState = "Lasley DevilEye";
		LasleyStageGUI::PushMsg(LasleyState);
	}
#endif
}
void ALasley::DevilEyeExit()
{
}
#pragma endregion

#pragma region Wake
void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
	LasleyRenderer->SetPivot(EPivot::BOT);
}

void ALasley::WakeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DemonicBlade");
		return;
	}

#ifdef _DEBUG
	{
		std::string LasleyState = "Lasley Wake";
		LasleyStageGUI::PushMsg(LasleyState);
	}
#endif
}

void ALasley::WakeExit()
{
}
#pragma endregion


#pragma region DemonicBlade
void ALasley::DemonicBladeBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDemonicBlade");
	LasleyRenderer->SetPivot(EPivot::MAX);
}

void ALasley::DemonicBladeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DimensionCutter");
		return;
	}

	if (true == IsDown('Y'))
	{
		std::shared_ptr<ADemonicBlade> DemonicBlade = GetWorld()->SpawnActor<ADemonicBlade>("DemonicBlade");
		
		if (LasleyRenderer->GetDir() == EEngineDir::Left)
		{
			DemonicBlade->SetLasleyLarge(Large);
			DemonicBlade->SetLasleyDir(EEngineDir::Left);
			FVector SetPos = GetActorLocation();
			SetPos.X -= 56.0f * 4.0f;
			DemonicBlade->SetDemonicBladePos(SetPos);
			DemonicBlade->SetDemonicBladeActive(true);
			DemonicBlade->SetDemonicBladeStart();
		}
		else if (LasleyRenderer->GetDir() == EEngineDir::Right)
		{
			DemonicBlade->SetLasleyLarge(Large);
			DemonicBlade->SetLasleyDir(EEngineDir::Right);
			FVector SetPos = GetActorLocation();
			SetPos.X += 56.0f * 4.0f;
			DemonicBlade->SetDemonicBladePos(SetPos);	
			DemonicBlade->SetDemonicBladeActive(true);
			DemonicBlade->SetDemonicBladeStart();
		}
	}

#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();
		std::string LasleyState = "Lasley DemonicBlade";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
	}
#endif
}
#pragma endregion

#pragma region DimensionCutter
void ALasley::DimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDimensionCutter");
}

void ALasley::DimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DoubleDimensionCutter");
		return;
	}

#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();
		std::string LasleyState = "Lasley Dimension Cutter";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
	}
#endif
}
void ALasley::DimensionCutterExit()
{
}
#pragma endregion

#pragma region DoubleDimensionCutter
void ALasley::DoubleDimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDoubleDimensionCutter");
}

void ALasley::DoubleDimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("Down");
		return;
	}

#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();
		std::string LasleyState = "Lasley Double Dimension Cutter";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
	}
#endif
}
#pragma endregion

#pragma region Down
void ALasley::DownBegin()
{
	LasleyRenderer->ChangeAnimation("Down");
	LasleyRenderer->SetPivot(EPivot::BOT);
	DownTime = 0.0f;
}

void ALasley::DownTick(float _DeltaTime)
{
	DownTime += _DeltaTime;

	if(true == IsDown('Y'))
	{
		std::shared_ptr<ADevilChurchWarlock> Warlock = GetWorld()->SpawnActor<ADevilChurchWarlock>("Slash");
		Warlock->SetPosition(SummonPos[0]);
		Warlock->SummonWarlock();
	}



	if (true == IsDown('X'))
	{
		State.ChangeState("Idle");
		return;
	}

#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();
		std::string LasleyState = "Lasley Down";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
	}
#endif
}
void ALasley::DownExit()
{
}
#pragma endregion


