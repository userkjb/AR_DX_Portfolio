#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

void APlayer::StateInit()
{
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Jumping");
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
	State.SetFunction("Jumping",
		std::bind(&APlayer::JumpingBegin, this),
		std::bind(&APlayer::JumpingTick, this, std::placeholders::_1),
		std::bind(&APlayer::JumpingEnd, this));
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
	// 플레이어 좌우 변경.
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
	ActorState = EPlayerState::Idle;
}

void APlayer::IdleTick(float _DeltaTime)
{
	{
		PlayerMouseDir(); // 캐릭터 좌우.
		Gravity(_DeltaTime); // 중력.
		PixelCheck(_DeltaTime);// 중력에 대한 픽셀 충돌.

		CalVector(); // Vector 최종 계산
		CalMoveVector(_DeltaTime); // 움직이기.
	}
	
	if (true == IsPress('A') || true == IsPress('D'))
	{
		State.ChangeState("Run");
		return;
	}

	// 게임에서 2개의 키를 받음
	if (true == IsDown(VK_SPACE) || true == IsDown('W'))
	{
		// 점프
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON) && DashCount != 0)
	{
		// 대쉬
		//State.ChangeState("Dash");
		//return;
	}

	// 하단 이동
	if (true == IsPress('S') && true == IsDown(VK_SPACE))
	{
		//
	}

	//MoveUpdate(_DeltaTime);
}

void APlayer::IdleEnd()
{
	
}
#pragma endregion

#pragma region Run
void APlayer::RunBegin()
{
	PlayerRenderer->ChangeAnimation("Run");
	RunVector = FVector::Zero;
	ActorState = EPlayerState::Run;
}

