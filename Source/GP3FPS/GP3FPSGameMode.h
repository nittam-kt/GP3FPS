// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GP3FPSGameMode.generated.h"

UCLASS(minimalapi)
class AGP3FPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGP3FPSGameMode();

protected:
    virtual void HandleStartingNewPlayer_Implementation(
        APlayerController* NewPlayer) override;

    virtual AActor* FindPlayerStart_Implementation(
        AController* Player, const FString& IncomingName) override;
};



