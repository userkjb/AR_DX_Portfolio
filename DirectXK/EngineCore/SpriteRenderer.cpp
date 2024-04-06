#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "EngineShaderResources.h"
#include "EngineSprite.h"

void USpriteAnimation::Update(float _DeltaTime)
{
	CurTime += _DeltaTime;

	if (CurTime > Inter[CurFrame])
	{
		CurTime -= Inter[CurFrame];
		++CurFrame;

		if (Frame.size() <= CurFrame)
		{
			if (true == Loop)
			{
				CurFrame = 0;
			}
			else
			{
				--CurFrame;
			}
		}
	}
}

USpriteRenderer::USpriteRenderer()
{
	SetMesh("Rect");
	SetMaterial("2DImage");
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	CurTexture = nullptr;
	Resources->SettingConstantBuffer("ResultColorValue", PlusColor);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);

}


USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::SetSprite(std::string_view _Name, UINT _Index/* = 0*/)
{
	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 세팅해주려고 했습니다.");
		return;
	}

	FSpriteInfo Info = Sprite->GetSpriteInfo(_Index);
	CuttingDataValue.CuttingPosition = Info.CuttingPosition;
	CuttingDataValue.CuttingSize = Info.CuttingSize;
	CurTexture = Info.Texture;
	Resources->SettingTexture("Image", Info.Texture, "POINT");
}

void USpriteRenderer::SetSamplering(ETextureSampling _Value)
{
	if (nullptr == CurTexture)
	{
		MsgBoxAssert("텍스처를 세팅하지 않은 상태에서 샘플링부터 바꿀수는 없습니다.");
		return;
	}

	switch (_Value)
	{
	case ETextureSampling::NONE:
		break;
	case ETextureSampling::LINEAR:
	{
		Resources->SettingTexture("Image", CurTexture, "LINEAR");
		break;
	}
	case ETextureSampling::POINT:
	{
		Resources->SettingTexture("Image", CurTexture, "POINT");
		break;
	}
	default:
		break;
	}


}

void USpriteRenderer::SetPlusColor(float4 _Color)
{
	PlusColor = _Color;
}

void USpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter,
	bool _Loop /*= true*/,
	int _Start /*= -1*/,
	int _End /*= -1*/)
{
	if (_Start > _End)
	{
		MsgBoxAssert("아직 역방향 기능은 지원하지 않습니다.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (nullptr == FindSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들수는 없습니다.");
		return;
	}

	std::vector<int> Frame;
	std::vector<float> Inter;

	int Start = _Start;
	int End = _End;

	if (0 > _Start)
	{
		Start = 0;
		End = static_cast<UINT>(FindSprite->GetInfoSize());
	}

	for (int i = 0; i < End; i++)
	{
		Inter.push_back(_Inter);
		Frame.push_back(i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Inter, Frame, _Loop);
}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 할수 없습니다." + std::string(_AnimationName));
		return;
	}

	CurAnimation = Animations[UpperName];
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<float> _Inter, std::vector<int> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (true == Animations.contains(UpperName))
	{
		MsgBoxAssert("이미 존재하는 이름의 애니메이션은 만들수 없습니다.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (nullptr == FindSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들수는 없습니다.");
		return;
	}

	std::shared_ptr<USpriteAnimation> NewAnimation = std::make_shared<USpriteAnimation>();

	NewAnimation->Sprite = FindSprite;
	NewAnimation->Inter = _Inter;
	NewAnimation->Frame = _Frame;
	NewAnimation->Loop = _Loop;
	NewAnimation->Reset();

	Animations[UpperName] = NewAnimation;
}