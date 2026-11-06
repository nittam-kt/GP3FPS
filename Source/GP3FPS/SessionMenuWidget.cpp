// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionMenuWidget.h"
#include "SessionSubsystem.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"


bool USessionMenuWidget::CreateRoom(FString RoomName)
{
    RoomName.TrimStartAndEndInline();

    if(RoomName.IsEmpty() || !GetGameInstance())
    {
        return false;
    }

    // ログイン済みか確認
    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    IOnlineIdentityPtr Identity =
        OSS ? OSS->GetIdentityInterface() : nullptr;

    if(!Identity.IsValid() ||
        Identity->GetLoginStatus(0) != ELoginStatus::LoggedIn)
    {
        return false;
    }

    auto* Sub =
        GetGameInstance()->GetSubsystem<USessionSubsystem>();

    // 作成要求が受け付けられたとき true
    return Sub && Sub->CreateSession(RoomName, 3);
}


void USessionMenuWidget::SearchRooms()
{
    if(auto* GI = GetGameInstance())
    {
        if(auto* Sub = GI->GetSubsystem<USessionSubsystem>())
        {
            Sub->FindSessions();
        }
    }
}