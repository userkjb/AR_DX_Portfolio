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
	State.CreateState("Move");
	State.CreateState("DevilEye");
	State.CreateState("DemonicBlade");
	State.CreateState("DimensionCutter");
	State.CreateState("DoubleDimensionCutter");

	State.CreateState("Down");
	State.CreateState("Wake");
	State.CreateState("Die");

	// Set Function

	State.SetFunction("Summons",
		std::bind(&ALasley::SummonsBegin, this),
		std::bind(&ALasley::SummonsTick, this, std::placeholders::_1),
		std::bind(&ALasley::SummonsEnd, this));

	State.SetFunction("Idle",
		std::bind(&ALasley::IdleBegin, this),
		std::bind(&ALasley::IdleTick, this, std::placeholders::_1),
		std::bind(&ALasley::IdleExit, this));

	State.SetFunction("Move",
		std::bind(&ALasley::MoveBegin, this),
		std::bind(&ALasley::MoveTick, this, std::placeholders::_1),
		std::bind(&ALasley::MoveExit, this));

	State.SetFunction("DevilEye",
		std::bind(&ALasley::DevilEyeBegin, this),
		std::bind(&ALasley::DevilEyeTick, this, std::placeholders::_1),
		std::bind(&ALasley::DevilEyeExit, this));

	State.SetFunction("Wake",
		std::bind(&ALasley::WakeBegin, this),
		std::bind(&ALasley::WakeTick, this, std::placeholders::_1),
		std::bind(&ALasley::WakeExit, this));

	State.SetFunction("DemonicBlade",
		std::bind(&ALasley::DemonicBladeBegin, this),
		std::bind(&ALasley::DemonicBladeTick, this, std::placeholders::_1),
		std::bind(&ALasley::DemonicBladeExit, this));

	State.SetFunction("DimensionCutter",
		std::bind(&ALasley::DimensionCutterBegin, this),
		std::bind(&ALasley::DimensionCutterTick, this, std::placeholders::_1),
		std::bind(&ALasley::DimensionCutterExit, this));
	
	State.SetFunction("DoubleDimensionCutter",
		std::bind(&ALasley::DoubleDimensionCutterBegin, this),
		std::bind(&ALasley::DoubleDimensionCutterTick, this, std::placeholders::_1),
		std::bind(&ALasley::DoubleDimensionCutterExit, this));
	
	State.SetFunction("Down",
		std::bind(&ALasley::DownBegin, this),
		std::bind(&ALasley::DownTick, this, std::placeholders::_1),
		std::bind(&ALasley::DownExit, this));

	State.SetStartFunction("Die", std::bind(&ALasley::DieBegin, this));
	State.SetUpdateFunction("Die", std::bind(&ALasley::DieTick, this, std::placeholders::_1));


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
	// �׳� �������� �� ����.
	if(true == LasleyRenderer->IsActive())
	{
		FVector MoveDemonSword = FVector::Zero;
		MoveDemonSword += FVector::Down * SwordSpeed * _DeltaTime;

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
	PreStateName = "Summons";
}

void ALasley::LasleySummonEndCallBack()
{
	LasleySummonFX->SetActive(false);
	PreStateName = "Summons";
}
#pragma endregion


#pragma region Idle
void ALasley::IdleBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
	LasleyRenderer->SetPivot(EPivot::MAX);
	IdleTime = 0.0f;
}

void ALasley::IdleTick(float _DeltaTime)
{
	IdleTime += _DeltaTime;

	if (2.0f <= IdleTime)
	{
		// ������ ������ �˸���, -> UI -> ���� �Ұ� ��
		// ������ ù ��° ���� DevilEye
		if (PreStateName == "Summons")
		{
			State.ChangeState("DevilEye");
			return;
		}

		if (PreStateName == "DevilEye_One")
		{
			State.ChangeState("Move");
			return;
		}

		if (PreStateName == "Move")
		{
			int NorD = UEngineRandom::MainRandom.RandomInt(1, 2);
			if (NorD == 1)
			{
				State.ChangeState("DimensionCutter");
			}
			else
			{
				State.ChangeState("DoubleDimensionCutter");
			}
			return;
		}

		if (PreStateName == "DimensionCutter" || PreStateName == "DoubleDimensionCutter")
		{
			State.ChangeState("DevilEye");
			return;
		}

		if (PreStateName == "DevilEye")
		{
			State.ChangeState("DemonicBlade");
			return;
		}

		if (PreStateName == "DemonicBlade")
		{
			State.ChangeState("Move");
			return;
		}

	}

#ifdef _DEBUG
	{
		std::string LasleyState = "Lasley Idle";
		LasleyStageGUI::PushMsg(LasleyState);
	}
#endif
}

