#pragma once
#include "Transform.h"
#include <vector>

// ���� :
class UTransformObject
{
public:
	// constrcuter destructer
	UTransformObject();
	~UTransformObject();

	// delete Function
	UTransformObject(const UTransformObject& _Other) = delete;
	UTransformObject(UTransformObject&& _Other) noexcept = delete;
	UTransformObject& operator=(const UTransformObject& _Other) = delete;
	UTransformObject& operator=(UTransformObject&& _Other) noexcept = delete;

	FTransform Transform;

	void SetParent(UTransformObject* _Parent)
	{
		Parent = _Parent;
		Parent->Childs.push_back(this);
	}

protected:

private:
	UTransformObject* Parent = nullptr;
	std::vector<UTransformObject*> Childs;
};

