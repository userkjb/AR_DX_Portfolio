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
	
	if (true == IsPress('A') || true == IsPress('D'))
	{
		State.ChangeState("Run");
		return;
	}

	// ���ӿ��� 2���� Ű�� ����
	if (true == IsDown(VK_SPACE) || true == IsDown('W'))
	{
		// ����
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON) && DashCount != 0)
	{
		// �뽬
		State.ChangeState("Dash");
		return;
	}

	// �ϴ� �̵�
	if (true == IsPress('S') && true == IsDown(VK_SPACE))
	{
		//
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

	if (true == IsDown(VK_SPACE) || true == IsDown('W'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON) && DashCount != 0)
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

	if (true == IsUp('A'))
	{
		RunVector = FVector::Zero;
	}
	if (true == IsUp('D'))
	{
		RunVector = FVector::Zero;
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
// �ܻ� 3��.
void APlayer::DashBegin()
{
	DashCount--; // �뽬 ī���� -1.
	//DashVector = FVector::Zero;
	DashDir = PlayerToMouseDir; // �뽬 ������ Player���� ���콺 ����.
	PlayerRenderer->ChangeAnimation("Run");
}

void APlayer::DashTick(float _DeltaTime)
{
	DashTime += _DeltaTime;


	FVector MoveVector = DashDir * DashPower * _DeltaTime;
	MoveVector.Z = 0.0f;
	AddActorLocation(MoveVector);
	

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
	Gravity(_DeltaTime); // �߷�


	CalVector(); // Vector ���� ���

	CalMoveVector(_DeltaTime); // �����̱�.
}

void APlayer::CalVector()
{
	CalVectors = FVector::Zero;
	CalVectors += RunVector;
	CalVectors += JumpVector;
	CalVectors += GravityVector;
	//CalVectors += DashVector;

	CalVectors + JumpVector;
}

void APlayer::Gravity(float _DeltaTime)
{
	if (true == GUI_Gravity)
	{
		GravityVector += GravityPower * _DeltaTime;
	
		if(true == IsGround)// ���� ������,
		{
			GravityVector = FVector::Zero;
		}
	}
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	AddActorLocation(CalVectors * _DeltaTime);
}

void APlayer::PixelCheck(float _DeltaTime)
{
	// ALasleyGameMode::LevelStart ���� MapTex �� MapTexScale ���� ����.
	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;
	if (nullptr == Tex)
	{
		MsgBoxAssert("Col ���� nullptr �Դϴ�.");
		return;
	}

	FVector V_PlayerPos = PlayerPos;
	float Size = UContentsConstValue::AutoSizeValue; // const
	float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const
	
	V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
	
	V_PlayerPos /= Size;

	Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
	if (Color != Color8Bit::Black) // ����
	{
		IsGround = false;
	}
	else // ���� ������,
	{
		IsGround = true;
	}
}

