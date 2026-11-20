// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP3FPSGameMode.h"
#include "GP3FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GP3FPSPlayerState.h"
#include "EngineUtils.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"

namespace
{
	constexpr int32 NumTeams = 4;
}

AGP3FPSGameMode::AGP3FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerStateClass = AGP3FPSPlayerState::StaticClass();
}


void AGP3FPSGameMode::HandleStartingNewPlayer_Implementation(
    APlayerController* NewPlayer)
{
    auto* PlayerState = NewPlayer->GetPlayerState<AGP3FPSPlayerState>();
    if(!PlayerState || !GameState)
    {
        UE_LOG(LogTemp, Error, TEXT("Team assignment: missing PlayerState or GameState"));
        return;
    }

    // チームIDを割り当てる
    if(PlayerState->TeamId == INDEX_NONE)
    {
        bool Taken[NumTeams] = {};

        // すでに使われているIDを列挙
        for(APlayerState* State : GameState->PlayerArray)
        {
            const auto* Other = Cast<AGP3FPSPlayerState>(State);
            if(Other && Other->TeamId >= 0 && Other->TeamId < NumTeams)
            {
                Taken[Other->TeamId] = true;
            }
        }

        // あらためて、使われていないIDを今回作成されるプレイヤーのTeamIdに設定する
        for(int32 TeamId = 0; TeamId < NumTeams; ++TeamId)
        {
            if(!Taken[TeamId])
            {
                PlayerState->TeamId = TeamId;
                break;
            }
        }
    }

    if(PlayerState->TeamId == INDEX_NONE)
    {
        UE_LOG(LogTemp, Warning, TEXT("Team assignment: all teams are occupied"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("%s assigned to Team%d"),
        *PlayerState->GetPlayerName(), PlayerState->TeamId);

    // 親クラスがスポーン処理に進む前に、TeamId を確定させる。
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}


AActor* AGP3FPSGameMode::FindPlayerStart_Implementation(
    AController* Player, const FString& IncomingName)
{
    const auto* PlayerState =
        Player ? Player->GetPlayerState<AGP3FPSPlayerState>() : nullptr;

    if(PlayerState && PlayerState->TeamId != INDEX_NONE)
    {
        const FName TeamTag(*FString::Printf(
            TEXT("Team%d"), PlayerState->TeamId));

        // プレイヤー開始位置を探す
        for(TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
        {
            if(It->PlayerStartTag == TeamTag)
            {
                UE_LOG(LogTemp, Log, TEXT("Selected PlayerStart: %s"),
                    *TeamTag.ToString());
                return *It;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Missing PlayerStart tag: %s"),
            *TeamTag.ToString());
    }

    // チーム確定前の呼び出しや、タグの設定漏れでは標準の地点選択を使う。
    return Super::FindPlayerStart_Implementation(Player, IncomingName);
}