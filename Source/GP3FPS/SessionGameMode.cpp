// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionGameMode.h"

#include "SessionGameMode.h"
#include "SessionSubsystem.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"


ASessionGameMode::ASessionGameMode()
{
    bUseSeamlessTravel = true;
}


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


void ASessionGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // サーバー以外では処理しない
    if(!HasAuthority()) return;

    // スタンドアロン（ネットワークなし）なら無視
    if(GetNetMode() == NM_Standalone) return;
    // セッションが立っている（Listen化も済み）ときだけ扱う

    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if(OSS)
    {
        IOnlineSessionPtr Session = OSS->GetSessionInterface();
        if(!Session.IsValid() || !Session->GetNamedSession(NAME_GameSession))
        {
            // まだ CreateSession 前/直後など → 待機
            return;
        }
    }

    TryStartIfReady();
}


void ASessionGameMode::TryStartIfReady()
{
    const int32 NumConnected = GameState ? GameState->PlayerArray.Num() : 0;
    auto str = FString::Printf(TEXT("Players: %d"), NumConnected);
    UKismetSystemLibrary::PrintString(this, str, true, true, FColor::Green, 6.f, TEXT("None"));

    if(NumConnected >= MaxPlayers)
    {
        // 直後の同期ズレ回避で次フレームに遷移
        FTimerHandle TH;
        GetWorldTimerManager().SetTimer(TH, [this]()
            {
                GetWorld()->ServerTravel(TEXT("/FpsFramework/Maps/FpsGameMap?listen"), /*bAbsolute=*/true);
            }, 0.1f, false);
    }
}
