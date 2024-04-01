#include "PreCompile.h"
#include "EngineTime.h"
#include <Windows.h>

UEngineTime::UEngineTime()
{
	TimeCheckStart();
}

UEngineTime::~UEngineTime()
{
}

//typedef union _LARGE_INTEGER {
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } DUMMYSTRUCTNAME;
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } u;
//    LONGLONG QuadPart;
//} LARGE_INTEGER;


void UEngineTime::TimeCheckStart()
{
	// �ʴ� ���� �ִ� ���ε�.
	QueryPerformanceFrequency(&Count);

	QueryPerformanceCounter(&PrevTime);

	dCount = static_cast<double>(Count.QuadPart);
}

float UEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);

	// ���е��� ���̱� ���ؼ� double�� ����Ѵ�.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}