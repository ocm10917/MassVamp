// Fill out your copyright notice in the Description page of Project Settings.


/**
 * 
 */

#pragma once
#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "ChaseTrait.generated.h"

USTRUCT(BlueprintType)
struct FSimpleMovementFragment : public FMassFragment
{
	GENERATED_BODY()
    
	// 잡몹의 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 200.0f; 
};