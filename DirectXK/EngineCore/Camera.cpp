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
	// ����� �������
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

// ����ī�޶� �Ǹ�
// �ٸ��ֵ��� �ȿ������� �Ѵ�.
// �ִϸ��̼ǵ� �ȵǾ� �ϳ���?
void UCamera::Tick(float _DeltaTime)
{
	// tick�� �׳� ����ȴ�.
	// �׷��� �Է��� ī�޶� �޾ƾ� �Ѵ�.
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