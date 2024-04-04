#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
	Renderer->SetMesh("Rect");
	// ���׸����� ���ִ¼���
	// ���׸����� �ȿ� ���ؽ����̴��� �ȼ����̴��� �Ѵ� ��� ����.
	// ����  ��Ƽ�������ü�� �������ش�.
	// 
	Renderer->SetMaterial("2DImage");

	// Renderer->�����ȼ����̴��������();
	// Renderer->���ù��ؽ����̴��������();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(100.0f, 300.0f, 100.0f));

	// �����ָ� �������Ѵ�.
	Renderer->Resources->SettingConstantBuffer("OutPutColor", Color);
	// ���ο��� ���÷��� ���� ã��
	// Renderer->Resources->SettingTexture("Image", "AAAA.png", "POINT");
}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD1))
	{
		Color.X += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD2))
	{
		Color.X -= _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD4))
	{
		Color.Y += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD5))
	{
		Color.Y -= _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD7))
	{
		Color.Z += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD8))
	{
		Color.Z -= _DeltaTime;
	}

	// Renderer->SetConstanctBuffer("Ftransform", GetTransform());


}