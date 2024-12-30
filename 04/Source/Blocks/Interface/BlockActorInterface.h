// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlockActorInterface.generated.h"

UINTERFACE(BlueprintType)
class UBlockActorInterface : public UInterface
{
    GENERATED_BODY()
};

class BLOCKS_API IBlockActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Blocks")
    void InteractWithBlock();
};

/**
 * 
class BLOCKS_API BlockActorInterface
{
public:
	BlockActorInterface();
	~BlockActorInterface();
};

 */