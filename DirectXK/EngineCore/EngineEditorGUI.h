#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// ���� �浹�ϰڽ��ϴ�.

// Imgui�� ����ϰڴ�.
// ��ư�� �ϳ��� ����� �͵� �Ϲ������δ� �ڵ�� ���� ������� �ϸ�
// ������ ��������� ���Դϴ�.
// �翬�� ���̺귯���� �� �ֽ��ϴ�. window
// imgui�� ���� ��Ƽ�÷��� ��ĭ ���̷�Ʈ9 ���̷�Ʈ11 ���̷�Ʈ12 �̷������� ��Ƽ�÷���
// �ű�� �ڵ差�� ����. �׳� imgui�ڵ带 ������ ���ͼ� ������ �׳� ����־ �������� ����.
// �������� branch�� doking���� �������̴�.

// ���� :
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

