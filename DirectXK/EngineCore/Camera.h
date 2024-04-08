#pragma once
#include <EngineBase/TransformObject.h>
#include "Actor.h"
#include "EngineEnums.h"

// ���� :
class ULevel;
class UCamera : public AActor
{
	friend ULevel;
	friend URenderer;

public:
	// constrcuter destructer
	UCamera();
	~UCamera();

	// delete Function
	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

	inline void SetNear(float _Value)
	{
		Near = _Value;
	}

	inline void SetFar(float _Value)
	{
		Far = _Value;
	}

	inline FMatrix GetView()
	{
		return View;
	}
	inline FMatrix GetProjection()
	{
		return Projection;
	}

	void ViewPortSetting();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool IsFreeCamera = false;

	float Near = 1.0f;
	float Far = 10000.0f;

	ECameraType ProjectionType = ECameraType::Orthographic;
	float FOV = 60.0f;

	FMatrix View;
	FMatrix Projection;
	D3D11_VIEWPORT ViewPort;

	void CameraTransformUpdate();
};

