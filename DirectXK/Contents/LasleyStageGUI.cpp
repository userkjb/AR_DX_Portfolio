#include "PreCompile.h"
#include "LasleyStageGUI.h"
#include "Player.h"
#include "Lasley.h"

std::vector<std::string> LasleyStageGUI::Msg;

LasleyStageGUI::LasleyStageGUI()
{
}

LasleyStageGUI::~LasleyStageGUI()
{
}

void LasleyStageGUI::PushMsg(std::string_view _Msg)
{
	Msg.push_back(_Msg.data());
}

void LasleyStageGUI::Init()
{
}

void LasleyStageGUI::Tick(ULevel* _Level, float _DeltaTime)
{
	Super::Tick(_Level, _DeltaTime);

	std::string LevelName = _Level->GetName();
	if ("LasleyLevel" == LevelName ||
		"LasleyLevelBoss" == LevelName)
	{
		On();
	}
	else
	{
		Off();
	}
}

void LasleyStageGUI::OnGui(ULevel* _Level, float _DeltaTime)
{
	for (size_t i = 0; i < Msg.size(); i++)
	{
		ImGui::Text(Msg[i].c_str());
	}

	Msg.clear();
}
