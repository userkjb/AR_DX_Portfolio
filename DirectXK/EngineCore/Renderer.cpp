#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// ����� �Ѵ�/
	// GetWorld()->PushRenderer();

}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	int a = 0;
}