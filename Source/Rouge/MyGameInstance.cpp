// MyGameInstance.cpp

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"

UMyGameInstance::UMyGameInstance()
    : HighScore(0)
{
    InitializeHighScoreFromSaveGame();
}

int32 UMyGameInstance::GetHighScore()
{
    return HighScore;
}

void UMyGameInstance::SetHighScore(int32 NewHighScore)
{
    HighScore = NewHighScore;
    SaveGame();
}

void UMyGameInstance::SaveGame()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    if (SaveGameInstance)
    {
        SaveGameInstance->HighScore = HighScore;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoreSlot"), 0);
    }
}

void UMyGameInstance::LoadGame()
{
    UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoreSlot"), 0));
    if (LoadGameInstance)
    {
        HighScore = LoadGameInstance->HighScore;
    }
}

void UMyGameInstance::InitializeHighScoreFromSaveGame()
{
    LoadGame();
}