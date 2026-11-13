// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SessionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GP3FPS_API ASessionGameMode : public AGameModeBase
{
	GENERATED_BODY()

	static constexpr int MaxPlayers = 2;

	// コンストラクタ
	ASessionGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void TryStartIfReady();
};
