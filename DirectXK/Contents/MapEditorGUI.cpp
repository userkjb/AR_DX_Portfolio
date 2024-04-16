#include "PreCompile.h"
#include "MapEditorGUI.h"
#include "TileMapLevel.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EngineCore/Camera.h>


MapEditorGUI::MapEditorGUI()
{

}

MapEditorGUI::~MapEditorGUI()
{
}

void MapEditorGUI::Init()
{
}

void MapEditorGUI::Tick(ULevel* _Level, float _DeltaTime)
{
	Super::Tick(_Level, _DeltaTime);
	// 카메라.
	/*{
		_Level->GetMainCamera();
		float Speed = 500.0f;
		if (true == UEngineInput::IsPress('A'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Left * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('D'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Right * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('W'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Up * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('S'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Down * _DeltaTime * Speed);
		}
	}*/


	std::string LevelName = _Level->GetName();

	if ("TestGameMode" == _Level->GetName())
	{
		On();
	}
	else
	{
		Off();
	}

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(_Level);
	if (nullptr == Ptr)
	{
		return;
	}
	
	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;

	if (true == UEngineInput::IsPress(VK_LBUTTON))
	{
		float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
		MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

		TileRenderer->SetTile(MousePosWorld, SelectSpriteIndex);
	}
}

void MapEditorGUI::OnGui(ULevel* _Level, float _DeltaTime)
{
	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	//MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	std::shared_ptr<AGameMode> Mode = _Level->GetGameMode();

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(Mode.get());
	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;

	ImGui::InputFloat("TileSizeX", &TileSizeX);
	// ImGui::InputFloat2()

	// 타일 크기 지정
	// 타일 개수 x
	// 타일 개수 y를 
	// 스프라이트 선택.
	// 저장.

	if (true == ImGui::Button("Create"))
	{
		TileRenderer->CreateTileMap("Map4X(64).png", { 64, 64 }, 50, 50, 0);
	}

	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());


	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Map4X(64).png");
	// DX에서 디바이스랑 컨텍스를 넣어줬다.
	// ImGui는 이걸 사용한다.
	// ImGui는 내부에서 자신의 쉐이더를 사용한다.	

	// imgui에서 사용하는 쉐이더에 내 텍스처가 들어간다.
	// ImVec2

	// IMgui는 무조건 char* Event체크를 합니다;
	if (SelectSpriteIndex != -1)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(SelectSpriteIndex);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		ImGui::ImageButton("Select", Info.Texture->GetSRV(), { 100, 100 }, UV0, UV1);
	}
	else
	{
		ImGui::ImageButton("Select", nullptr, { 100, 100 });
	}

	ImGui::BeginChild("TileSelect", { 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);


	for (int i = 0; i < Sprite->GetInfoSize(); i++)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(i);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		std::string Text = std::to_string(i);

		// 줄바꿈을 자동으로 해준다.
		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), { 64, 64 }, UV0, UV1))
		{
			SelectSpriteIndex = i;
		}

		// 줄바꿈
		if ((i + 1) % 5)
		{
			ImGui::SameLine();
		}
	}

	// Index = 내가 찍어야 할 스프라이트니까.
	ImGui::EndChild();
}
