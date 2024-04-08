#include "PreCompile.h"
#include "Actor.h"
#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

std::set<AActor*> AActor::InputActors;
std::set<AActor*> AActor::PrevInputActors;

AActor::AActor()
{
	// UEngineInput
	// InputActors.insert(this);
}

AActor::~AActor()
{
}

void AActor::InputOff()
{
	// map같은 경우에는 pair 이터레이터
	// set은 정말 편합니다.
	InputActors.erase(this);
}

void AActor::InputOn()
{
	//std::map<AActor*, int> Test;
	//Test.insert(std::pair<AActor*, int>(this, 10));
	InputActors.insert(this);
}

void AActor::RootCheck()
{
	if (nullptr == RootComponent)
	{
		RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>("UDefaultSceneComponent");
	}
}

void AActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->SetWorld(GetWorld());
		Components[i]->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < Components.size(); i++)
	{
		if (false == Components[i]->IsActive())
		{
			continue;
		}

		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{

	_Component->SetActor(this);
	_Component->SetName(_Name);
	//_Component->BeginPlay();

	Components.push_back(_Component);

	// shared_ptr을 안전하게 다운캐스팅하는 함수
	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);

	if (nullptr == RootComponent && nullptr != SceneComponent)
	{
		// std::shared_ptr을 그냥 포인터로 변경하는 함수
		RootComponent = SceneComponent.get();
	}
}


FTransform& AActor::GetActorTransform()
{
	return RootComponent->Transform;
}

FVector AActor::GetActorForwardVector()
{
	return RootComponent->Transform.GetForward();
}

FVector AActor::GetActorRightVector()
{
	return RootComponent->Transform.GetRight();
}
FVector AActor::GetActorUpVector()
{
	return RootComponent->Transform.GetUp();
}

FVector AActor::GetActorLocation()
{
	return RootComponent->Transform.GetPosition();
}

void AActor::SetActorLocation(FVector _Value)
{
	RootComponent->Transform.SetPosition(_Value);
}

void AActor::SetActorScale3D(FVector _Value)
{
	RootComponent->Transform.SetScale(_Value);
}

void AActor::SetActorRotation(FVector _Value)
{
	RootComponent->Transform.SetRotation(_Value);
}

void AActor::AddActorLocation(FVector _Value)
{
	RootComponent->Transform.AddPosition(_Value);
}

void AActor::AddActorRotation(FVector _Value)
{
	RootComponent->Transform.AddRotation(_Value);
}

void AActor::AddActorScale3D(FVector _Value)
{
	RootComponent->Transform.AddScale(_Value);
}


// 액터에서만 인풋 처리가 가능하게 되었습니다.
bool AActor::IsDoubleClick(int _Key, float _ClickTime)
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsDoubleClick(_Key, _ClickTime);
}

void AActor::OnlyInput(AActor* _this)
{
	PrevInputActors = InputActors;
	InputActors.clear();
	InputActors.insert(_this);
}

void AActor::OnlyInputStop()
{
	InputActors.clear();
	InputActors = PrevInputActors;
}

bool AActor::IsDown(int _Key)
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsDown(_Key);
}

float AActor::GetPressTime(int _Key)
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::GetPressTime(_Key);

}

bool AActor::IsPress(int _Key)
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsPress(_Key);

}

bool AActor::IsUp(int _Key)
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsUp(_Key);

}

bool AActor::IsFree(int _Key) {
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsFree(_Key);

}

bool AActor::IsAnykeyDown() {
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsAnykeyDown();

}

bool AActor::IsAnykeyPress() {
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsAnykeyPress();

}

bool AActor::IsAnykeyUp()
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsAnykeyUp();

}

bool AActor::IsAnykeyFree()
{
	// InputActors 등록된 애들만 입력을 받을수 있다.
	if (false == InputActors.contains(this))
	{
		return false;
	}

	return UEngineInput::IsAnykeyFree();

}