void ALasley::IdleExit()
{
	PreStateName = "Idle";
}
#pragma endregion

#pragma region Move
void ALasley::MoveBegin()
{
	LasleyRenderer->ChangeAnimation("Idle");
	LasleyRenderer->SetPivot(EPivot::MAX);

	if (Life == 3)
	{
		// �� �ٴ� ���� üũ
		MovePosNum = UEngineRandom::MainRandom.RandomInt(0, 9);
	}
	else
	{
		// �� �ٴ� üũ ����.
		MovePosNum = UEngineRandom::MainRandom.RandomInt(0, 7);
	}
}
void ALasley::MoveTick(float _DeltaTime)
{
	FVector MoveVectorPos = LasleyMovePos[MovePosNum];
	FVector FLasleyPos = GetActorLocation();
	FVector LengV = MoveVectorPos - FLasleyPos;
	FVector MoveDir = LengV.Normalize2DReturn();
	float Leng = std::sqrtf(std::powf(FLasleyPos.X - MoveVectorPos.X, 2) + std::powf(FLasleyPos.Y - MoveVectorPos.Y, 2));

	float4 MoveLasley = MoveDir * MoveSpeed * _DeltaTime;

	AddActorLocation(MoveLasley);

	if (5.0f >= Leng)
	{
		SetActorLocation(MoveVectorPos);

		if (0 > (FLasleyPos.X - PlayerPos.X))
		{
			LasleyRenderer->SetDir(EEngineDir::Right);
		}
		else
		{
			LasleyRenderer->SetDir(EEngineDir::Left);
		}

		State.ChangeState("Idle");
		return;
	}
	
#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();

		std::string LasleyState = "Lasley Move";
		std::string LasleyPos = std::format("Lasley Pos : {}\n", FLasleyPos.ToString());
		std::string LasleyToTarget = std::format("Target Pos Len : {}\n", Leng);
		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
		LasleyStageGUI::PushMsg(LasleyToTarget);
	}
#endif
}
void ALasley::MoveExit()
{
	PreStateName = "Move";
}
#pragma endregion

#pragma region DevilEye
void ALasley::DevilEyeBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDevilEye");
	LasleyRenderer->SetPivot(EPivot::BOT);
	DevilEyeTime = 0.0f;
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	// �ݹ����� Tentacle ��ȯ
	if (false == b_DoorTentacle)
	{
		LasleyRenderer->SetFrameCallback("LasleyDevilEye", 8, [=]()
			{
				b_DoorTentacle = true;
			});
	}
	else
	{
		LasleyRenderer->SetFrameCallback("LasleyDevilEye", 8, [=]()
			{
				if (3 == Life)
				{
					int CreatePos = UEngineRandom::MainRandom.RandomInt(3, 6);
					size_t SummonCout = TentacleSummonPos[CreatePos].size();
					for (size_t i = 0; i < SummonCout; i++)
					{
						std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
						Tentacle->SetCreatePos(TentacleSummonPos[CreatePos][i]);
						Tentacle->SetInfinity(false);
						Tentacle->CreateTentacle();
					}
				}
				else if (2 == Life)
				{
					std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
					Tentacle->SetCreatePos(TentacleSummonPos[9][0]);
					Tentacle->SetInfinity(true);
					Tentacle->CreateTentacle();
				}
				else if (1 == Life)
				{
					int CreatePos_1 = UEngineRandom::MainRandom.RandomInt(3, 6);
					int CreatePos_2 = UEngineRandom::MainRandom.RandomInt(3, 6);
					if (CreatePos_1 == CreatePos_2)
					{
						while (true)
						{
							CreatePos_2 = UEngineRandom::MainRandom.RandomInt(3, 6);
							if (CreatePos_1 != CreatePos_2)
							{
								break;
							}
						}
					}

					{
						std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
						Tentacle->SetCreatePos(TentacleSummonPos[3][CreatePos_1]);
						Tentacle->SetInfinity(false);
						Tentacle->CreateTentacle();
					}
					{
						std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
						Tentacle->SetCreatePos(TentacleSummonPos[3][CreatePos_2]);
						Tentacle->SetInfinity(false);
						Tentacle->CreateTentacle();
					}
					{
						int CreatePos = UEngineRandom::MainRandom.RandomInt(7, 8);
						std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
						Tentacle->SetCreatePos(TentacleSummonPos[CreatePos][0]);
						Tentacle->SetInfinity(false);
						Tentacle->CreateTentacle();
					}
				}
			});
	}


	if (true == LasleyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
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
	if (false == b_DevilEye_One)
	{
		PreStateName = "DevilEye_One";
		b_DevilEye_One = true;
	}
	else
	{
		PreStateName = "DevilEye";
	}
}

