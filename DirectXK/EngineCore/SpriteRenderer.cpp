#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "EngineShaderResources.h"
#include "EngineSprite.h"

struct FCuttingData
{
	//       0, 0
	float4 CuttingPosition;
	//      0.5 0.5
	float4 CuttingSize;
};

USpriteRenderer::USpriteRenderer()
{
	SetMesh("Rect");
	SetMaterial("2DImage");
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	CurTexture = nullptr;
	Resources->SettingConstantBuffer("ResultColorValue", PlusColor);
}


USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::SetSprite(std::string_view _Name, UINT _Index/* = 0*/)
{
	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� �������ַ��� �߽��ϴ�.");
		return;
	}

	FSpriteInfo Info = Sprite->GetSpriteInfo(_Index);

	CurTexture = Info.Texture;
	Resources->SettingTexture("Image", Info.Texture, "POINT");
}

void USpriteRenderer::SetSamplering(ETextureSampling _Value)
{
	if (nullptr == CurTexture)
	{
		MsgBoxAssert("�ؽ�ó�� �������� ���� ���¿��� ���ø����� �ٲܼ��� �����ϴ�.");
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