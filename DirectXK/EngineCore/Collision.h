#pragma once
#include "SceneComponent.h"

// ���� :
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

	// �������� �и��� �ϱ� ���ؼ� ���� ���� ������ �Լ��ε��� �̸��� �ٲ㼭 �ٽ� �����.
	// ���� � �׷쿡 ���� �ݸ������� ���ϱ� ���ؼ�
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

