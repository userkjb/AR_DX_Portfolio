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

	if (true == ImGui::Button("PlayerLevel"))
	{
		GEngine->ChangeLevel("LasleyLevel");
	}

	if (true == ImGui::Button("PlayLevel"))
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}
