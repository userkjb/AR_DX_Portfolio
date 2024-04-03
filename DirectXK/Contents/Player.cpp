#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");

	Renderer->SetMesh("Rect");
	Renderer->SetMaterial("2DImage");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FTransform& Transform = GetActorTransform();
	Renderer->Resources->SettingConstantBuffer("FTransform", Transform);
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);


}