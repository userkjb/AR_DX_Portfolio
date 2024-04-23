#include "PreCompile.h"
#include "Player.h"


void APlayer::t_DeBugFunction(float _DeltaTime)
{
	PlayerPos = GetActorLocation();
	FVector PlayerScale = GetActorScale3D();
	float4 CulMousPos = GEngine->EngineWindow.GetScreenMousePos();
	float4 MousePosWorld = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(CulMousPos);

	FVector ScreenScale = GEngine->EngineWindow.GetWindowScale();
	//CulMousPos.Y -= ScreenScale.Y;
	//CulMousPos.Y *= -1.0f;

	//float4 Leng = CulMousPos - PlayerPos;
	float4 Leng = MousePosWorld - PlayerPos;
	//PlayerToMouseDir = Leng.Normalize3DReturn();

	//float Rot = atan2((MousePosWorld.Y - PlayerPos.Y), (MousePosWorld.X - PlayerPos.X));
	//Rot *= UEngineMath::RToD; // µð±×¸®( 0 ~ 180)
	//WeaponDir.Z = Rot;

	std::string StateName = State.GetCurStateName();
	//std::string Msg1 = std::format("Screen : {}\n", ScreenScale.ToString());
	std::string Msg2 = std::format("Player_World Pos : {}\n", PlayerPos.ToString());
	std::string Msg3 = std::format("Player_World Scale : {}\n", PlayerScale.ToString());
	//std::string Msg4 = std::format("Mouses_World Pos : {}\n", MousePosWorld.ToString());
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

	//UEngineDebugMsgWindow::PushMsg(Msg1);
	UEngineDebugMsgWindow::PushMsg(Msg2);
	UEngineDebugMsgWindow::PushMsg(Msg3);
	//UEngineDebugMsgWindow::PushMsg(Msg4);
	//UEngineDebugMsgWindow::PushMsg(Msg5);
	//UEngineDebugMsgWindow::PushMsg(Msg6);
	//UEngineDebugMsgWindow::PushMsg(Msg7);
	//UEngineDebugMsgWindow::PushMsg(Msg8);
	//UEngineDebugMsgWindow::PushMsg(Msg9);
	UEngineDebugMsgWindow::PushMsg(DashCountMsg);
	UEngineDebugMsgWindow::PushMsg(CalVectorsMsg);
	UEngineDebugMsgWindow::PushMsg(RunVectorMsg);
	UEngineDebugMsgWindow::PushMsg(JumpVectorMsg);
	UEngineDebugMsgWindow::PushMsg(GravityVectorMsg);
	UEngineDebugMsgWindow::PushMsg(DashVectorMsg);
	UEngineDebugMsgWindow::PushMsg(StateName);
}