void ALasley::DoorTentacle(float _DeltaTime)
{
	DoorTentacleTime += _DeltaTime;

	if (false == b_DoorTentacleOne)
	{
		std::shared_ptr<ATentacle> Tentacle_L = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle_L->SetCreatePos(TentacleSummonPos[0][0]);
		Tentacle_L->SetInfinity(true);
		Tentacle_L->CreateTentacle();

		size_t DoorTentacleCount_R = TentacleSummonPos[0].size();
		std::shared_ptr<ATentacle> Tentacle_R = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle_R->SetCreatePos(TentacleSummonPos[0][DoorTentacleCount_R - 1]);
		Tentacle_R->SetInfinity(true);
		Tentacle_R->CreateTentacle();

		DoorTentacles.push_back(Tentacle_L);
		DoorTentacles.push_back(Tentacle_R);

		DoorTentacleTime = 0.0f;

		b_DoorTentacleOne = true;
		doorTentacleCount += 1;
	}

	if (1.0f <= DoorTentacleTime && 6 >= doorTentacleCount)
	{
		std::shared_ptr<ATentacle> Tentacle_L = GetWorld()->SpawnActor<ATentacle>("Tentacle");

		Tentacle_L->SetCreatePos(TentacleSummonPos[0][doorTentacleCount]);
		Tentacle_L->SetInfinity(true);
		Tentacle_L->CreateTentacle();

		size_t DoorTentacleCount_R = TentacleSummonPos[0].size() -1;
		std::shared_ptr<ATentacle> Tentacle_R = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle_R->SetCreatePos(TentacleSummonPos[0][DoorTentacleCount_R - doorTentacleCount]);
		Tentacle_R->SetInfinity(true);
		Tentacle_R->CreateTentacle();

		DoorTentacles.push_back(Tentacle_L);
		DoorTentacles.push_back(Tentacle_R);
		
		DoorTentacleTime = 0.0f;

		doorTentacleCount += 1;
	}
	
	if (1.0f <= DoorTentacleTime && Life == 2 && 5 >= DoorTentacleCount_2)
	{
		std::shared_ptr<ATentacle> Tentacle_L = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle_L->SetCreatePos(TentacleSummonPos[1][DoorTentacleCount_2]);
		Tentacle_L->SetInfinity(true);
		Tentacle_L->CreateTentacle();

		size_t DoorTentacleCount_R = TentacleSummonPos[1].size() - 1;
		std::shared_ptr<ATentacle> Tentacle_R = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle_R->SetCreatePos(TentacleSummonPos[1][DoorTentacleCount_R - DoorTentacleCount_2]);
		Tentacle_R->SetInfinity(true);
		Tentacle_R->CreateTentacle();

		DoorTentacles.push_back(Tentacle_L);
		DoorTentacles.push_back(Tentacle_R);
		
		DoorTentacleTime = 0.0f;
		
		DoorTentacleCount_2++;
	}

	if (1.0f <= DoorTentacleTime && 6 == DoorTentacleCount_2)
	{
		std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle->SetCreatePos(TentacleSummonPos[2][0]);
		Tentacle->SetInfinity(true);
		Tentacle->CreateTentacle();

		DoorTentacles.push_back(Tentacle);

		DoorTentacleCount_2++;

		DoorTentacleTime = 0.0f;
		b_DoorTentacle = false;
	}
}
#pragma endregion

