#include "PreCompile.h"
#include "EngineShader.h"

UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
	if (nullptr != ErrorCodeBlob)
	{
		ErrorCodeBlob->Release();
	}

	if (nullptr != ShaderCodeBlob)
	{
		ShaderCodeBlob->Release();
	}
}



void UEngineShader::ShaderResCheck()
{
	Resources.ShaderResourcesCheck(Type, EntryName, ShaderCodeBlob);
}