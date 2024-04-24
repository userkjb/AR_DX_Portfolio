#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

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

		// 둘 다 Black 이면 벽.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}

		// 몸통 Point 가 Black 이 아니고
		// 바닥 Point 만 Black 인 경우.
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

		// 둘 다 Black 이면 벽.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}


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

		// 둘 다 Black 이면 벽.
		if (PlayerRunColor_1 == Color8Bit::Black && PlayerRunColor_2 == Color8Bit::Black)
		{
			IsWall = true;
		}
		else
		{
			IsWall = false;
		}


		Color8Bit Color = Tex->GetColor(V_PlayerPos, Color8Bit::Black);
		if (Color == Color8Bit::Black || Color == Color8Bit::Red || Color == Color8Bit::Magenta)
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