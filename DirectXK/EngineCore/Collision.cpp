#include "PreCompile.h"
#include "Collision.h"

UCollision::UCollision()
{
}

UCollision::~UCollision()
{
}

void UCollision::SetCollisionGroup(int _Index)
{
	SetOrder(_Index);
}

void UCollision::BeginPlay()
{
	Super::BeginPlay();
}

