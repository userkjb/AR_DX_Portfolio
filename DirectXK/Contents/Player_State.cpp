#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

void APlayer::StateInit()
{
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");
	State.CreateState("Die");

	State.SetFunction("Idle",
		std::bind(&APlayer::IdleBegin, this),
		std::bind(&APlayer::IdleTick, this, std::placeholders::_1),
		std::bind(&APlayer::IdleEnd, this));
	State.SetFunction("Run",
		std::bind(&APlayer::RunBegin, this),
		std::bind(&APlayer::RunTick, this, std::placeholders::_1),
		std::bind(&APlayer::RunEnd, this));
	State.SetFunction("Jump",
		std::bind(&APlayer::JumpBegin, this),
		std::bind(&APlayer::JumpTick, this, std::placeholders::_1),
		std::bind(&APlayer::JumpEnd, this));
	State.SetFunction("Dash",
		std::bind(&APlayer::DashBegin, this),
		std::bind(&APlayer::DashTick, this, std::placeholders::_1),
		std::bind(&APlayer::DashEnd, this));
	State.SetFunction("Die",
		std::bind(&APlayer::DieBegin, this),
		std::bind(&APlayer::DieTick, this, std::placeholders::_1),
		std::bind(&APlayer::DieEnd, this));

	State.ChangeState("Idle");
}

void APlayer::PlayerMouseDir()
{
	if (PlayerToMouseDir.X < 0.0f)
	{
		PlayerRenderer->SetDir(EEngineDir::Left);
		ActorDir = PlayerRenderer->GetDir();
	}
	else
	{
		PlayerRenderer->SetDir(EEngineDir::Right);
		ActorDir = PlayerRenderer->GetDir();
	}
}

#pragma region Idle
void APlayer::IdleBegin()
{
	PlayerRenderer->ChangeAnimation("Idle");
	RunVector = FVector::Zero;
}

void APlayer::IdleTick(float _DeltaTime)
{
	PlayerMouseDir();
	
	if (true == IsDown('A') || true == IsDown('D'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsDown(VK_SPACE))
	{
		// 점프
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_LBUTTON))
	{
		// 공격
		int a = 0;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		// 대쉬
		State.ChangeState("Dash");
		return;
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::IdleEnd()
{
	int a = 0;
}
#pragma endregion

#pragma region Run
void APlayer::RunBegin()
{
	PlayerRenderer->ChangeAnimation("Run");
	RunVector = FVector::Zero;
}

void APlayer::RunTick(float _DeltaTime)
{
	PlayerMouseDir();

	if (true == IsFree('A') && true == IsFree('D'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress('A'))
	{
		RunVector = FVector::Left * RunSpeed;
	}
	if (true == IsPress('D'))
	{
		RunVector = FVector::Right * RunSpeed;
	}

	if (true == IsDown(VK_SPACE))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
		return;
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::RunEnd()
{
}
#pragma endregion

#pragma region Jump
void APlayer::JumpBegin()
{
	PlayerRenderer->ChangeAnimation("Jump");
	JumpVector = JumpPower;
	JumpTime = 0.0f;
}

void APlayer::JumpTick(float _DeltaTime)
{
	JumpTime += _DeltaTime;
	PlayerMouseDir();

	if (true == IsPress('A'))
	{
		RunVector = FVector::Left * RunSpeed;
	}
	if (true == IsPress('D'))
	{
		RunVector = FVector::Right * RunSpeed;
	}

	MoveUpdate(_DeltaTime);	

	if (JumpTime >= 0.1f)
	{
		if (true == IsGround)
		{
			JumpVector = FVector::Zero;

			if (true == IsPress('A') || true == IsPress('D'))
			{
				State.ChangeState("Run");
				return;
			}
			else
			{
				State.ChangeState("Idle");
				return;
			}
		}
	}
}

void APlayer::JumpEnd()
{
}
#pragma endregion

#pragma region Dash
void APlayer::DashBegin()
{
	AddActorLocation(PlayerToMouseDir * DashPower);
	PlayerRenderer->ChangeAnimation("Run");
}

void APlayer::DashTick(float _DeltaTime)
{
	//AddActorLocation(PlayerToMouseDir * DashPower * _DeltaTime);
	
	if (true == IsDown('A') || true == IsDown('D'))
	{
		State.ChangeState("Run");
		return;
	}

	State.ChangeState("Idle");
	return;
}

void APlayer::DashEnd()
{
}
#pragma endregion


#pragma region Die
void APlayer::DieBegin()
{
	PlayerRenderer->ChangeAnimation("Die");
}

void APlayer::DieTick(float _DeltaTime)
{
}

void APlayer::DieEnd()
{
}
#pragma endregion



void APlayer::MoveUpdate(float _DeltaTime)
{
	Gravity(_DeltaTime); // 중력


	CalVector(); // Vector 최종 계산

	CalMoveVector(_DeltaTime); // 움직이기.
}

void APlayer::CalVector()
{
	CalVectors = FVector::Zero;
	CalVectors += RunVector;
	CalVectors += JumpVector;
	CalVectors += GravityVector;

	CalVectors + JumpVector;
}

void APlayer::Gravity(float _DeltaTime)
{
	GravityVector += GravityPower * _DeltaTime;
	
	if(true == IsGround)// 땅에 닿으면,
	{
		GravityVector = FVector::Zero;
	}
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	AddActorLocation(CalVectors * _DeltaTime);
}

void APlayer::PixelCheck(float _DeltaTime)
{
	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;
	if (nullptr == Tex)
	{
		MsgBoxAssert("Col 맵이 nullptr 입니다.");
		return;
	}

	//PlayerPos /= UContentsConstValue::TileSize; 
	PlayerPos.Y = -PlayerPos.Y;

	Color8Bit Color = Tex->GetColor(PlayerPos, Color8Bit::Black);
	if (Color != Color8Bit::Black) // 공중
	{
		IsGround = false;
	}
	else // 땅에 닿으면,
	{
		IsGround = true;
	}
}

