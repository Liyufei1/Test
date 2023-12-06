// Fill out your copyright notice in the Description page of Project Settings.


#include "GeelyGameState.h"

void AGeelyGameState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GameState BeginPlay!")));
	
	//Receive StringData from Android
	DataReceivedString.BindUFunction(this, FName("ReceiveAndroidStringData"));
	UAndroidUtilsBPLibrary::RegisterAndroidDataReceivedStringDelegate(DataReceivedString);

	//Receive StringData from native Json file
	ReceiveNativeStringData();
}

void AGeelyGameState::ReceiveAndroidStringData(int32 DataId, FString Key,  FString Data)
{
	TotalObstacle.Empty();
	if (!bIsReceiveAndroidStringData)
	{
		return;
	}
	//String=========>RootJsonObject
	TSharedPtr<FJsonObject> RootJsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Data);
	FJsonSerializer::Deserialize(JsonReader, RootJsonObject);

	//Processing VehNaviPilotNotification1 Data
	HandleVehNaviPilotNotification1Data(RootJsonObject);

	//Processing VehNaviPilotNotification1 Data
	
}

void AGeelyGameState::ReceiveNativeStringData()
{
	TotalObstacle.Empty();
	if (!bIsReceiveNativeStringData)
	{
		return;
	}
	FString Data;
	FFileHelper::LoadFileToString(Data, *Path);
	TSharedPtr<FJsonObject> RootJsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Data);
	FJsonSerializer::Deserialize(JsonReader, RootJsonObject);

	//1.Processing VehNaviPilotNotification1 Data
	HandleVehNaviPilotNotification1Data(RootJsonObject);

	//2.Processing VehNaviPilotNotification2 Data
	

	//3.Processing VehNaviPilotNotification2 Data
	HandleVehNaviPilotNotification3Data(RootJsonObject);
}

//emptyData
void AGeelyGameState::EmptyDynamicMeshTotalData()
{
	DynamicMeshTotalData.BoudrayPoint.Empty();
	DynamicMeshTotalData.BoundaryLine1.Empty();
	DynamicMeshTotalData.BoundaryLine2.Empty();
	DynamicMeshTotalData.BoundaryLine3.Empty();
	DynamicMeshTotalData.BoundaryLine4.Empty();
	DynamicMeshTotalData.CrossWalk1.Empty();
	DynamicMeshTotalData.CrossWalk2.Empty();
	DynamicMeshTotalData.CrossWalk3.Empty();
	DynamicMeshTotalData.CrossWalk4.Empty();
	DynamicMeshTotalData.CrossWalk5.Empty();
	DynamicMeshTotalData.CrossWalk6.Empty();
	DynamicMeshTotalData.PlanningLane.Empty();
	DynamicMeshTotalData.GreenBelt1.Empty();
	DynamicMeshTotalData.GreenBelt2.Empty();
	DynamicMeshTotalData.GreenBelt3.Empty();
	DynamicMeshTotalData.GreenBelt4.Empty();
	DynamicMeshTotalData.GreenBelt5.Empty();
	DynamicMeshTotalData.GreenBelt6.Empty();
	DynamicMeshTotalData.SelfLaneLeft.Empty();
	DynamicMeshTotalData.SelfLaneRight.Empty();
	DynamicMeshTotalData.StopLine1.Empty();
	DynamicMeshTotalData.StopLine2.Empty();
	DynamicMeshTotalData.StopLine3.Empty();
	DynamicMeshTotalData.StopLine4.Empty();
	DynamicMeshTotalData.StopLine5.Empty();
	DynamicMeshTotalData.StopLine6.Empty();
}

