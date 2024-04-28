#pragma once
#include <EngineCore/EngineEditorWindow.h>
#include <vector>

class LasleyStageGUI : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)
public:
	// constrcuter destructer
	LasleyStageGUI();
	~LasleyStageGUI();

	// delete Function
	LasleyStageGUI(const LasleyStageGUI& _Other) = delete;
	LasleyStageGUI(LasleyStageGUI&& _Other) noexcept = delete;
	LasleyStageGUI& operator=(const LasleyStageGUI& _Other) = delete;
	LasleyStageGUI& operator=(LasleyStageGUI&& _Other) noexcept = delete;

	static void PushMsg(std::string_view _Msg);

protected:
	virtual void Init();
	virtual void Tick(ULevel* _Level, float _DeltaTime);
	virtual void OnGui(ULevel* _Level, float _DeltaTime);

	static std::vector<std::string> Msg;
};

