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
	ClearAll();
	if (!bIsReceiveAndroidStringData)
	{
		return;
	}
	//String=========>RootJsonObject
	TSharedPtr<FJsonObject> RootJsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Data);
	FJsonSerializer::Deserialize(JsonReader, RootJsonObject);

	//1.Processing VehNaviPilotNotification1 Data
	HandleVehNaviPilotNotification1Data(RootJsonObject);

	//2.Processing VehNaviPilotNotification2 Data
	HandleVehNaviPilotNotification2Data(RootJsonObject);

	//3.Processing VehNaviPilotNotification3 Data
	HandleVehNaviPilotNotification3Data(RootJsonObject);

	//4.Processing VehNaviPilotNotification4 Data
	HandleVehNaviPilotNotification4Data(RootJsonObject);

	//5.Processing VehNaviPilotNotification5 Data
	HandleVehNaviPilotNotification5Data(RootJsonObject);

	//6.Processing VehNaviPilotNotification6 Data
	HandleVehNaviPilotNotification6Data(RootJsonObject);

	//7.Processing VehNaviPilotNotification7 Data
	HandleVehNaviPilotNotification7Data(RootJsonObject);

	//8.Processing VehNaviPilotNotification8 Data
	HandleVehNaviPilotNotification8Data(RootJsonObject);

	//9.Processing VehNaviPilotNotification9 Data
	HandleVehNaviPilotNotification9Data(RootJsonObject);

	//10.Processing VehNaviPilotNotification10 Data
	HandleVehNaviPilotNotification10Data(RootJsonObject);

	//11.Processing VehNaviPilotNotification11 Data
	HandleVehNaviPilotNotification11Data(RootJsonObject);

	//12.Processing VehNaviPilotNotification12 Data
	HandleVehNaviPilotNotification12Data(RootJsonObject);

	//13.Processing VehNaviPilotNotificationStart Data
	HandleVehNaviPilotNotificationStartData(RootJsonObject);

	//14.Processing VehNaviPilotNotificationEnd Data
	HandleVehNaviPilotNotificationEndData(RootJsonObject);

	UGeelyDraw_GameInstanceSubsystem* UGD = GetGameInstance()->GetSubsystem<UGeelyDraw_GameInstanceSubsystem>();
	UGD->Clear();
	UGD->TotalData = GeelyDrawTotalData;
	UGD->Update();

}

void AGeelyGameState::ReceiveNativeStringData()
{
	TotalObstacle.Empty();
	ClearAll();
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
	HandleVehNaviPilotNotification2Data(RootJsonObject);

	//3.Processing VehNaviPilotNotification3 Data
	HandleVehNaviPilotNotification3Data(RootJsonObject);

	//4.Processing VehNaviPilotNotification4 Data
	HandleVehNaviPilotNotification4Data(RootJsonObject);

	//5.Processing VehNaviPilotNotification5 Data
	HandleVehNaviPilotNotification5Data(RootJsonObject);

	//6.Processing VehNaviPilotNotification6 Data
	HandleVehNaviPilotNotification6Data(RootJsonObject);

	//7.Processing VehNaviPilotNotification7 Data
	HandleVehNaviPilotNotification7Data(RootJsonObject);

	//8.Processing VehNaviPilotNotification8 Data
	HandleVehNaviPilotNotification8Data(RootJsonObject);

	//9.Processing VehNaviPilotNotification9 Data
	HandleVehNaviPilotNotification9Data(RootJsonObject);

	//10.Processing VehNaviPilotNotification10 Data
	HandleVehNaviPilotNotification10Data(RootJsonObject);

	//11.Processing VehNaviPilotNotification11 Data
	HandleVehNaviPilotNotification11Data(RootJsonObject);

	//12.Processing VehNaviPilotNotification12 Data
	HandleVehNaviPilotNotification12Data(RootJsonObject);

	//13.Processing VehNaviPilotNotificationStart Data
	HandleVehNaviPilotNotificationStartData(RootJsonObject);

	//14.Processing VehNaviPilotNotificationEnd Data
	HandleVehNaviPilotNotificationEndData(RootJsonObject);

	UGeelyDraw_GameInstanceSubsystem* UGD = GetGameInstance()->GetSubsystem<UGeelyDraw_GameInstanceSubsystem>();
	UGD->Clear();
	UGD->TotalData = GeelyDrawTotalData;
	UGD->Update();
}

