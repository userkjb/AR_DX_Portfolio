#include "PreCompile.h"
#include "EngineVertexBuffer.h"
#include "EngineCore.h"

UEngineVertexBuffer::UEngineVertexBuffer()
{
}

UEngineVertexBuffer::~UEngineVertexBuffer()
{
}

void UEngineVertexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	// 다이렉트에서 어떤 메모리를 할당할때 초기값을 넣어주고 싶으면
	// 이걸로 넣어줘야 합니다.
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	// 크기
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);
	// 용도
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU에서 접근가능한가?
	BufferInfo.CPUAccessFlags = 0;
	// 어디저장할거야?
	// D3D11_USAGE_DEFAULT 그래픽카드에 저장해죠.
	// D3D11_USAGE_DYNAMIC 일단 그래픽카드 만약 없으면 Ram
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;


	// CreateVertexBuffer 같은 함수가 아라
	// 버퍼계열은 아래의 함수로 통일
	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}