#pragma once
#include <EngineCore/EngineEditorWindow.h>

class MapEditorGUI : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)
public:
	// constrcuter destructer
	MapEditorGUI();
	~MapEditorGUI();

	// delete Function
	MapEditorGUI(const MapEditorGUI& _Other) = delete;
	MapEditorGUI(MapEditorGUI&& _Other) noexcept = delete;
	MapEditorGUI& operator=(const MapEditorGUI& _Other) = delete;
	MapEditorGUI& operator=(MapEditorGUI&& _Other) noexcept = delete;

protected:
	virtual void Init();
	virtual void Tick(ULevel* _Level, float _DeltaTime);
	virtual void OnGui(ULevel* _Level, float _DeltaTime);

private:

	//bool FileExists(const wchar_t* _FileName);
	//void CreateXmlFile(const wchar_t* _FileName);
	//void ReadXmlFile(const std::string_view _FileName);

	bool MapEditorCamera = false;
	float4 MousePosWorld;
	int SelectSpriteIndex = 0;

	std::string ImageFileName = "";

	float4 InputTileSize = float4::Zero;
	int InputHWValue[2] = { 0 };
	std::string Str_CreateImage = "";
	bool IsCreateImage = false;

	char name[128] = "";
};

