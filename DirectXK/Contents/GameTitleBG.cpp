#include "PreCompile.h"
#include "GameTitleBG.h"

AGameTitleBG::AGameTitleBG()
{
}

AGameTitleBG::~AGameTitleBG()
{
}

void AGameTitleBG::BeginPlay()
{
	Super::BeginPlay();
}

void AGameTitleBG::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	VertexPlus.Y += _DeltaTime;
	//BackGround_Cloud_1->SetVertexUVPlus(VertexPlus);
}
