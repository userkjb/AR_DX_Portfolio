#include "PreCompile.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
{
}

USceneComponent::~USceneComponent()
{
}

void USceneComponent::SetupAttachment(USceneComponent* _Parent)
{
	SetParent(_Parent);
}

bool USceneComponent::IsActive()
{
	if (false == UActorComponent::IsActive())
	{
		return false;
	}

	if (nullptr != Parent)
	{
		USceneComponent* ParentPtr = dynamic_cast<USceneComponent*>(Parent);

		if (false == ParentPtr->IsActive())
		{
			return false;
		}
	}


	return UActorComponent::IsActive();
}