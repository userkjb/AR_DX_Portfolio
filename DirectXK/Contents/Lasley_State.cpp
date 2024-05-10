#include "PreCompile.h"
#include "Lasley.h"
#include <EngineBase/EngineRandom.h>
#include "Tentacle.h"
#include "DimensionSlash.h"
#include "DemonicBlade.h"
#include "DevilChurchWarlock.h"
#include "LasleyUI.h"
#include "CosmosSwordFX.h"

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
	// 그냥 내려오는 것 방지.
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
	FVector GetScale = LasleyRenderer->GetLocalScale();
	LasleyCollision->SetScale(GetScale);

	FVector CulPosValue = LasleyCollision->GetLocalPosition();
	CulPosValue.Y += 48.0f;
	LasleyCollision->SetPosition(CulPosValue);

	Explosion_Sound.On();
	b_ExplosionSound = true;
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

	// 보스전 시작을 알리면, -> UI -> 보스 소개 끝
	// 정해진 첫 번째 패턴 DevilEye
	if (2.0f <= IdleTime && PreStateName == "Summons")
	{
		if (true == BattleStart)
		{
			State.ChangeState("DevilEye");
			return;
		}
	}

	if (2.0f <= IdleTime && PreStateName == "DevilEye_One")
	{
		State.ChangeState("Move");
		return;
	}

	if (PreStateName == "Move" && false == MoveBlade)
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
	else if (PreStateName == "Move" && true == MoveBlade)
	{
		State.ChangeState("DemonicBlade");
		return;
	}

	if (PreStateName == "DimensionCutter" || PreStateName == "DoubleDimensionCutter")
	{
		if (1.0f <= IdleTime)
		{
			State.ChangeState("DevilEye");
			return;
		}
	}

	if (1.0f <= IdleTime && PreStateName == "DevilEye")
	{
		// 이동 하고 블레이드!
		if (MoveVectorPos.X == 702.0f)
		{
			if (LasleyRenderer->GetDir() == EEngineDir::Right)
			{
				MoveBlade = true;
				State.ChangeState("Move");
				return;
			}
		}
		
		if(MoveVectorPos.X == 1150.0f)
		{
			if (LasleyRenderer->GetDir() == EEngineDir::Left)
			{
				MoveBlade = true;
				State.ChangeState("Move");
				return;
			}
		}


		// 제자리에서 블레이드!
		State.ChangeState("DemonicBlade");
		return;
	}

	if (1.0f <= IdleTime && PreStateName == "DemonicBlade")
	{
		State.ChangeState("Move");
		return;
	}

	if (2.0f <= IdleTime && PreStateName == "Wake")
	{
		State.ChangeState("DevilEye");
		return;
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
		// 밑 바닥 까지 체크
		MovePosNum = UEngineRandom::MainRandom.RandomInt(0, 9);
	}
	else
	{
		// 밑 바닥 체크 안함.
		MovePosNum = UEngineRandom::MainRandom.RandomInt(0, 7);
	}
}
void ALasley::MoveTick(float _DeltaTime)
{
	MoveVectorPos = LasleyMovePos[MovePosNum];
	FVector FLasleyPos = GetActorLocation();
	FVector LengV = MoveVectorPos - FLasleyPos;
	FVector MoveDir = LengV.Normalize2DReturn();
	float Leng = std::sqrtf(std::powf(FLasleyPos.X - MoveVectorPos.X, 2) + std::powf(FLasleyPos.Y - MoveVectorPos.Y, 2));

	float4 MoveLasley = MoveDir * MoveSpeed * _DeltaTime;

	AddActorLocation(MoveLasley);

	if (10.0f >= Leng)
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
	ExplosionSoundTime = 0.0f;
}

