#pragma once
#include <Enginecore/Actor.h>

class USpriteRenderer;
class AGameTitleBG : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AGameTitleBG();
	~AGameTitleBG();

	// delete Function
	AGameTitleBG(const AGameTitleBG& _Other) = delete;
	AGameTitleBG(AGameTitleBG&& _Other) noexcept = delete;
	AGameTitleBG& operator=(const AGameTitleBG& _Other) = delete;
	AGameTitleBG& operator=(AGameTitleBG&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateCloud(float _DeltaTime);

	USpriteRenderer* BackGround_Sky = nullptr;
	USpriteRenderer* BackGround_Cloud = nullptr;

	float4 VertexPlus = float4::Zero;
	float CreateCloudTime = 0.0f;
};

