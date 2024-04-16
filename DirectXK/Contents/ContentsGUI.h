#pragma once
#include <EngineCore/EngineEditorWindow.h>

/// <summary>
/// ���� ����� ���� ���ݿ��� ����� GUI
/// </summary>
class ContentsGUI : public UEngineEditorWindow
{
public :
	// constrcuter destructer
	ContentsGUI();
	~ContentsGUI();

	// delete Function
	ContentsGUI(const ContentsGUI& _Other) = delete;
	ContentsGUI(ContentsGUI&& _Other) noexcept = delete;
	ContentsGUI& operator=(const ContentsGUI& _Other) = delete;
	ContentsGUI& operator=(ContentsGUI&& _Other) noexcept = delete;

protected :
	virtual void Init();
	virtual void OnGui(ULevel* _Level, float _Delta);

private :
};

