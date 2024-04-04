#pragma once
#include <map>
#include <string>
#include <memory>
#include <list>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineResources.h>

// #include나 이런걸 사용하더라도 실제로 그 코드가 실행되지 않으면
// 컴파일러가 무시한다.
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
//			MsgBoxAssert("이미 존재하는 리소스를 또 로드하려고 했습니다." + UpperName);
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
//	// 당연히 그 자료형 그대로 쓰고
//	// 텍스처면 텍스처 그대로
//	// 랜더타겟이면 랜더타겟 그대로
//	// 사운드면 사운드 그대로 쓰고 싶을 것이다.
//	static std::map<std::string, std::shared_ptr<UEngineTexture>> NameResources;
//	static std::list<std::shared_ptr<UEngineTexture>> UnNameResources;
//};
//
//// 템플릿일때는 문제가 없습니다.
//// 전역변수는 헤더에 추가할수가 없죠?
//// 템플릿이면 무넺가 해결됩니다.
//// 템플릿 static 변수를 선언하는 방법을 배워야 한다.
//template<typename ResType>
//std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;
//
//// 템플릿 static 변수 선언하는법.
//template<typename ResType>
//std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;

// 설명 :
// 템플릿
// class UEngineTexture : public UEngineResourcesUEngineTexture
// 사용하기나 관리하기가 너무 힘드니까
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

	// 이미지 그 자체.
	// Directx에서는 메모리를 의미하는 핸들
	// 그리고 그런 메모리가 있어야 메모리 수정권한
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx에서는 이미지(메모리) 수정 권한(여기에 그릴수 있는 권한)
	ID3D11RenderTargetView* RTV = nullptr;
	// directx에서 이미지를 쉐이더에 세팅할수 있는 권한.
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

