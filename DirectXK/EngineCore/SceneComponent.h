#pragma once
#include <EngineBase/TransformObject.h>
#include "ActorComponent.h"

// 설명 : 해당 Component가 있어야 위치를 알 수 있다.
class USceneComponent : public UActorComponent, public UTransformObject
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	void SetupAttachment(USceneComponent* _Parent);

	bool IsActive() override;

protected:

private:
	USceneComponent* ComponentParent = nullptr;
};

