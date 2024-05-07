#include "PreCompile.h"
#include "ContentsGUI.h"

ContentsGUI::ContentsGUI()
{
}

ContentsGUI::~ContentsGUI()
{
}

void ContentsGUI::Init()
{
}

void ContentsGUI::OnGui(ULevel* _Level, float _Delta)
{
	// 해당 버튼을 누르면 해당 Level로 이동.

	if (true == ImGui::Button("TestGameMode"))
	{
		GEngine->ChangeLevel("TestGameMode");
	}

	if (true == ImGui::Button("TitleLevel"))
	{
		GEngine->ChangeLevel("TitleLevel");
	}

	if (true == ImGui::Button("LasleyLevel"))
	{
		GEngine->ChangeLevel("LasleyLevel");
	}

	if (true == ImGui::Button("LasleyLevelBoss"))
	{
		GEngine->ChangeLevel("LasleyLevelBoss");
	}
}
