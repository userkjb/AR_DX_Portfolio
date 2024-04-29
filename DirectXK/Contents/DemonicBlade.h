#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class ADemonicBlade : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ADemonicBlade();
	~ADemonicBlade();

	// delete Function
	ADemonicBlade(const ADemonicBlade& _Other) = delete;
	ADemonicBlade(ADemonicBlade&& _Other) noexcept = delete;
	ADemonicBlade& operator=(const ADemonicBlade& _Other) = delete;
	ADemonicBlade& operator=(ADemonicBlade&& _Other) noexcept = delete;

	/// <summary>
	/// 라슬리 Large 여부.
	/// </summary>
	/// <param name="_Large"></param>
	inline void SetLasleyLarge(bool _Large)
	{
		Lasley_Large = _Large;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void InitState();
	void CreateAnimation();

	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void DisappearBegin();
	void DisappearTick(float _DeltaTime);
	void DisappearExit();

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* DemonicBladeRenderer = nullptr;
	UStateManager State;
	bool Lasley_Large = false;
};

