#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

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

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 상수버퍼의 세세한 정보를 알려줘
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			// 상수버퍼는 이름이 중요한게 아니라
			// 바이트가 중요해.
			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);


			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		default:
			MsgBoxAssert("처리할수 없는 타입입니다.");
			break;
		}
		int a = 0;
	}
	CompileInfo->Release();

	int a = 0;
}
