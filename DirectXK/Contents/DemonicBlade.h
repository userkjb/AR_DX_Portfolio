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

	inline void SetLasleyDir(EEngineDir _Dir)
	{
		Dir = _Dir;
	}

	inline void SetDemonicBladeActive(bool _Active)
	{
		DemonicBladeRenderer->SetActive(_Active);
	}

	inline void SetDemonicBladeStart()
	{
		State.ChangeState("Create");
	}

	inline void SetDemonicBladePos(FVector _Pos)
	{
		StartPos = _Pos;
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

	void CollisionCheck(float _DeltaTime);

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* DemonicBladeRenderer = nullptr;
	UCollision* DemonicBladeCollision = nullptr;
	UStateManager State;
	EEngineDir Dir = EEngineDir::MAX;
	FVector StartPos = FVector::Zero;
	bool Lasley_Large = false;
};

