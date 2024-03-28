#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>


// final을 사용하면 이제 ULevel 상속받은 클래스를 만들수가 없어요.

// 설명 :
class AActor;
class AGameMode;
class UEngineCore;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend UEngineCore;
	static bool IsActorConstructer;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	template<typename ActorType>
	void SpawnActor(std::string _Name, int _Order = 0)
	{
		// 이 사이에서만 컴포넌트를 생성할수 있어야 한다.
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		IsActorConstructer = false;
		// 이
		//NewActor->SetWorld(this);
		//NewActor->BeginPlay();

		PushActor(NewActor);

		// Actors[_Order].push_back(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	void ActorInit(std::shared_ptr<AActor> _Actor);
	void PushActor(std::shared_ptr<AActor> _Actor);
};

