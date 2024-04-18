#pragma once
#include <EngineBase/TransformObject.h>
#include "RenderUnit.h"
#include "TickObject.h"
#include "EngineStruct.h"

// 여기서 어떻게 할거냐가 중요하다.

// 설명 :

// 자기 자식오브젝트나 이런것들을 추가할수 있습니다.
// 부모자식 관계를 이를수 있어야 한다.

// 화면에 UI처럼 고정되어서 보이는 애들을 랜더링하는 기능이다.
// 일반적으로 이런 UI관련 오브젝트들이 있으면 스크린좌표계를 기준으로 잡는다.
// 그런데 우리는 그냥 일반 액터처럼 하겠습니다.
class ULevel;
class UWidget :
	public UTransformObject,
	public URenderUnit,
	public UWorldObject,
	public UTickObject,
	public UNameObject,
	public std::enable_shared_from_this<UWidget>
{
public:
	GENERATED_BODY(URenderUnit)

	friend ULevel;
	// constrcuter destructer
	UWidget();
	virtual ~UWidget();

	// delete Function
	UWidget(const UWidget& _Other) = delete;
	UWidget(UWidget&& _Other) noexcept = delete;
	UWidget& operator=(const UWidget& _Other) = delete;
	UWidget& operator=(UWidget&& _Other) noexcept = delete;

	void AddToViewPort();

	void SetHover(std::function<void()> _Hover)
	{
		Hover = _Hover;
	}

	void SetDown(std::function<void()> _Down)
	{
		Down = _Down;
	}

	void SetUnHover(std::function<void()> _UnHover)
	{
		UnHover = _UnHover;
	}



protected:
	void MaterialSettingEnd() override;
	void Tick(float _DeltaTime) override;

	void Reset()
	{
		IsHover = false;
	}

private:
	void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);

	bool IsHover = false;

	std::function<void()> UnHover;
	std::function<void()> Hover;
	std::function<void()> Down;
};