void APlayer::RunTick(float _DeltaTime)
{
	{
		PlayerMouseDir(); // 캐릭터 좌우.
		Gravity(_DeltaTime); // 중력.
		PixelCheck(_DeltaTime);// 중력에 대한 픽셀 충돌.

		CalVector(); // Vector 최종 계산
		CalMoveVector(_DeltaTime); // 움직이기.
	}

	if (true == IsFree('A') && true == IsFree('D'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress('A'))
	{
		if (true == IsHill)
		{
			if (true == IsWall)
			{
				RunVector = FVector::Zero;
			}
			else
			{
				RunVector = (FVector::Left + FVector::Up) * RunSpeed;
			}
		}
	}
	if (true == IsPress('D'))
	{
		if (true == IsHill)
		{
			if (true == IsWall)
			{
				RunVector = FVector::Zero;
			}
			else
			{
				RunVector = (FVector::Right + FVector::Up) * RunSpeed;
			}
		}
	}

	if (true == IsDown(VK_SPACE) || true == IsDown('W'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON) && DashCount != 0)
	{
		//State.ChangeState("Dash");
		//return;
	}
}

void APlayer::RunEnd()
{
	RunVector = FVector::Zero;
}
#pragma endregion

#pragma region Jump
void APlayer::JumpBegin()
{
	PlayerRenderer->ChangeAnimation("Jump");
	JumpVector = JumpPower;
	ActorState = EPlayerState::Jump;
	JumpTime = 0.0f;
}

void APlayer::JumpTick(float _DeltaTime)
{
	{
		PlayerMouseDir(); // 캐릭터 좌우.
		Gravity(_DeltaTime); // 중력.
		PixelCheck(_DeltaTime);// 중력에 대한 픽셀 충돌.

		CalVector(); // Vector 최종 계산
		CalMoveVector(_DeltaTime); // 움직이기.
	}
	JumpTime += _DeltaTime;

	if (true == IsPress('A'))
	{
		RunVector = FVector::Left * RunSpeed;
	}
	if (true == IsPress('D'))
	{
		RunVector = FVector::Right * RunSpeed;
	}

	if (true == IsUp('A'))
	{
		RunVector = FVector::Zero;
	}
	if (true == IsUp('D'))
	{
		RunVector = FVector::Zero;
	}

	// 0.008
	if (JumpTime >= 0.05f)
	{
		State.ChangeState("Jumping");
		return;
	}
}

void APlayer::JumpEnd()
{
}

#pragma endregion

#pragma region Jumping
void APlayer::JumpingBegin()
{
	PlayerRenderer->ChangeAnimation("Jump");
	JumpVector = JumpPower;
	ActorState = EPlayerState::Jumping;
	JumpTime = 0.0f;
	IsGround = false;
}

void APlayer::JumpingTick(float _DeltaTime)
{
	{
		PlayerMouseDir(); // 캐릭터 좌우.
		Gravity(_DeltaTime); // 중력.
		PixelCheck(_DeltaTime);// 중력에 대한 픽셀 충돌.

		CalVector(); // Vector 최종 계산
		CalMoveVector(_DeltaTime); // 움직이기.
	}

	if (true == IsPress('A'))
	{
		RunVector = FVector::Left * RunSpeed;
	}
	if (true == IsPress('D'))
	{
		RunVector = FVector::Right * RunSpeed;
	}

	if (true == IsUp('A'))
	{
		RunVector = FVector::Zero;
	}
	if (true == IsUp('D'))
	{
		RunVector = FVector::Zero;
	}

	if (true == IsGround)
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::JumpingEnd()
{
	IsGround = false;
}
#pragma endregion

#pragma region Dash
// 잔상 3개.
void APlayer::DashBegin()
{
	DashCount--; // 대쉬 카운터 -1.

	DashDir = PlayerToMouseDir; // 대쉬 방향은 Player기준 마우스 방향.
	PlayerRenderer->ChangeAnimation("Run");

	DashVector = FVector::Zero;
	DashVector = DashDir * DashPower;
	int a = 0;
	ActorState = EPlayerState::Dash;
}

void APlayer::DashTick(float _DeltaTime)
{
	DashTime += _DeltaTime;


	//FVector MoveVector = DashDir * DashPower * _DeltaTime;
	//MoveVector.Z = 0.0f;
	//AddActorLocation(MoveVector);
	DashVector.Z = 0.0f;
	//MoveUpdate(_DeltaTime);
	DashVector = DashVector * DashSlowPower * _DeltaTime;
	

	if (true == IsPress('A') || true == IsPress('D'))
	{
		State.ChangeState("Run");
		return;
	}

	if (DashTime >= 0.5f)
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::DashEnd()
{
	DashTime = 0.0f;
	DashDir = float4::Zero;
	//DashVector = FVector::Zero;
}
#pragma endregion

#pragma region Die
void APlayer::DieBegin()
{
	PlayerRenderer->ChangeAnimation("Die");
	ActorState = EPlayerState::Die;
}

void APlayer::DieTick(float _DeltaTime)
{
}

void APlayer::DieEnd()
{
}
#pragma endregion



//void APlayer::MoveUpdate(float _DeltaTime)
//{
//	Gravity(_DeltaTime); // 중력
//
//
//	CalVector(); // Vector 최종 계산
//
//	CalMoveVector(_DeltaTime); // 움직이기.
//}

void APlayer::CalVector()
{
	CalVectors = FVector::Zero;
	CalVectors += RunVector;
	CalVectors += JumpVector;
	CalVectors += GravityVector;
	CalVectors += DashVector;

	CalVectors + JumpVector;
	CalVectors + DashVector;
}

void APlayer::Gravity(float _DeltaTime)
{
	if (true == GUI_Gravity)
	{
		GravityVector += GravityPower * _DeltaTime;
	
		if(true == IsGround)// 땅에 닿으면,
		{
			GravityVector = FVector::Zero;
		}
	}
}

void APlayer::PixelCheck(float _DeltaTime)
{
	// ALasleyGameMode::LevelStart 에서 MapTex 과 MapTexScale 값을 넣음.
	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;
	if (nullptr == Tex)
	{
		MsgBoxAssert("Col 맵이 nullptr 입니다.");
		return;
	}

	//float Size = UContentsConstValue::AutoSizeValue; // const
	//float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const
	//
	//FVector V_PlayerPos = PlayerPos;
	//V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
	//V_PlayerPos /= Size;

	switch (ActorState)
	{
	case EPlayerState::Idle:
	{
		{
			if (true == TestRenderer_2->IsActive())
			{
				TestRenderer_2->SetActive(false);
			}
		}

		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
		}

		break;
	}
	case EPlayerState::Run:
	{
		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;


		FVector V_PlayerRunPos_1 = FVector::Zero;
		FVector V_PlayerRunPos_2 = FVector::Zero;
		V_PlayerRunPos_1 = V_PlayerPos;
		V_PlayerRunPos_2 = V_PlayerPos;

		if (true == IsPress('A'))
		{
			V_PlayerRunPos_1.X -= 8.0f;
			V_PlayerRunPos_1.Y -= 8.0f;

			V_PlayerRunPos_2.X -= 8.0f;
			V_PlayerRunPos_2.Y -= 1.0f;
		}
		if (true == IsPress('D'))
		{
			V_PlayerRunPos_1.X += 8.0f;
			V_PlayerRunPos_1.Y -= 8.0f;

			V_PlayerRunPos_2.X += 8.0f;
			V_PlayerRunPos_2.Y -= 1.0f;
		}

		Color8Bit PlayerRunColor_1 = Tex->GetColor(V_PlayerRunPos_1, Color8Bit::Black);
		Color8Bit PlayerRunColor_2 = Tex->GetColor(V_PlayerRunPos_2, Color8Bit::Black);

		
		if (PlayerRunColor_1 == Color8Bit::Black)
		{
			IsHill = true;
		}
		else
		{
			IsHill = false;
		}

		if (PlayerRunColor_1 == Color8Bit::Black &&
			PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black || Color == Color8Bit::Blue)
		{
			GravityVector = FVector::Zero;
		}
		break;
	}
	case EPlayerState::Jump:
	{
		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;


		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black) // 공중
		{
			GravityVector = FVector::Zero;
		}

		break;
	}
	case EPlayerState::Jumping:
	{
		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;


		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
			JumpVector = FVector::Zero;
			IsGround = true;
		}

		break;
	}
	default:
	{
		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color != Color8Bit::Black) // 공중
		{
			IsGround = false;
		}
		else // 땅에 닿으면,
		{
			IsGround = true;
		}
		break;
	}
	}
}


void APlayer::CalMoveVector(float _DeltaTime)
{
	AddActorLocation(CalVectors * _DeltaTime);
	int a = 0;
}