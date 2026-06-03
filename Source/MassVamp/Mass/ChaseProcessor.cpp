// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseProcessor.h"

#include "ChaseTrait.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UChaseProcessor::UChaseProcessor() : EntityQuery(*this)
{
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
}

void UChaseProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FSimpleMovementFragment>(EMassFragmentAccess::ReadOnly);
}

void UChaseProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// 1. 월드에서 플레이어의 현재 위치를 가져옵니다 (가장 단순한 방식)
	AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerActor) return;
	FVector PlayerLocation = PlayerActor->GetActorLocation();

	float DeltaTime = Context.GetDeltaTimeSeconds();
	
	EntityQuery.ForEachEntityChunk(Context, [this, PlayerLocation, DeltaTime](FMassExecutionContext& ChunkContext)
	{
		TArrayView<FTransformFragment> TransformList = ChunkContext.GetMutableFragmentView<FTransformFragment>();
		TConstArrayView<FSimpleMovementFragment> SpeedList = ChunkContext.GetFragmentView<FSimpleMovementFragment>();
        
		int32 EntityCount = ChunkContext.GetNumEntities();
		for (int32 i = 0; i < EntityCount; ++i)
		{
			FTransform& MonsterTransform = TransformList[i].GetMutableTransform();
			FVector MonsterLocation = MonsterTransform.GetLocation();
            
			FVector Direction = (PlayerLocation - MonsterLocation);
			Direction.Z = 0.0f;
			Direction.Normalize();
            
			FVector NewLocation = MonsterLocation + (Direction * SpeedList[i].MoveSpeed * DeltaTime);
			MonsterTransform.SetLocation(NewLocation);
            
			MonsterTransform.SetRotation(Direction.Rotation().Quaternion());
		}
	});
}