//emptyData
void AGeelyGameState::ClearAll()
{
	TotalObstacle.Empty();
	EmptyDynamicMeshTotalData();
	EthLineArray.Empty();
	RoadArrow.Empty();
	TrfcSign.Empty();
	TrafficLight.Empty();
	
}
void AGeelyGameState::EmptyDynamicMeshTotalData()
{
	GeelyDrawTotalData.BoudrayPoint.Empty();
	GeelyDrawTotalData.BoundaryLine1.Empty();
	GeelyDrawTotalData.BoundaryLine2.Empty();
	GeelyDrawTotalData.BoundaryLine3.Empty();
	GeelyDrawTotalData.BoundaryLine4.Empty();
	GeelyDrawTotalData.BoundaryLine5.Empty();
	GeelyDrawTotalData.BoundaryLine6.Empty();
	GeelyDrawTotalData.BoundaryLine1up.Empty();
	GeelyDrawTotalData.BoundaryLine2up.Empty();
	GeelyDrawTotalData.BoundaryLine3up.Empty();
	GeelyDrawTotalData.BoundaryLine4up.Empty();
	GeelyDrawTotalData.BoundaryLine5up.Empty();
	GeelyDrawTotalData.BoundaryLine6up.Empty();
	GeelyDrawTotalData.CrossWalk1.Empty();
	GeelyDrawTotalData.CrossWalk2.Empty();
	GeelyDrawTotalData.CrossWalk3.Empty();
	GeelyDrawTotalData.CrossWalk4.Empty();
	GeelyDrawTotalData.CrossWalk5.Empty();
	GeelyDrawTotalData.CrossWalk6.Empty();
	GeelyDrawTotalData.PlanningLane.Empty();
	GeelyDrawTotalData.GreenBelt1.Empty();
	GeelyDrawTotalData.GreenBelt2.Empty();
	GeelyDrawTotalData.GreenBelt3.Empty();
	GeelyDrawTotalData.GreenBelt4.Empty();
	GeelyDrawTotalData.GreenBelt5.Empty();
	GeelyDrawTotalData.GreenBelt6.Empty();
	GeelyDrawTotalData.SelfLaneLeft.Empty();
	GeelyDrawTotalData.SelfLaneRight.Empty();
	GeelyDrawTotalData.StopLine1.Empty();
	GeelyDrawTotalData.StopLine2.Empty();
	GeelyDrawTotalData.StopLine3.Empty();
	GeelyDrawTotalData.StopLine4.Empty();
	GeelyDrawTotalData.StopLine5.Empty();
	GeelyDrawTotalData.StopLine6.Empty();
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
			tmpObstacle.objPoint.X = TargetObstacleJsonObject->GetObjectField("objPoint")->GetNumberField("dstLat") * 0.2 -6553.5;
			tmpObstacle.objPoint.Y = TargetObstacleJsonObject->GetObjectField("objPoint")->GetNumberField("dstLgt") * 0.4 -3000;
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
	TESTLOG(RootJsonObject,VehNaviPilotNotification2)

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
	TmpEthLine.endPoint = EthLine->GetNumberField("endPoint") * 0.4 - 3000;
	TmpEthLine.startPoint = EthLine->GetNumberField("startPoint") * 0.4 - 3000;
	TmpEthLine.prmA = EthLine->GetNumberField("prmA") * 0.002 -65.536;
	TmpEthLine.prmB = EthLine->GetNumberField("prmB") * 0.001 - 1.6;
	TmpEthLine.prmC = EthLine->GetNumberField("prmC") * 0.0001 - 1.6;
	TmpEthLine.prmD = EthLine->GetNumberField("prmD") * 0.000001 - 0.001;
	TmpEthLine.typOfAsyLine = static_cast<ETypOfAsyLine>(EthLine->GetNumberField("typOfAsyLine"));
	TmpEthLine.typOfFishBone = static_cast<ETypOfFishBone>(EthLine->GetNumberField("typOfFishBone"));
	TArray<TSharedPtr<FJsonValue>> linePoints = EthLine->GetArrayField("linePoint");
	for (auto& it : linePoints)
	{
		FVector2D tmppoint;
		tmppoint.X = it->AsObject()->GetNumberField("dstLat") * 0.2 - 6553.5;
		tmppoint.Y = it->AsObject()->GetNumberField("dstLgt") * 0.4 - 3000;
		TmpEthLine.linePoint.Add(tmppoint);
	}


	EthLineArray.Add(TmpEthLine);
}

