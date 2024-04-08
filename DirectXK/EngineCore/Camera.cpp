#include "PreCompile.h"
#include "Camera.h"
#include "EngineCore.h"

UCamera::UCamera()
{
	InputOn();

	float4 Scale = GEngine->EngineWindow.GetWindowScale();

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
	View.LookToLH(GetActorLocation(), GetActorForwardVector(), GetActorUpVector());

	FVector Scale = GEngine->EngineWindow.GetWindowScale();

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

	if (false == IsFreeCamera && IsDown(Key))
	{
		PrevTransform = GetActorTransform();

		PrevProjectionType = ProjectionType;
		ProjectionType = ECameraType::Perspective;
		IsFreeCamera = true;
		OnlyInput(this);
	}
	else if (true == IsFreeCamera && IsDown(Key))
	{
		SetActorTransform(PrevTransform);
		ProjectionType = PrevProjectionType;
		IsFreeCamera = false;
		OnlyInputStop();
		return;
	}

	if (false == IsFreeCamera)
	{
		return;
	}

	if (true == IsDown('R'))
	{
		switch (ProjectionType)
		{
		case ECameraType::NONE:
			break;
		case ECameraType::Perspective:
			ProjectionType = ECameraType::Orthographic;
			break;
		case ECameraType::Orthographic:
			ProjectionType = ECameraType::Perspective;
			break;
		default:
			break;
		}

	}

	float Speed = FreeCameraMoveSpeed;

	if (true == IsPress(VK_LSHIFT))
	{
		Speed = Speed * 4.0f;
	}



	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == IsPress('Q'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsPress('E'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Forward * _DeltaTime * Speed);
	}

	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::BackWard * _DeltaTime * Speed);
	}

	// �̶����� ȸ���� �ȴ�.
	if (true == IsPress(VK_RBUTTON))
	{
		// 
		float4 Rot = GEngine->EngineWindow.GetScreenMouseDirNormal();
		AddActorRotation({ -Rot.Y, -Rot.X, 0.0f });
	}
}

void UCamera::ViewPortSetting()
{
	GEngine->GetDirectXContext()->RSSetViewports(1, &ViewPort);
}