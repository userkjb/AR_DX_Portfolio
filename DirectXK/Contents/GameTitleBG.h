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
	USpriteRenderer* BackGround_Cloud_1 = nullptr;
	USpriteRenderer* BackGround_Cloud_2 = nullptr;

	float4 VertexPlus;
};

