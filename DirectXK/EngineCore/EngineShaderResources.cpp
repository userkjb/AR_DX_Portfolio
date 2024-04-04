#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"
#include "EngineTexture.h"
#include "EngineSampler.h"

/// UEngineConstantBufferSetter
void UEngineConstantBufferSetter::Setting()
{
	// 상수버퍼를 세팅한다.

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + " 상수버퍼에 세팅을 해주지 않았습니다. 해주세요...");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}

///

void UEngineShaderResources::ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode)
{
	// std::string_view _EntryName <= 무슨 쉐이더에 무슨 리소스가 있는지 확인하려고

	if (nullptr == _ShaderCode)
	{
		MsgBoxAssert("컴파일이 실패한 쉐이더에서 리소스 체크를 하려고 했습니다");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	// 다이렉트 x가 자동검색 기능과 함수를 제공해줍니다.
	// 우린 이용하기만 하면 됩니다.

	// Reflection <= 많이 보렉 될것이다.
	// 컴파일후 결과물을 말합니다. 프로그래밍에서

	ID3D11ShaderReflection* CompileInfo = nullptr;

	// 쉐이더의 컴파일된 내용을 분석후 정보화 해서 우리에게 제공합니다.
	if (S_OK != D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 정보수집에 실패했습니다");
		return;
	}

	D3D11_SHADER_DESC Info = {};

	CompileInfo->GetDesc(&Info);


	// Info.BoundResources 쉐이더 안에서 사용한 총 리소스 개수
	// 전부다 합쳐서 입니다.
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC ResDesc;

		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = UEngineString::ToUpper(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 상수버퍼의 세세한 정보를 알려줘
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			_EntryName;

			// 상수버퍼는 이름이 중요한게 아니라
			// 바이트가 중요해.
			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);

			UEngineConstantBufferSetter& NewSetter = ConstantBuffers[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;
			NewSetter.Res = Buffer;
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			ResDesc.Name;
			UEngineTextureSetter& NewSetter = Textures[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			ResDesc.Name;
			UEngineSamplerSetter& NewSetter = Samplers[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		default:
			MsgBoxAssert("처리할수 없는 타입입니다.");
			break;
		}


		int a = 0;
	}

	CompileInfo->Release();

	int a = 0;
}

void UEngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (false == ResMap.contains(UpperName))
		{
			continue;
		}

		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (Setter.BufferSize != _Size)
		{
			MsgBoxAssert(Setter.Res->GetName() + "의 바이트 크기가 다릅니다." + std::to_string(Setter.BufferSize) + " Vs " + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return true;
		}
	}

	return false;
}

void UEngineShaderResources::SettingAllShaderResources()
{
	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineConstantBufferSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

}

void UEngineShaderResources::SettingTexture(std::string_view _TexName, std::string_view _ImageName, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = UEngineTexture::FindRes(_ImageName);
	std::shared_ptr<UEngineSampler> FindSampler = UEngineSampler::FindRes(_SamperName);

	if (nullptr == FindTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == FindSampler)
	{
		MsgBoxAssert("존재하지 않는 샘플러를 세팅하려고 했습니다.");
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_TexName);
	std::string SmpUpperName = UpperName + "_Sampler";

	for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>>& Pair : Textures)
	{
		std::map<std::string, UEngineTextureSetter>& TexMap = Pair.second;
		std::map<std::string, UEngineSamplerSetter>& SmpMap = Samplers[Pair.first];

		// 샘플러와 텍스처가 한쌍이 아니면 세팅자체를 하지 않는구조 
		if (false == TexMap.contains(UpperName))
		{
			continue;
		}

		if (false == SmpMap.contains(SmpUpperName))
		{
			MsgBoxAssert("텍스처와 한쌍인 샘플러가 존재하지 않습니다");
			continue;
		}

		UEngineTextureSetter& TexSetter = TexMap[UpperName];
		UEngineSamplerSetter& SmpSetter = SmpMap[UpperName];

		TexSetter.Res = FindTexture;
		SmpSetter.Res = FindSampler;
	}
}