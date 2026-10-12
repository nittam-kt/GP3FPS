// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionGameMode.h"

#include "SessionGameMode.h"
#include "SessionSubsystem.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

void ASessionGameMode::BeginPlay()
{
    Super::BeginPlay();

    if(UGameplayStatics::ParseOption(
        OptionsString, TEXT("HostSession")) == TEXT("1"))
    {
        if(auto* Sub =
            GetGameInstance()->GetSubsystem<USessionSubsystem>())
        {
            Sub->StartSession();
        }
    }
}