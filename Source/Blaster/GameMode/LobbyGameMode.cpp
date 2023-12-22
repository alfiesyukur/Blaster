// Copyright SF5Gaming, Inc.

#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	int NumberOfPlayers = GameState.Get()->PlayerArray.Num();	
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel("/Game/Maps/BlasterMap?listen");
		}
	}	
}