void AGeelyGameState::HandleVehNaviPilotNotification1Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification1 = RootJsonObject->GetObjectField("VehNaviPilotNotification1");
	TESTLOG(RootJsonObject,VehNaviPilotNotification1)
	TSharedPtr<FJsonObject> obstacleJsonObject = VehNaviPilotNotification1->GetObjectField("obstacle");
	TESTLOG(VehNaviPilotNotification1, obstacle)
	TArray<TSharedPtr<FJsonValue>> ObstacleArray = obstacleJsonObject->GetArrayField("obstacle");
	//get ObstacleArray if ObstacleArray Not Null
	if (ObstacleArray.IsValidIndex(0))
	{
		for (auto& it : ObstacleArray)
		{
			FObstacle tmpObstacle;
			TSharedPtr<FJsonObject> TargetObstacleJsonObject = it->AsObject();
			////if type == 0 (Not display) ,continue;
			if (TargetObstacleJsonObject->GetNumberField("hmiObjTyp")== 0)
			{
				continue;
			}
			tmpObstacle.id = TargetObstacleJsonObject->GetNumberField("id");
			tmpObstacle.objHeading = TargetObstacleJsonObject->GetNumberField("hdDirOfObj") * 0.1;
			tmpObstacle.objPoint.X = TargetObstacleJsonObject->GetObjectField("objPoint")->GetNumberField("dstLat") * 0.2;
			tmpObstacle.objPoint.Y = TargetObstacleJsonObject->GetObjectField("objPoint")->GetNumberField("dstLgt") * 0.4;
			tmpObstacle.objType = static_cast<EHmiObjType>(TargetObstacleJsonObject->GetNumberField("hmiObjTyp"));
			tmpObstacle.objSpeed = static_cast<ESpdOfMovgObj>(TargetObstacleJsonObject->GetNumberField("spdOfMovgObj"));
			tmpObstacle.objColor = static_cast<EColorOfObj>(TargetObstacleJsonObject->GetNumberField("color"));
			tmpObstacle.ObjLight = static_cast<EHmiObjLight>(TargetObstacleJsonObject->GetNumberField("hmiObjLight"));
			TotalObstacle.Add(tmpObstacle);
		}
	}
}

void AGeelyGameState::HandleVehNaviPilotNotification2Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification2 = RootJsonObject->GetObjectField("VehNaviPilotNotification2");
	TESTLOG(RootJsonObject,ehNaviPilotNotification2)
}

void AGeelyGameState::HandleVehNaviPilotNotification3Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	if (!RootJsonObject.IsValid()) return;
	EthLineArray.Empty();
	TSharedPtr<FJsonObject> VehNaviPilotNotification3 = RootJsonObject->GetObjectField("VehNaviPilotNotification3");
	TESTLOG(RootJsonObject,VehNaviPilotNotification3)
	TSharedPtr<FJsonObject> ethLineLe1 = VehNaviPilotNotification3->GetObjectField("ethLineLe1");
	TESTLOG(VehNaviPilotNotification3, ethLineLe1)
	TSharedPtr<FJsonObject> ethLineLe2 = VehNaviPilotNotification3->GetObjectField("ethLineLe2");
	TESTLOG(VehNaviPilotNotification3, ethLineLe2)
	TSharedPtr<FJsonObject> ethLineRi1 = VehNaviPilotNotification3->GetObjectField("ethLineRi1");
	TESTLOG(VehNaviPilotNotification3, ethLineRi1)
		TSharedPtr<FJsonObject> ethLineRi2 = VehNaviPilotNotification3->GetObjectField("ethLineRi2");
	TESTLOG(VehNaviPilotNotification3, ethLineRi2)
		
	HandleEthLineData(ethLineLe2);
	HandleEthLineData(ethLineLe1);
	HandleEthLineData(ethLineRi1);
	HandleEthLineData(ethLineRi2);
	


}
void AGeelyGameState::HandleEthLineData(TSharedPtr<FJsonObject>& EthLine)
{
	if (!EthLine.IsValid())
	{
		return;
	}
	FEthLine TmpEthLine;
	TmpEthLine.colorOfAsyLine = static_cast<EColorOfAsyLine>(EthLine->GetNumberField("colorOfAsyLine"));
	TmpEthLine.endPoint = EthLine->GetNumberField("endPoint") * 0.4;
	TmpEthLine.startPoint = EthLine->GetNumberField("startPoint") * 0.4;
	//if (!EthLine->HasField("startPoint"))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("===========")));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("JsonName is %f"),TmpEthLine.startPoint ));
	TmpEthLine.prmA = EthLine->GetNumberField("prmA") * 0.2;
	TmpEthLine.prmB = EthLine->GetNumberField("prmB") * 0.1;
	TmpEthLine.prmC = EthLine->GetNumberField("prmC") * 0.01;
	TmpEthLine.prmD = EthLine->GetNumberField("prmD") * 0.0001;
	TmpEthLine.typOfAsyLine = static_cast<ETypOfAsyLine>(EthLine->GetNumberField("typOfAsyLine"));
	TmpEthLine.typOfFishBone = static_cast<ETypOfFishBone>(EthLine->GetNumberField("typOfFishBone"));
	TArray<TSharedPtr<FJsonValue>> linePoints = EthLine->GetArrayField("linePoint");
	for (auto& it : linePoints)
	{
		FVector2D tmppoint;
		tmppoint.X = it->AsObject()->GetNumberField("dstLat") * 0.2;
		tmppoint.Y = it->AsObject()->GetNumberField("dstLgt") * 0.4;
		TmpEthLine.linePoint.Add(tmppoint);
	}


	EthLineArray.Add(TmpEthLine);
}

