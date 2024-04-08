#include "PreCompile.h"
#include "Camera.h"
#include "EngineCore.h"

UCamera::UCamera()
{
	InputOn();

	float4 Scale = GEngine->GetWindowScale();

	ViewPort.Width = Scale.X;
	ViewPort.Height = Scale.Y;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
}

UCamera::~UCamera()
{
}

void UCamera::CameraTransformUpdate()
{
	// 뷰행렬 만들어짐
	View.View(GetActorLocation(), GetActorForwardVector(), GetActorUpVector());

	FVector Scale = GEngine->GetWindowScale();

	switch (ProjectionType)
	{
	case ECameraType::NONE:
		break;
	case ECameraType::Perspective:
		Projection.PerspectiveFovDeg(FOV, Scale.X, Scale.Y, Near, Far);
		break;
	case ECameraType::Orthographic:
		Projection.OrthographicLH(Scale.X, Scale.Y, Near, Far);
		break;
	default:
		break;
	}

}

void UCamera::BeginPlay()
{

}

// 프리카메라가 되면
// 다른애들은 안움직여야 한다.
// 애니메이션도 안되야 하나요?
void UCamera::Tick(float _DeltaTime)
{
	// tick은 그냥 진행된다.
	// 그런데 입력은 카메라만 받아야 한다.
	// IsDown()

	int Key = GEngine->GetEngineOption().FreeCameraKey;

	if (IsDown(Key))
	{
		IsFreeCamera = true;
	}

	if (false == IsFreeCamera)
	{
		return;
	}

	int a = 0;
}

void UCamera::ViewPortSetting()
{
	GEngine->GetDirectXContext()->RSSetViewports(1, &ViewPort);
}