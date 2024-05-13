#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ATownMap : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATownMap();
	~ATownMap();

	// delete Function
	ATownMap(const ATownMap& _Other) = delete;
	ATownMap(ATownMap&& _Other) noexcept = delete;
	ATownMap& operator=(const ATownMap& _Other) = delete;
	ATownMap& operator=(ATownMap&& _Other) noexcept = delete;

	inline void SetIdleTown()
	{
		State.ChangeState("Idle");
		return;
	}

	inline std::string GetTownState() const
	{
		return State.GetCurStateName();
	}

	inline bool GoNextLevel() const
	{
		return IsNextLevel;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateAnimation();
	void StateInit();
	void CollisionCheck(float _DeltaTime);

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();
	void UpBegin();
	void UpTick(float _DeltaTime);
	void UpExit();
	void IngBegin();
	void IngTick(float _DeltaTime);
	void IngExit();
	void DownBegin();
	void DownTick(float _DeltaTime);
	void DownExit();

	UStateManager State;

	USpriteRenderer* MapImage = nullptr;
	USpriteRenderer* MapCol = nullptr;
	USpriteRenderer* DungeonEat = nullptr;
	UCollision* DungeonInCol = nullptr;

	bool IsNextLevel = false;
};

