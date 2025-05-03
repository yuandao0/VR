// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionCurve.generated.h"

UCLASS()
class BLOCKS_API AInteractionCurve : public AActor
{
    GENERATED_BODY()

public:	
    // Sets default values for this actor's properties
    AInteractionCurve(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // 确保 GenerateCurve 方法是 public 或 protected
    UFUNCTION(BlueprintCallable, Category = "InteractionCurve")
    void GenerateCurve(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "InteractionCurve")
    void DetectCollision();

    UFUNCTION(BlueprintCallable, Category = "InteractionCurve")
    void DrawDebugCurve(float DeltaTime);

    UPROPERTY(VisibleAnywhere)
    UCurveFloat* InteractionCurveData;

    UPROPERTY(VisibleAnywhere)
    APlayerController* PlayerController;

    FVector StartLocation;
    FVector EndLocation;
    FRotator StartRotation;
};
