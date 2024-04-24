#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

void APlayer::PixelCheck(float _DeltaTime)
{
	// ALasleyGameMode::LevelStart ���� MapTex �� MapTexScale ���� ����.
	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;
	if (nullptr == Tex)
	{
		MsgBoxAssert("Col ���� nullptr �Դϴ�.");
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
		//{
		//	if (true == TestRenderer_2->IsActive())
		//	{
		//		TestRenderer_2->SetActive(false);
		//	}
		//}

		float Size = UContentsConstValue::AutoSizeValue; // const
		float4 MapColSize = UContentsConstValue::MapTexScale * Size; // const

		FVector V_PlayerPos = PlayerPos;
		V_PlayerPos.Y = MapColSize.Y - PlayerPos.Y;
		V_PlayerPos /= Size;

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		//if (Color == Color8Bit::Black)
		if (Color == Color8Bit::Black || Color == Color8Bit::Magenta || Color == Color8Bit::Red)
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

#ifdef _DEBUG
		{
			V_Test_PlayerPoint_1 = V_PlayerRunPos_1;
			V_Test_PlayerPoint_2 = V_PlayerRunPos_2;
		}
#endif

		Color8Bit PlayerRunColor_1 = Tex->GetColor(V_PlayerRunPos_1, Color8Bit::Black);
		Color8Bit PlayerRunColor_2 = Tex->GetColor(V_PlayerRunPos_2, Color8Bit::Red);

		// �� �� Black �̸� ��.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}

		// ���� Point �� Black �� �ƴϰ�
		// �ٴ� Point �� Black �� ���.
		if (PlayerRunColor_1 != Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Red)
		{
			IsHill = true;
		}
		else
		{
			IsHill = false;
		}

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black || Color == Color8Bit::Magenta || Color == Color8Bit::Red)
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
		Color8Bit PlayerRunColor_2 = Tex->GetColor(V_PlayerRunPos_2, Color8Bit::Red);

		// �� �� Black �̸� ��.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}


		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black) // ����
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

		FVector V_PlayerHeadPos = FVector::Zero;
		FVector V_PlayerRunPos_1 = FVector::Zero;
		FVector V_PlayerRunPos_2 = FVector::Zero;

		V_PlayerHeadPos = V_PlayerPos;
		V_PlayerRunPos_1 = V_PlayerPos;
		V_PlayerRunPos_2 = V_PlayerPos;

		V_PlayerHeadPos.Y -= 16.0f;
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
		Color8Bit PlayerRunColor_2 = Tex->GetColor(V_PlayerRunPos_2, Color8Bit::Red);

		// �� �� Black �̸� ��.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}

		Color8Bit PlayerHeadColor = Tex->GetColor(V_PlayerHeadPos, Color8Bit::Black);
		if (PlayerHeadColor == Color8Bit::Black)
		{
			JumpVector -= JumpVector;
			//GravityVector = FVector::Zero;
		}

		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black || Color == Color8Bit::Red || Color == Color8Bit::Magenta)
		{
			if (CalVectors.Y <= 0.0f)
			{
				GravityVector = FVector::Zero;
				JumpVector = FVector::Zero;
				IsGround = true;
			}
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
		if (Color != Color8Bit::Black) // ����
		{
			IsGround = false;
		}
		else // ���� ������,
		{
			IsGround = true;
		}
		break;
	}
	}
}