#pragma once
#include <EngineCore/Actor.h>

class ABird : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABird();
	~ABird();

	// delete Function
	ABird(const ABird& _Other) = delete;
	ABird(ABird&& _Other) noexcept = delete;
	ABird& operator=(const ABird& _Other) = delete;
	ABird& operator=(ABird&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};