void AGeelyGameState::HandleVehNaviPilotNotification4Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification4 = RootJsonObject->GetObjectField("VehNaviPilotNotification4");
	TESTLOG(RootJsonObject,VehNaviPilotNotification4)
}
void AGeelyGameState::HandleVehNaviPilotNotification5Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification5 = RootJsonObject->GetObjectField("VehNaviPilotNotification5");
	TESTLOG(RootJsonObject, VehNaviPilotNotification5)
}
void AGeelyGameState::HandleVehNaviPilotNotification6Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification6 = RootJsonObject->GetObjectField("VehNaviPilotNotification6");
	TESTLOG(RootJsonObject, VehNaviPilotNotification6)
}
void AGeelyGameState::HandleVehNaviPilotNotification7Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification7 = RootJsonObject->GetObjectField("VehNaviPilotNotification7");
	TESTLOG(RootJsonObject, VehNaviPilotNotification7)
}
void AGeelyGameState::HandleVehNaviPilotNotification8Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification8 = RootJsonObject->GetObjectField("VehNaviPilotNotification8");
	TESTLOG(RootJsonObject, VehNaviPilotNotification8)
}
void AGeelyGameState::HandleVehNaviPilotNotification9Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification9 = RootJsonObject->GetObjectField("VehNaviPilotNotification9");
	TESTLOG(RootJsonObject, VehNaviPilotNotification9)
}
void AGeelyGameState::HandleVehNaviPilotNotification10Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification10 = RootJsonObject->GetObjectField("VehNaviPilotNotification10");
	TESTLOG(RootJsonObject, VehNaviPilotNotification10)
}
void AGeelyGameState::HandleVehNaviPilotNotification11Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification11 = RootJsonObject->GetObjectField("VehNaviPilotNotification11");
	TESTLOG(RootJsonObject, VehNaviPilotNotification11)
}
void AGeelyGameState::HandleVehNaviPilotNotification12Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification12 = RootJsonObject->GetObjectField("VehNaviPilotNotification12");
	TESTLOG(RootJsonObject, VehNaviPilotNotification12)
}
void AGeelyGameState::HandleVehNaviPilotNotificationStartData(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotificationStart = RootJsonObject->GetObjectField("VehNaviPilotNotificationStart");
	TESTLOG(RootJsonObject, VehNaviPilotNotificationStart)
}
void AGeelyGameState::HandleVehNaviPilotNotificationEndData(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotificationEnd = RootJsonObject->GetObjectField("VehNaviPilotNotificationEnd");
	TESTLOG(RootJsonObject, VehNaviPilotNotificationEnd)
}