void AGeelyGameState::HandleVehNaviPilotNotification4Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification4 = RootJsonObject->GetObjectField("VehNaviPilotNotification4");
	TESTLOG(RootJsonObject,VehNaviPilotNotification4)
	TSharedPtr<FJsonObject> ethHmiBoundaryLe1 = VehNaviPilotNotification4->GetObjectField("ethHmiBoundaryLe1");
	TESTLOG(VehNaviPilotNotification4, ethHmiBoundaryLe1)
	TSharedPtr<FJsonObject> ethHmiBoundaryRi1 = VehNaviPilotNotification4->GetObjectField("ethHmiBoundaryRi1");
	TESTLOG(VehNaviPilotNotification4, ethHmiBoundaryRi1)
	TSharedPtr<FJsonObject> ethLineLe3 = VehNaviPilotNotification4->GetObjectField("ethLineLe3");
	TESTLOG(VehNaviPilotNotification4, ethLineLe3)
	TSharedPtr<FJsonObject> ethLineRi3 = VehNaviPilotNotification4->GetObjectField("ethLineRi3");
	TESTLOG(VehNaviPilotNotification4, ethLineRi3)

	HandleEthLineData(ethLineLe3);
	HandleEthLineData(ethLineRi3);
	HandleBoundaryLine(ethHmiBoundaryLe1,GeelyDrawTotalData.BoundaryLine1);
	HandleBoundaryLine(ethHmiBoundaryRi1, GeelyDrawTotalData.BoundaryLine2);

}
void AGeelyGameState::HandleBoundaryLine(TSharedPtr<FJsonObject>& BoundaryLine, TArray<FVector>& Line)
{
	TArray<TSharedPtr<FJsonValue>> linePoints = BoundaryLine->GetArrayField("linePoint");
	TESTLOG(BoundaryLine, linePoint)
	GEELYLOG(BoundaryLine, linePoint)
	for (auto& it : linePoints)
	{
		FVector tmppoint;
		tmppoint.X = it->AsObject()->GetNumberField("dstLat") * 0.2 -6553.5;
		tmppoint.Y = it->AsObject()->GetNumberField("dstLgt") * 0.4 - 3000;
		tmppoint.Z = 0;
		Line.Add(tmppoint);
	}
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
	GEELYLOG(RootJsonObject, VehNaviPilotNotification8)
	//FHmiCamView
	TSharedPtr<FJsonObject> ethHmiCamView = VehNaviPilotNotification8->GetObjectField("ethHmiCamView");
	HmiCamView.hmiCamViewY = static_cast<EHmiCamViewY> (ethHmiCamView->GetNumberField("hmiCamViewY"));
	HmiCamView.hmiCamViewZ = static_cast<EHmiCamViewZ> (ethHmiCamView->GetNumberField("hmiCamViewZ"));

	//CrossWalk
	TArray<TSharedPtr<FJsonValue>>  ethHmiCrosswalk = VehNaviPilotNotification8->GetArrayField("ethHmiCrosswalk");
	TESTLOG(VehNaviPilotNotification8, ethHmiCrosswalk)
	GEELYLOG(VehNaviPilotNotification8, ethHmiCrosswalk)
	if (ethHmiCrosswalk.IsValidIndex(0)) HandleCrossWalkData(ethHmiCrosswalk[0]->AsObject(),GeelyDrawTotalData.CrossWalk1 );
	if (ethHmiCrosswalk.IsValidIndex(1)) HandleCrossWalkData(ethHmiCrosswalk[1]->AsObject(), GeelyDrawTotalData.CrossWalk2);
	if (ethHmiCrosswalk.IsValidIndex(2)) HandleCrossWalkData(ethHmiCrosswalk[2]->AsObject(), GeelyDrawTotalData.CrossWalk3);
	if (ethHmiCrosswalk.IsValidIndex(3)) HandleCrossWalkData(ethHmiCrosswalk[3]->AsObject(), GeelyDrawTotalData.CrossWalk4);
	if (ethHmiCrosswalk.IsValidIndex(4)) HandleCrossWalkData(ethHmiCrosswalk[4]->AsObject(), GeelyDrawTotalData.CrossWalk5);
	if (ethHmiCrosswalk.IsValidIndex(5)) HandleCrossWalkData(ethHmiCrosswalk[5]->AsObject(), GeelyDrawTotalData.CrossWalk6);

	//StopLine
	TArray<TSharedPtr<FJsonValue>>  ethHmiStopLine = VehNaviPilotNotification8->GetArrayField("ethHmiStopLine");
	TESTLOG(VehNaviPilotNotification8, ethHmiStopLine)
	GEELYLOG(VehNaviPilotNotification8, ethHmiStopLine)
	if (ethHmiStopLine.IsValidIndex(0)) HandleStopLineData(ethHmiStopLine[0]->AsObject(), GeelyDrawTotalData.StopLine1);
	if (ethHmiStopLine.IsValidIndex(1)) HandleStopLineData(ethHmiStopLine[1]->AsObject(), GeelyDrawTotalData.StopLine2);
	if (ethHmiStopLine.IsValidIndex(2)) HandleStopLineData(ethHmiStopLine[2]->AsObject(), GeelyDrawTotalData.StopLine3);
	if (ethHmiStopLine.IsValidIndex(3)) HandleStopLineData(ethHmiStopLine[3]->AsObject(), GeelyDrawTotalData.StopLine4);
	if (ethHmiStopLine.IsValidIndex(4)) HandleStopLineData(ethHmiStopLine[4]->AsObject(), GeelyDrawTotalData.StopLine5);
	if (ethHmiStopLine.IsValidIndex(5)) HandleStopLineData(ethHmiStopLine[5]->AsObject(), GeelyDrawTotalData.StopLine6);

	//Roadarrow
	TArray<TSharedPtr<FJsonValue>>  ethHmiRoadarrow = VehNaviPilotNotification8->GetArrayField("ethHmiRoadarrow");
	TESTLOG(VehNaviPilotNotification8, ethHmiRoadarrow)
	GEELYLOG(VehNaviPilotNotification8, ethHmiRoadarrow)
	for (auto& it : ethHmiRoadarrow)
	{
		if (!it.IsValid())
		{
			break;
		}
		FRoadArrow tmp;
		tmp.colorOfRoadArrowe = static_cast<EColorOfRoadArrow>( it->AsObject()->GetNumberField("colorOfRoadArrow"));
		tmp.hmiRoadArrowLane = static_cast<EHmiRoadArrowLane>(it->AsObject()->GetNumberField("hmiRoadArrowLane"));
		tmp.typOfRoadArrow = static_cast<ETypOfRoadArrow>(it->AsObject()->GetNumberField("typOfRoadArrow"));
		tmp.hdDirOfRoadArrow = it->AsObject()->GetNumberField("colorOfRoadArrow") * 0.1;
		tmp.roadArrowPoint.X = it->AsObject()->GetObjectField("roadArrowPoint")->GetNumberField("dstLat") * 0.2 - 6553.5;
		tmp.roadArrowPoint.Y = it->AsObject()->GetObjectField("roadArrowPoint")->GetNumberField("dstLgt") * 0.4 - 3000;
		RoadArrow.Add(tmp);
	}

	//SpeedBump
	TArray<TSharedPtr<FJsonValue>>  ethHmiSpeedBump = VehNaviPilotNotification8->GetArrayField("ethHmiSpeedBump");
	TESTLOG(VehNaviPilotNotification8, ethHmiSpeedBump)
	GEELYLOG(VehNaviPilotNotification8, ethHmiSpeedBump)
	for (auto& it : ethHmiSpeedBump)
	{
		if (!it.IsValid())
		{
			break;
		}
		FSpeedBump tmp;
		tmp.startPoint.X = it->AsObject()->GetObjectField("startPoint")->GetNumberField("dstLat")*0.2 - 6553.5;
		tmp.startPoint.Y = it->AsObject()->GetObjectField("startPoint")->GetNumberField("dstLgt") * 0.4 - 3000;
		tmp.endPoint.X = it->AsObject()->GetObjectField("endPoint")->GetNumberField("dstLat") * 0.2 - 6553.5;
		tmp.endPoint.Y = it->AsObject()->GetObjectField("endPoint")->GetNumberField("dstLgt") * 0.4 - 3000;
		SpeedBump.Add(tmp);
	}

	//TrfcLight
	TArray<TSharedPtr<FJsonValue>>  ethHmiTrfcLight = VehNaviPilotNotification8->GetArrayField("ethHmiTrfcLight");
	TESTLOG(VehNaviPilotNotification8, ethHmiTrfcLight)
	GEELYLOG(VehNaviPilotNotification8, ethHmiTrfcLight)
	for (auto& it : ethHmiTrfcLight)
	{
		if (!it.IsValid())
		{
			break;
		}
		FTrafficLight tmp;
		tmp.colorOfTrfcLight = static_cast<EColorOfTrfcLight>(it->AsObject()->GetNumberField("color"));
		tmp.typOfTrfcLight = static_cast<ETypOfTrfcLight>(it->AsObject()->GetNumberField("type"));
		tmp.headingAngle = (it->AsObject()->GetNumberField("headingAngle")) * 0.1;
		tmp.lightDstHeight = (it->AsObject()->GetNumberField("lightDstHeight")) * 0.1;
		tmp.lightDstLat = (it->AsObject()->GetNumberField("lightDstLat")) * 0.2 - 6553.5;
		tmp.lightDstLgt = (it->AsObject()->GetNumberField("lightDstLgt")) * 0.4 - 3000;
		TrafficLight.Add(tmp);
	}

	//TrafficSign
	TArray<TSharedPtr<FJsonValue>>  ethHmiTrfcSign = VehNaviPilotNotification8->GetArrayField("ethHmiTrfcSign");
	TESTLOG(VehNaviPilotNotification8, ethHmiTrfcSign)
	GEELYLOG(VehNaviPilotNotification8, ethHmiTrfcSign)
	for (auto& it : ethHmiTrfcSign)
	{
		if (!it.IsValid())
		{
			break;
		}
		FTrafficSign tmp;
		tmp.typOfTrfcSign = static_cast<ETypOfTrfcSign>(it->AsObject()->GetNumberField("type"));
		tmp.hdDirOfTrfcSign = (it->AsObject()->GetNumberField("hdDirOfTrfcSign")) * 0.1;
		tmp.signDstHeight = (it->AsObject()->GetNumberField("signDstHeight")) * 0.1;
		tmp.signDstLat = (it->AsObject()->GetNumberField("signDstLat")) * 0.2 -6553.5;
		tmp.signDstLgt = (it->AsObject()->GetNumberField("signDstLgt")) * 0.4 -3000;
		TrfcSign.Add(tmp);
	}

	//renderingStatus88888
	RenderingStatus8.ethSelfLane =static_cast<ESelfLaneColor>(VehNaviPilotNotification8->GetNumberField("ethSelfLane"));
	RenderingStatus8.ethBoundarySpaceColor = static_cast<EEthBoundarySpaceColor>(VehNaviPilotNotification8->GetNumberField("ethBoundarySpaceColor"));
	RenderingStatus8.Weather = static_cast<EWeather>(VehNaviPilotNotification8->GetObjectField("ethADThemeDisp")->GetNumberField("weather"));

}
void AGeelyGameState::HandleCrossWalkData(TSharedPtr<FJsonObject> CrossWalk, TArray<FVector>& Line)
{
	TSharedPtr<FJsonObject> point1 = CrossWalk->GetObjectField("point1");
	TSharedPtr<FJsonObject> point2 = CrossWalk->GetObjectField("point2");
	TSharedPtr<FJsonObject> point3 = CrossWalk->GetObjectField("point3");
	TSharedPtr<FJsonObject> point4 = CrossWalk->GetObjectField("point4");
	Line.Add(FVector(point1->GetNumberField("dstLat")*0.2-6553.5, point1->GetNumberField("dstLgt") * 0.4 - 3000, 0));
	Line.Add(FVector(point2->GetNumberField("dstLat") * 0.2 - 6553.5, point2->GetNumberField("dstLgt") * 0.4 - 3000, 0));
	Line.Add(FVector(point3->GetNumberField("dstLat") * 0.2 - 6553.5, point3->GetNumberField("dstLgt") * 0.4 - 3000, 0));
	Line.Add(FVector(point4->GetNumberField("dstLat") * 0.2 - 6553.5, point4->GetNumberField("dstLgt") * 0.4 - 3000, 0));
}
void AGeelyGameState::HandleStopLineData(TSharedPtr<FJsonObject> StopLine, TArray<FVector>& Line)
{
	TSharedPtr<FJsonObject>startPoint = StopLine->GetObjectField("startPoint");
	TSharedPtr<FJsonObject>endPoint = StopLine->GetObjectField("endPoint");
	Line.Add(FVector(startPoint->GetNumberField("dstLat") * 0.2 - 6553.5, startPoint->GetNumberField("dstLgt") * 0.4 - 3000, 0));
	Line.Add(FVector(endPoint->GetNumberField("dstLat") * 0.2 - 6553.5, endPoint->GetNumberField("dstLgt") * 0.4 - 3000, 0));
}

