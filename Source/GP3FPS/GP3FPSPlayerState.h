// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GP3FPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GP3FPS_API AGP3FPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Team")
    int32 TeamId = INDEX_NONE;

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
