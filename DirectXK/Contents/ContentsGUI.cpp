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
	// �ش� ��ư�� ������ �ش� Level�� �̵�.

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
