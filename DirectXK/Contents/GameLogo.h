#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class AGameLogo : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	AGameLogo();
	~AGameLogo();

	// delete Function
	AGameLogo(const AGameLogo& _Other) = delete;
	AGameLogo(AGameLogo&& _Other) noexcept = delete;
	AGameLogo& operator=(const AGameLogo& _Other) = delete;
	AGameLogo& operator=(AGameLogo&& _Other) noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	USpriteRenderer* LogoRenderer = nullptr;
};