void ALasley::DevilEyeTick(float _DeltaTime)
{
	// 콜백으로 Tentacle 소환
	if (false == b_DoorTentacle)
	{
		LasleyRenderer->SetFrameCallback("LasleyDevilEye", 8, [=]()
			{
				b_DoorTentacle = true;

				Tentacle_Sound.On();
				b_TentacleSound = true;
			});
	}
	else
	{
		LasleyRenderer->SetFrameCallback("LasleyDevilEye", 8, [=]()
			{
				Tentacle_Sound.On();
				b_TentacleSound = true;
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
				else if (2 == Life) ////
				{
					size_t SummonCount = TentacleSummonPos[9].size();
					for (size_t i = 0; i < SummonCount; i++)
					{
						std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
						Tentacle->SetCreatePos(TentacleSummonPos[9][i]);
						Tentacle->SetInfinity(false);
						Tentacle->CreateTentacle();
					}
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
						size_t SummonCout = TentacleSummonPos[CreatePos_1].size();
						for (size_t i = 0; i < SummonCout; i++)
						{
							std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
							Tentacle->SetCreatePos(TentacleSummonPos[CreatePos_1][i]);
							Tentacle->SetInfinity(false);
							Tentacle->CreateTentacle();
						}
					}
					{
						size_t SummonCout = TentacleSummonPos[CreatePos_1].size();
						for (size_t i = 0; i < SummonCout; i++)
						{
							std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
							Tentacle->SetCreatePos(TentacleSummonPos[CreatePos_2][i]);
							Tentacle->SetInfinity(false);
							Tentacle->CreateTentacle();
						}
					}
					{
						int CreatePos = UEngineRandom::MainRandom.RandomInt(7, 8);
						size_t SummonCout = TentacleSummonPos[CreatePos].size();
						for (size_t i = 0; i < SummonCout; i++)
						{
							std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
							Tentacle->SetCreatePos(TentacleSummonPos[CreatePos][i]);
							Tentacle->SetInfinity(false);
							Tentacle->CreateTentacle();
						}
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

	// 마지막 중앙 불꽃
	if (1.0f <= DoorTentacleTime && 6 == DoorTentacleCount_2)
	{
		std::shared_ptr<ATentacle> Tentacle = GetWorld()->SpawnActor<ATentacle>("Tentacle");
		Tentacle->SetCreatePos(TentacleSummonPos[2][0]);
		Tentacle->SetInfinity(true);
		Tentacle->CreateTentacle();

		DoorTentacles.push_back(Tentacle);

		DoorTentacleCount_2++;

		DoorTentacleTime = 0.0f;
		//b_DoorTentacle = false;
	}
}
#pragma endregion

// 부활.
#pragma region Wake 
void ALasley::WakeBegin()
{
	LasleyRenderer->ChangeAnimation("Wake");
	LasleyRenderer->SetPivot(EPivot::BOT);
	if (Hp <= 0)
	{
		Hp = MaxHp; // 피 회복.
	}
	Life--;
}

void ALasley::WakeTick(float _DeltaTime)
{
	if (true == LasleyRenderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
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
	PreStateName = "Wake";
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
	// Large 값 적용.
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
	MoveBlade = false;
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
			Cutter_Sound.On();
			b_CutterSound = true;

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
			Cutter_Sound.On();
			b_CutterSound = true;
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
			DoubleCutter_Sound.On();
			b_DoubleCutterSound = true;
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
	DemonSwordVector = FVector::Zero;

	if (false == LasleyDemonSword->IsActive())
	{
		LasleyDemonSword->SetActive(true);
	}
}

void ALasley::DownTick(float _DeltaTime)
{
	DownTime += _DeltaTime;

	// 무기 날아감.
	if(false == MoveOne)
	{
		float DemonSwordMoveSpeed = 700.0f;
		FVector RotSpeed = FVector(0.0f, 0.0f, 100.0f);
		FVector Dir = FVector::Zero;
		if (EEngineDir::Left == LasleyRenderer->GetDir())
		{
			Dir = FVector::Right;
		}
		else
		{
			Dir = FVector::Left;
		}

		DemonSwordVector = Dir * DemonSwordMoveSpeed * _DeltaTime;

		LasleyDemonSword->AddRotationDeg(RotSpeed);
		LasleyDemonSword->AddPosition(DemonSwordVector);


		float DemonSwordLen = LasleyDemonSword->GetLocalPosition().X;
		if (1080.0f <= DemonSwordLen)
		{
			MoveOne = true;
		}
		else if(-1080.0f >= DemonSwordLen)
		{
			MoveOne = true;
		}
	}

	
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

	// 모든 워록들이 다 죽으면,
	if (0 != WarlockCount)
	{
		if (true == Warlocks[0]->IsDestroy() &&
			true == Warlocks[1]->IsDestroy() &&
			true == Warlocks[2]->IsDestroy() &&
			true == Warlocks[3]->IsDestroy())
		{
			// 무기 되돌아 옴.
			FVector RotSpeed = FVector(0.0f, 0.0f, 100.0f);
			LasleyDemonSword->AddRotationDeg(RotSpeed);
			LasleyDemonSword->AddPosition(-DemonSwordVector);
			float DemonSwordLen = LasleyDemonSword->GetLocalPosition().X;
			if (0.0f >= DemonSwordLen)
			{
				LasleyDemonSword->SetRotationDeg(FVector(0.0f, 0.0f, 0.0f));
				LasleyDemonSword->SetPosition(FVector(0.0f, 0.0f, 0.0f));
				LasleyDemonSword->SetActive(false);
			
				State.ChangeState("Wake");
				return;
			}
		}
	}

#ifdef _DEBUG
	{
		FVector FLasleyPos = GetActorLocation();
		float DemonSwordLen = LasleyDemonSword->GetLocalPosition().X;
		std::string LasleyState = "Lasley Down";
		std::string LasleyPos = std::format("Lasley Pos {}\n", FLasleyPos.ToString());
		std::string str_DemonSwordLen = std::format("Sword Len : {}\n", DemonSwordLen);

		LasleyStageGUI::PushMsg(LasleyState);
		LasleyStageGUI::PushMsg(LasleyPos);
		LasleyStageGUI::PushMsg(str_DemonSwordLen);
	}
#endif
}
void ALasley::DownExit()
{
	WarlockCount = 0;
	DownTime = 0.0f;
	Warlocks.clear();
	
}
#pragma endregion

#pragma region Die
void ALasley::DieBegin()
{
	LasleyRenderer->ChangeAnimation("Down");
	LasleyRenderer->SetPivot(EPivot::BOT);

	if (0 != DoorTentacles.size())
	{
		size_t x = DoorTentacles.size();
		for (size_t i = 0; i < x; i++)
		{
			DoorTentacles[i]->Destroy();
		}
		DoorTentacles.clear();
	}
}

void ALasley::DieTick(float _DeltaTime)
{
	DieTime += _DeltaTime;

	// Down 과 똑같이 무기 날리고.
	if (false == DieOne)
	{
		float DemonSwordMoveSpeed = 700.0f;
		FVector RotSpeed = FVector(0.0f, 0.0f, 100.0f);
		FVector Dir = FVector::Zero;
		if (EEngineDir::Left == LasleyRenderer->GetDir())
		{
			Dir = FVector::Right;
		}
		else
		{
			Dir = FVector::Left;
		}

		DemonSwordVector = Dir * DemonSwordMoveSpeed * _DeltaTime;

		LasleyDemonSword->AddRotationDeg(RotSpeed);
		LasleyDemonSword->AddPosition(DemonSwordVector);


		float DemonSwordLen = LasleyDemonSword->GetLocalPosition().X;
		if (1080.0f <= DemonSwordLen)
		{
			DieOne = true;
		}
		else if (-1080.0f >= DemonSwordLen)
		{
			DieOne = true;
		}
	}


	if (3.0f <= DieTime)
	{
		std::string str = "Clear!!!!";
		// Levle 에서 작업 진행.
	}
}
#pragma endregion

void ALasley::CollisionCheck(float _DeltaTime)
{
	LasleyCollision->CollisionEnter(ECollisionOrder::WeaponFX, [=](std::shared_ptr<UCollision> _Collision)
		{
			ACosmosSwordFX* CosmosSword = dynamic_cast<ACosmosSwordFX*>(_Collision->GetActor());
			if (nullptr == CosmosSword)
			{
				return;
			}
			int Damage = CosmosSword->GetSwordDamage();
			Widget->RecvHit(true, MaxHp, Damage);

			if (0 >= Hp)
			{
				Hp = 0;
			}
			else
			{
				Hp -= Damage;
			}

			if (0 != Life && 0 >= Hp)
			{
				State.ChangeState("Down");
				return;
			}

			if (0 == Life && 0 >= Hp)
			{
				State.ChangeState("Die");
				return;
			}
		}
	);
}

void ALasley::SoundCheck(float _DeltaTime)
{
	if (true == b_ExplosionSound)
	{
		ExplosionSoundTime += _DeltaTime;
		if (1.8f <= ExplosionSoundTime)
		{
			Explosion_Sound.Off();
			Explosion_Sound.Replay();
			b_ExplosionSound = false;
			ExplosionSoundTime = 0.0f;
		}
	}

	if (true == b_TentacleSound)
	{
		DevilEyeSoundTime += _DeltaTime;
		if (0.7f <= DevilEyeSoundTime)
		{
			Tentacle_Sound.Off();
			Tentacle_Sound.Replay();
			b_TentacleSound = false;
			DevilEyeSoundTime = 0.0f;
		}
	}

	if (true == b_CutterSound)
	{
		CutterSoundTime += _DeltaTime;
		if (0.7f <= CutterSoundTime)
		{
			Cutter_Sound.Off();
			Cutter_Sound.Replay();
			b_CutterSound = false;
			CutterSoundTime = 0.0f;
		}
	}

	if (true == b_DoubleCutterSound)
	{
		DoubleCutterSoundTime += _DeltaTime;
		if (0.7f <= DoubleCutterSoundTime)
		{
			DoubleCutter_Sound.Off();
			DoubleCutter_Sound.Replay();
			b_DoubleCutterSound = false;
			DoubleCutterSoundTime = 0.0f;
		}
	}
}