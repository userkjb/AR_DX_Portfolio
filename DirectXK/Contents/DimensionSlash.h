#pragma once
#include <EngineCore/Actor.h>
//#include <EngineCore/SpriteRenderer.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class ADimensionSlash : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	ADimensionSlash();
	~ADimensionSlash();

	// delete Function
	ADimensionSlash(const ADimensionSlash& _Other) = delete;
	ADimensionSlash(ADimensionSlash&& _Other) noexcept = delete;
	ADimensionSlash& operator=(const ADimensionSlash& _Other) = delete;
	ADimensionSlash& operator=(ADimensionSlash&& _Other) noexcept = delete;
	
protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void InitState();
	void CreateAnimation();

	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();
	void AttackBegin();
	void AttackTick(float _DeltaTime);
	void AttackExit();

	void FrameCallBack();

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* DimensionSlashRenderer_B = nullptr;
	//USpriteRenderer* DimensionSlashRenderer_F = nullptr;
	//UCollision* SlashCollision = nullptr;
	UStateManager State;

};

