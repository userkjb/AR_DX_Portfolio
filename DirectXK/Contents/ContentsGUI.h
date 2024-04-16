#pragma once
#include <EngineCore/EngineEditorWindow.h>

/// <summary>
/// 내가 만드는 게임 전반에서 사용할 GUI
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

