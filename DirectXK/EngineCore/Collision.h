#pragma once
#include "SceneComponent.h"

// 설명 :
class UCollision : public USceneComponent, public std::enable_shared_from_this<UCollision>
{
	GENERATED_BODY(USceneComponent)
public:
	// constrcuter destructer
	UCollision();
	~UCollision();

	// delete Function
	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	// 목적성을 분명히 하기 위해서 굳이 같은 수준의 함수인데도 이름만 바꿔서 다시 만든다.
	// 내가 어떤 그룹에 속한 콜리전인지 정하기 위해서
	template<typename EnumType>
	void SetCollisionGroup(EnumType _Index)
	{
		SetCollisionGroup(static_cast<int>(_Index));
	}

	void SetCollisionGroup(int _Index);

protected:
	void BeginPlay() override;

private:
	ECollisionType CollisionType = ECollisionType::CirCle;

};

