// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP3FPSGameMode.h"
#include "GP3FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGP3FPSGameMode::AGP3FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
