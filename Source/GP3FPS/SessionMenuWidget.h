// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GP3FPS_API USessionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Session")
	bool CreateRoom(FString RoomName);

	UFUNCTION(BlueprintCallable, Category = "Session")
	void SearchRooms();
};
