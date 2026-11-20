// Fill out your copyright notice in the Description page of Project Settings.


#include "GP3FPSPlayerState.h"
#include "Net/UnrealNetwork.h"

void AGP3FPSPlayerState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AGP3FPSPlayerState, TeamId);
}
