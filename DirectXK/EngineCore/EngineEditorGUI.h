#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// 내일 충돌하겠습니다.

// Imgui를 사용하겠다.
// 버튼을 하나를 만드는 것도 일반적으로는 코드로 내가 만들려고 하면
// 굉장히 고생스러운 일입니다.
// 당연히 라이브러리가 또 있습니다. window
// imgui의 장점 멀티플랫폼 불칸 다이렉트9 다이렉트11 다이렉트12 이런식으로 멀티플랫폼
// 거기다 코드량이 적다. 그냥 imgui코드를 파일을 들고와서 내꺼에 그냥 집어넣어도 될정도로 적다.
// 선생님은 branch를 doking으로 받을것이다.

// 설명 :
class UEngineCore;
class UEngineEditorGUI
{
	friend UEngineCore;
public:
	// constrcuter destructer
	UEngineEditorGUI();
	~UEngineEditorGUI();

	// delete Function
	UEngineEditorGUI(const UEngineEditorGUI& _Other) = delete;
	UEngineEditorGUI(UEngineEditorGUI&& _Other) noexcept = delete;
	UEngineEditorGUI& operator=(const UEngineEditorGUI& _Other) = delete;
	UEngineEditorGUI& operator=(UEngineEditorGUI&& _Other) noexcept = delete;

protected:

private:
	static void GUIRender(float _DeltaTime);
	static void GUIInit();
	static void GUIRelease();

	static ImGuiIO* IOPtr;

};

