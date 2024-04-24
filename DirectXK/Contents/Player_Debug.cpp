#include "PreCompile.h"
#include "Player.h"


void APlayer::t_DeBugFunction(float _DeltaTime)
{
	FVector T_PlayerPos = PlayerPos;
	FVector PlayerScale = GetActorScale3D();
	float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
	float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);
	FVector ScreenScale = GEngine->EngineWindow.GetWindowScale();
	//CulMousPos.Y -= ScreenScale.Y;
	//CulMousPos.Y *= -1.0f;
	//float4 Leng = CulMousPos - PlayerPos;
	float4 Leng = MousePosWorld - PlayerPos;
	//PlayerToMouseDir = Leng.Normalize3DReturn();
	//FVector TesetRenserLOne = TestRenderer_1->GetLocalPosition();
	//FVector TesetRenserWOne = TestRenderer_1->GetWorldPosition();
	std::string s_IsWall = "";
	std::string s_IsHill = "";
	if (true == IsWall)
		s_IsWall = "Wall : True";
	else
		s_IsWall = "Wall : False";
	if (true == IsHill)
		s_IsHill = "Hill : True";
	else
		s_IsHill = "Hill : False";

	FVector V_PlayerColPos_W = PlayerCollision->GetWorldPosition();
	FVector V_PlayerColPos_L = PlayerCollision->GetLocalPosition();
	



	std::string StateName = State.GetCurStateName(); // 현재 상태.
	//std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
	std::string Player_World_Pos = std::format("Player_World Pos : {}\n", T_PlayerPos.ToString());
	//std::string Msg3 = std::format("Player_World Scale : {}\n", PlayerScale.ToString());
	std::string Msg4 = std::format("Mouses_World Pos : {}\n", MousePosWorld.ToString());
	//std::string Msg5 = std::format("Mouses_World Pos : {}\n", MousePosWorld.ToString());
	//std::string Msg6 = std::format("Leng : {}\n", Leng.ToString());
	//std::string Msg7 = std::format("PlayerToMouseDir : {}\n", PlayerToMouseDir.ToString());
	//std::string Msg8 = std::format("Leng : {}\n", Leng.ToString());
	//std::string Msg9 = std::format("Rot : {}\n", Rot);
	std::string DashCountMsg = std::format("DashCount : {}\n", DashCount);
	std::string CalVectorsMsg = std::format("CalVectors : {}\n", CalVectors.ToString());
	std::string RunVectorMsg = std::format("RunVector : {}\n", RunVector.ToString());
	std::string JumpVectorMsg = std::format("JumpVector : {}\n", JumpVector.ToString());
	std::string GravityVectorMsg = std::format("GravityVector : {}\n", GravityVector.ToString());
	std::string DashVectorMsg = std::format("DashVector : {}\n", DashVector.ToString());
	//std::string T_Render_L = std::format("T_Render_L : {}\n", TesetRenserLOne.ToString());
	//std::string T_Render_W = std::format("T_Render_W : {}\n", TesetRenserWOne.ToString());
	std::string T_PlayerPoint_1 = std::format("T_Render_L1 : {}\n", V_Test_PlayerPoint_1.ToString());
	std::string T_PlayerPoint_2 = std::format("T_Render_L2 : {}\n", V_Test_PlayerPoint_2.ToString());
	std::string str_PlayerCollisionPos_W = std::format("Player Col Pos W : {}\n", V_PlayerColPos_W.ToString());
	std::string str_PlayerCollisionPos_L = std::format("Player Col Pos L : {}\n", V_PlayerColPos_L.ToString());


	UEngineDebugMsgWindow::PushMsg(StateName);
	UEngineDebugMsgWindow::PushMsg(Player_World_Pos);
	//UEngineDebugMsgWindow::PushMsg(Msg2);
	//UEngineDebugMsgWindow::PushMsg(Msg3);
	UEngineDebugMsgWindow::PushMsg(Msg4);
	//UEngineDebugMsgWindow::PushMsg(T_Render_L);
	//UEngineDebugMsgWindow::PushMsg(T_Render_W);
	//UEngineDebugMsgWindow::PushMsg(Msg5);
	//UEngineDebugMsgWindow::PushMsg(Msg6);
	//UEngineDebugMsgWindow::PushMsg(Msg7);
	//UEngineDebugMsgWindow::PushMsg(Msg8);
	//UEngineDebugMsgWindow::PushMsg(Msg9);
	//UEngineDebugMsgWindow::PushMsg(DashCountMsg);
	UEngineDebugMsgWindow::PushMsg(CalVectorsMsg);
	UEngineDebugMsgWindow::PushMsg(s_IsWall);
	UEngineDebugMsgWindow::PushMsg(s_IsHill);
	UEngineDebugMsgWindow::PushMsg(T_PlayerPoint_1);
	UEngineDebugMsgWindow::PushMsg(T_PlayerPoint_2);
	//UEngineDebugMsgWindow::PushMsg(RunVectorMsg);
	//UEngineDebugMsgWindow::PushMsg(JumpVectorMsg);
	//UEngineDebugMsgWindow::PushMsg(GravityVectorMsg);
	//UEngineDebugMsgWindow::PushMsg(DashVectorMsg);
	UEngineDebugMsgWindow::PushMsg(str_PlayerCollisionPos_W);
	UEngineDebugMsgWindow::PushMsg(str_PlayerCollisionPos_L);
}
