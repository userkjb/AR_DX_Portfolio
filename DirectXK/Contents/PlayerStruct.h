#pragma once

struct EPlayerStateValue
{
public:
	static int MaxHp;
	static int Hp;
	static int DashCount;
	static int DashCountMax;
	static int Life;
	static const float DashCountUpTime; // 3√ 
};