// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionCurve.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h" // 添加用于调试绘制的头文件

// Sets default values
AInteractionCurve::AInteractionCurve(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create a default curve data object
    InteractionCurveData = CreateDefaultSubobject<UCurveFloat>(TEXT("InteractionCurveData"));
    InteractionCurveData->FloatCurve.AddKey(0.0f, 0.0f);
    InteractionCurveData->FloatCurve.AddKey(1.0f, 1.0f);
}

// Called when the game starts or when spawned
void AInteractionCurve::BeginPlay()
{
    Super::BeginPlay();
    PlayerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AInteractionCurve::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //GenerateCurve(DeltaTime); // 确保 DeltaTime 被传递
    //DetectCollision();
}

void AInteractionCurve::GenerateCurve(float DeltaTime)
{
    if (PlayerController)
    {
        FVector ViewLocation;
        FRotator ViewRotation;
        PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation); // 使用 GetPlayerViewPoint 获取视点位置和旋转

        StartLocation = ViewLocation;
        StartRotation = ViewRotation;
        EndLocation = StartLocation + StartRotation.Vector() * 1000.0f;

        // 调试输出
        UE_LOG(LogTemp, Log, TEXT("StartLocation: %s"), *StartLocation.ToString());
        UE_LOG(LogTemp, Log, TEXT("EndLocation: %s"), *EndLocation.ToString());
        UE_LOG(LogTemp, Log, TEXT("StartRotation: %s"), *StartRotation.ToString());

        // 清空之前的曲线数据
        InteractionCurveData->FloatCurve.Reset();

        // 添加新的曲线键值
        InteractionCurveData->FloatCurve.AddKey(0.0f, 0.0f);
        InteractionCurveData->FloatCurve.AddKey(1.0f, 1.0f);

        // 调试绘制曲线
        DrawDebugCurve(DeltaTime);
    }
}

void AInteractionCurve::DrawDebugCurve(float DeltaTime)
{
    // 使用 DebugDraw 来可视化曲线
    for (float Alpha = 0.0f; Alpha < 1.0f; Alpha += 0.01f)
    {
        FVector CurrentLocation = FMath::Lerp(StartLocation, EndLocation, InteractionCurveData->GetFloatValue(Alpha));
        FVector NextLocation = FMath::Lerp(StartLocation, EndLocation, InteractionCurveData->GetFloatValue(Alpha + 0.01f));
        DrawDebugLine(GetWorld(), CurrentLocation, NextLocation, FColor::Red, false, DeltaTime, 0, 5.0f);
    }
}

void AInteractionCurve::DetectCollision()
{
    // 检测碰撞的逻辑
}