void AGeelyGameState::HandleVehNaviPilotNotification9Data(TSharedPtr<FJsonObject>& RootJsonObject)
{
	TSharedPtr<FJsonObject> VehNaviPilotNotification9 = RootJsonObject->GetObjectField("VehNaviPilotNotification9");
	TESTLOG(RootJsonObject, VehNaviPilotNotification9)
	GEELYLOG(RootJsonObject, VehNaviPilotNotification9)
	TSharedPtr<FJsonObject> ethHmiBoundary = VehNaviPilotNotification9->GetObjectField("ethHmiBoundary");
	TESTLOG(VehNaviPilotNotification9, ethHmiBoundary)
	GEELYLOG(VehNaviPilotNotification9, ethHmiBoundary)
	TArray<TSharedPtr<FJsonValue>> ethBoundaryLineA = ethHmiBoundary->GetArrayField("ethBoundaryLineA");
	TESTLOG(ethHmiBoundary, ethBoundaryLineA)
	GEELYLOG(ethHmiBoundary, ethBoundaryLineA)
	if (ethBoundaryLineA.IsValidIndex(0)) { 
		TSharedPtr<FJsonObject> ethBoundaryLine1 = ethBoundaryLineA[0]->AsObject(); 
		if (ethBoundaryLine1->HasField("linePoint")) { HandleBoundaryLine(ethBoundaryLine1, GeelyDrawTotalData.BoundaryLine3); }
	}
	if (ethBoundaryLineA.IsValidIndex(1)) { 
		TSharedPtr<FJsonObject> ethBoundaryLine2 = ethBoundaryLineA[1]->AsObject();
		if (ethBoundaryLine2->HasField("linePoint")) { HandleBoundaryLine(ethBoundaryLine2, GeelyDrawTotalData.BoundaryLine4); }
	}
	if (ethBoundaryLineA.IsValidIndex(2)) {
		TSharedPtr<FJsonObject> ethBoundaryLine3 = ethBoundaryLineA[2]->AsObject();
		if (ethBoundaryLine3->HasField("linePoint")) { HandleBoundaryLine(ethBoundaryLine3, GeelyDrawTotalData.BoundaryLine5); }
	}
	if (ethBoundaryLineA.IsValidIndex(3)) {
		TSharedPtr<FJsonObject> ethBoundaryLine4 = ethBoundaryLineA[3]->AsObject();
		if (ethBoundaryLine4->HasField("linePoint")) { HandleBoundaryLine(ethBoundaryLine4, GeelyDrawTotalData.BoundaryLine6); }
	}
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
