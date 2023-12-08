// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DataStruct.h"
#include "GeelyDrawType.h"
#include "GeelyDraw_GameInstanceSubsystem.h"
#include "AndroidUtilsBPLibrary.h"
#include "GeelyGameState.generated.h"

#define GEELYLOG(JsonName,...) \
if(!JsonName->HasField(#__VA_ARGS__)) \
{ \
FPlatformMisc::LowLevelOutputDebugStringf(TEXT("JsonObject:%s:===>%s<=== is Not Found."),TEXT(#JsonName),TEXT(#__VA_ARGS__)); \
}

//Message about Json error
#define TESTLOG(JsonObject,...) \
if(!JsonObject->HasField(#__VA_ARGS__)) \
{ \
GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("*****JsonError:%s do not has %s"),TEXT(#JsonObject),TEXT(#__VA_ARGS__))); \
}

/**
 * 
 */
UCLASS()
class GEELYHMI_API AGeelyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;
	UFUNCTION()
	void ReceiveAndroidStringData(int32 DataId, FString Key, FString Data);
	UFUNCTION(BlueprintCallable)
	void ReceiveNativeStringData();
public:
	void ClearAll();
	void EmptyDynamicMeshTotalData();
	void HandleVehNaviPilotNotification1Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification2Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification3Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleEthLineData(TSharedPtr<FJsonObject>& EthLine);
	void HandleVehNaviPilotNotification4Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleBoundaryLine(TSharedPtr<FJsonObject>& BoundaryLine , TArray<FVector>& Line);
	void HandleVehNaviPilotNotification5Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification6Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification7Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification8Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleCrossWalkData(TSharedPtr<FJsonObject> CrossWalk, TArray<FVector>& Line);
	void HandleStopLineData(TSharedPtr<FJsonObject> StopLine, TArray<FVector>& Line);
	void HandleVehNaviPilotNotification9Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification10Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification11Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotification12Data(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotificationStartData(TSharedPtr<FJsonObject>& RootJsonObject);
	void HandleVehNaviPilotNotificationEndData(TSharedPtr<FJsonObject>& RootJsonObject);

public:
	/***************Parameter list***************
	* TotalObstacle
	* GeelyDrawTotalData
	* EthLineArray
	* HmiCamView
	* RoadArrow
	* SpeedBump
	* TrafficLight
	*/
	UPROPERTY()
	UAndroidUtilsBPLibrary::FOnAndroidDataReceivedString DataReceivedString;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Path")
	FString Path = TEXT("D:/WorkTempProject/testData.json");
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray<FObstacle> TotalObstacle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Geely|GeelyGameState")
	FGeelyDrawTotalData GeelyDrawTotalData;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray< FEthLine> EthLineArray;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	FHmiCamView HmiCamView;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray<FRoadArrow> RoadArrow;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray<FSpeedBump> SpeedBump;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray<FTrafficLight> TrafficLight;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	TArray<FTrafficSign> TrfcSign;
	UPROPERTY(BlueprintReadWrite, Category = "Geely|GeelyGameState")
	FRenderingStatus8 RenderingStatus8;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Switch")
	bool bIsReceiveNativeStringData = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Switch")
	bool bIsReceiveAndroidStringData = true;
	
};
