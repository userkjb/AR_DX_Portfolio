#include "PreCompile.h"
#include "Lasley.h"
#include <EngineBase/EngineRandom.h>

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

	State.SetStartFunction("Idle", std::bind(&ALasley::IdleBegin, this));
	State.SetUpdateFunction("Idle", std::bind(&ALasley::IdleTick, this, std::placeholders::_1));

	State.SetStartFunction("DevilEye", std::bind(&ALasley::DevilEyeBegin, this));
	State.SetUpdateFunction("DevilEye", std::bind(&ALasley::DevilEyeTick, this, std::placeholders::_1));
	State.SetStartFunction("Wake", std::bind(&ALasley::WakeBegin, this));
	State.SetUpdateFunction("Wake", std::bind(&ALasley::WakeTick, this, std::placeholders::_1));
	State.SetStartFunction("DemonicBlade", std::bind(&ALasley::DemonicBladeBegin, this));
	State.SetUpdateFunction("DemonicBlade", std::bind(&ALasley::DemonicBladeTick, this, std::placeholders::_1));
	State.SetStartFunction("DimensionCutter", std::bind(&ALasley::DimensionCutterBegin, this));
	State.SetUpdateFunction("DimensionCutter", std::bind(&ALasley::DimensionCutterTick, this, std::placeholders::_1));
	State.SetStartFunction("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterBegin, this));
	State.SetUpdateFunction("DoubleDimensionCutter", std::bind(&ALasley::DoubleDimensionCutterTick, this, std::placeholders::_1));
	State.SetStartFunction("Down", std::bind(&ALasley::DownBegin, this));
	State.SetUpdateFunction("Down", std::bind(&ALasley::DownTick, this, std::placeholders::_1));


	// Change
	State.ChangeState("Summons");
}

#pragma region Summons
void ALasley::SummonsBegin()
{
	
}

void ALasley::SummonsTick(float _DeltaTime)
{
	FVector MoveDemonSword = FVector::Zero;
	float MovePower = 300.0f;

	MoveDemonSword += FVector::Down * MovePower * _DeltaTime;

	LasleyDemonSword->AddPosition(MoveDemonSword);

	{
		std::string LasleyDemonSword_Str = std::format("DemonSword L Pos : {}\n", LasleyDemonSword->GetLocalPosition().ToString());

		LasleyStageGUI::PushMsg(LasleyDemonSword_Str);
	}
}

void ALasley::SummonsEnd()
{
}

void ALasley::LasleySummonEndCallBack()
{
	LasleySummonFX->SetActive(false);
	//int x = UEngineRandom::MainRandom.RandomInt(1, 12);
}
#pragma endregion

#pragma region DevilEye
void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("DevilEye");
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("Idle");
		return;
	}
}
#pragma endregion


#pragma region Idle
void ALasley::IdleBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
}

void ALasley::IdleTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("Wake");
		return;
	}
}
#pragma endregion


#pragma region Wake
void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
}

void ALasley::WakeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DemonicBlade");
		return;
	}
}
#pragma endregion


#pragma region DemonicBlade
void ALasley::DemonicBladeBegin()
{
	LasleyRenderer->ChangeAnimation("DemonicBlade");
}

void ALasley::DemonicBladeTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DimensionCutter");
		return;
	}
}
#pragma endregion

#pragma region DimensionCutter
void ALasley::DimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DimensionCutter");
}

void ALasley::DimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("DoubleDimensionCutter");
		return;
	}
}
#pragma endregion

#pragma region DoubleDimensionCutter
void ALasley::DoubleDimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("DoubleDimensionCutter");
}

void ALasley::DoubleDimensionCutterTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("Down");
		return;
	}
}
#pragma endregion

#pragma region Down
void ALasley::DownBegin()
{
	LasleyRenderer->ChangeAnimation("Down");
}

void ALasley::DownTick(float _DeltaTime)
{
	if (true == IsDown('X'))
	{
		State.ChangeState("Idle");
		return;
	}
}
#pragma endregion


