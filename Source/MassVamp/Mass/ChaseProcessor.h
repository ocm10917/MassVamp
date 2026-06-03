// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "ChaseProcessor.generated.h"

/**
 * 
 */
UCLASS()
class MASSVAMP_API UChaseProcessor : public UMassProcessor
{
	GENERATED_BODY()
	
public:
	UChaseProcessor();
	
protected:
	
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	

private:
	FMassEntityQuery EntityQuery;
};