// ��Ȱ.
#pragma region Wake 
void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
	LasleyRenderer->SetPivot(EPivot::BOT);
	if (Hp <= 0)
	{
		Hp = MaxHp; // �� ȸ��.
	}
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
		FVector FLasleyPos = GetActorLocation();
		std::string LasleyState = "Lasley Wake";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
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
	// Large �� ����.
	{
		if (Life == 3)
		{
			Large = false;
		}
		else if (Life == 2)
		{
			int Percentage = UEngineRandom::MainRandom.RandomInt(1, 2);
			if (Percentage == 1)
			{
				Large = true;
			}
			else
			{
				Large = false;
			}
		}
		else if (Life == 1)
		{
			Large = true;
		}
	}

	LasleyRenderer->SetFrameCallback("LasleyDemonicBlade", 7, [=]()
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
		});

	if (true == LasleyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
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
void ALasley::DemonicBladeExit()
{
	PreStateName = "DemonicBlade";
}
#pragma endregion

#pragma region DimensionCutter
void ALasley::DimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDimensionCutter");
}

void ALasley::DimensionCutterTick(float _DeltaTime)
{
	LasleyRenderer->SetFrameCallback("LasleyDimensionCutter", 12, [=]()
		{
			int SlashRotRan = UEngineRandom::MainRandom.RandomInt(0, 90);
			float fSlashRotRan = static_cast<float>(SlashRotRan);
			FVector SlashRot = { 0.0f, 0.0f, fSlashRotRan };
			std::shared_ptr<ADimensionSlash> Slash = GetWorld()->SpawnActor<ADimensionSlash>("Slash");
			Slash->SetActive(true);
			Slash->SetPos(PlayerPos);
			Slash->SetDimensionSlashRot(SlashRot);
			Slash->CreateDimensionSlash();
		});

	if (true == LasleyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
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
	PreStateName = "DimensionCutter";
}
#pragma endregion

#pragma region DoubleDimensionCutter
void ALasley::DoubleDimensionCutterBegin()
{
	LasleyRenderer->ChangeAnimation("LasleyDoubleDimensionCutter");
}

void ALasley::DoubleDimensionCutterTick(float _DeltaTime)
{
	LasleyRenderer->SetFrameCallback("LasleyDoubleDimensionCutter", 12, [=]()
		{
			int SlashRotRan = UEngineRandom::MainRandom.RandomInt(0, 90);
			float fSlashRotRan = static_cast<float>(SlashRotRan);
			FVector SlashRot = { 0.0f, 0.0f, fSlashRotRan };
			std::shared_ptr<ADimensionSlash> Slash = GetWorld()->SpawnActor<ADimensionSlash>("Slash");
			Slash->SetActive(true);
			Slash->SetPos(PlayerPos);
			Slash->SetDimensionSlashRot(SlashRot);
			Slash->CreateDimensionSlash();
		});

	LasleyRenderer->SetFrameCallback("LasleyDoubleDimensionCutter", 16, [=]()
		{
			int SlashRotRan = UEngineRandom::MainRandom.RandomInt(0, 90);
			float fSlashRotRan = static_cast<float>(SlashRotRan);
			FVector SlashRot = { 0.0f, 0.0f, fSlashRotRan };
			std::shared_ptr<ADimensionSlash> Slash = GetWorld()->SpawnActor<ADimensionSlash>("Slash");
			Slash->SetActive(true);
			Slash->SetPos(PlayerPos);
			Slash->SetDimensionSlashRot(SlashRot);
			Slash->CreateDimensionSlash();
		});


	if (true == LasleyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
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
void ALasley::DoubleDimensionCutterExit()
{
	PreStateName = "DoubleDimensionCutter";
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

	//if(true == IsDown('Y'))
	if(2.0f <= DownTime)
	{
		int WarlocsDataSize = static_cast<int>(Warlocks.size());
		if (4 > WarlocsDataSize)
		{
			std::shared_ptr<ADevilChurchWarlock> Warlock = GetWorld()->SpawnActor<ADevilChurchWarlock>("Slash");
			Warlock->SetPosition(WarlockSummonPos[WarlockCount]);
			Warlock->SummonWarlock();
			Warlocks.push_back(Warlock);
			WarlockCount++;
		}
	}

	// ��� ���ϵ��� �� ������,
	if (0 != WarlockCount)
	{
		if (true == Warlocks[0]->IsDestroy() &&
			true == Warlocks[1]->IsDestroy() &&
			true == Warlocks[2]->IsDestroy() &&
			true == Warlocks[3]->IsDestroy())
		{
			State.ChangeState("Wake");
			return;
		}
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
	DownTime = 0.0f;
}
#pragma endregion

#pragma region Die
void ALasley::DieBegin()
{
}

void ALasley::DieTick(float _DeltaTime)
{
}
#pragma endregion