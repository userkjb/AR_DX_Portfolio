#pragma once
#include "Renderer.h"
#include "EngineSprite.h"

struct FCuttingData
{
	//       0, 0
	float4 CuttingPosition;
	//      0.5 0.5
	float4 CuttingSize;
};

class UEngineSprite;
class USpriteAnimation : public UNameObject
{
public:
	std::shared_ptr<UEngineSprite> Sprite;
	std::vector<float> Inter;
	std::vector<int> Frame;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = true;

	void Update(float _DeltaTime);

	FSpriteInfo GetCurSpriteInfo()
	{
		return Sprite->GetSpriteInfo(CurFrame);
	}

	void Reset()
	{
		CurTime = 0.0f;
		CurFrame = 0;
	}
};

// ���� :
class UEngineTexture;
class USpriteRenderer : public URenderer
{
	GENERATED_BODY(URenderer);

public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetPlusColor(float4 _Color);
	void SetSamplering(ETextureSampling _Value);



protected:

private:
	FCuttingData CuttingDataValue;
	float4 PlusColor = float4::Zero;
	std::shared_ptr<UEngineTexture> CurTexture;

};
