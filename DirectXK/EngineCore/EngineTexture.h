#pragma once
#include <map>
#include <string>
#include <memory>
#include <list>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineResources.h>

// #include�� �̷��� ����ϴ��� ������ �� �ڵ尡 ������� ������
// �����Ϸ��� �����Ѵ�.
#include "ThirdParty\DirectXTex\inc\DirectXTex.h"


#include "EngineSampler.h"

//class UEngineResourcesUEngineTexture
//{
//public:
//	// constrcuter destructer
//	UEngineResources() {}
//	~UEngineResources() {}
//
//	// delete Function
//	UEngineResources(const UEngineResources& _Other) = delete;
//	UEngineResources(UEngineResources&& _Other) noexcept = delete;
//	UEngineResources& operator=(const UEngineResources& _Other) = delete;
//	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;
//
//	static std::shared_ptr<UEngineTexture> CreateResName(std::string_view& _Name, std::string_view _Path)
//	{
//		std::string UpperName = UEngineString::ToUpper(_Name);
//
//		std::shared_ptr<UEngineTexture> NewRes = std::make_shared<UEngineTexture>();
//		NewRes->Name = _Name;
//		NewRes->Path = _Path;
//
//		if (true == NameResources.contains(UpperName))
//		{
//			MsgBoxAssert("�̹� �����ϴ� ���ҽ��� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
//		}
//
//		NameResources[UpperName] = NewRes;
//		return NewRes;
//	}
//
//	static std::shared_ptr<UEngineTexture> CreateResUnName()
//	{
//		std::shared_ptr<ResType> NewRes = std::make_shared<UEngineTexture>();
//		UnNameResources.push_back(NewRes);
//		return NewRes;
//	}
//
//
//protected:
//
//private:
//	// �翬�� �� �ڷ��� �״�� ����
//	// �ؽ�ó�� �ؽ�ó �״��
//	// ����Ÿ���̸� ����Ÿ�� �״��
//	// ����� ���� �״�� ���� ���� ���̴�.
//	static std::map<std::string, std::shared_ptr<UEngineTexture>> NameResources;
//	static std::list<std::shared_ptr<UEngineTexture>> UnNameResources;
//};
//
//// ���ø��϶��� ������ �����ϴ�.
//// ���������� ����� �߰��Ҽ��� ����?
//// ���ø��̸� ������ �ذ�˴ϴ�.
//// ���ø� static ������ �����ϴ� ����� ����� �Ѵ�.
//template<typename ResType>
//std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;
//
//// ���ø� static ���� �����ϴ¹�.
//template<typename ResType>
//std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;

// ���� :
// ���ø�
// class UEngineTexture : public UEngineResourcesUEngineTexture
// ����ϱ⳪ �����ϱⰡ �ʹ� ����ϱ�
class UEngineTextureSetter;
class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	friend UEngineTextureSetter;
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->ResCreate(_Texture);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

protected:


private:

	// �̹��� �� ��ü.
	// Directx������ �޸𸮸� �ǹ��ϴ� �ڵ�
	// �׸��� �׷� �޸𸮰� �־�� �޸� ��������
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx������ �̹���(�޸�) ���� ����(���⿡ �׸��� �ִ� ����)
	ID3D11RenderTargetView* RTV = nullptr;
	// directx���� �̹����� ���̴��� �����Ҽ� �ִ� ����.
	ID3D11ShaderResourceView* SRV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	std::shared_ptr<UEngineSampler> Sampler;
	
	void ResCreate(ID3D11Texture2D* _Texture);

	void ResLoad();

	void CreateRenderTargetView();

	void Setting(EShaderType _Type, UINT _Slot);
};

