#include "DungeonGenerator.h"
#include "Engine/World.h"

ADungeonGenerator::ADungeonGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADungeonGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateDungeon();
}

void ADungeonGenerator::GenerateDungeon()
{
    if (!StartRoomClass || !BossRoomClass || RoomVariants.Num() == 0) return;

    FActorSpawnParameters SpawnParams;
    GeneratedRooms.Empty();

    // Spawn la salle de départ
    ADungeonRoom* StartRoom = GetWorld()->SpawnActor<ADungeonRoom>(
        StartRoomClass,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (StartRoom)
    {
        StartRoom->bIsStartRoom = true;
        GeneratedRooms.Add(StartRoom);
    }
    else
    {
        return;
    }

    // Crée une chaîne principale de salles
    ADungeonRoom* MainPathLastRoom = StartRoom;
    int32 MainPathRooms = NumRooms / 2;

    for (int32 i = 0; i < MainPathRooms; i++)
    {
        TSubclassOf<ADungeonRoom> RoomClass = RoomVariants[FMath::RandRange(0, RoomVariants.Num() - 1)];
        FVector SpawnLocation = CalculateNextRoomLocation(MainPathLastRoom, 0); // Direction devant

        ADungeonRoom* NewRoom = GetWorld()->SpawnActor<ADungeonRoom>(
            RoomClass,
            SpawnLocation,
            FRotator::ZeroRotator,
            SpawnParams
        );

        if (NewRoom)
        {
            GeneratedRooms.Add(NewRoom);
            MainPathLastRoom = NewRoom;
        }
    }

    // Crée une branche latérale (gauche)
    ADungeonRoom* LeftBranchStart = StartRoom;
    int32 LeftBranchRooms = (NumRooms - MainPathRooms) / 2;

    ADungeonRoom* LeftBranchLastRoom = LeftBranchStart;
    for (int32 i = 0; i < LeftBranchRooms; i++)
    {
        TSubclassOf<ADungeonRoom> RoomClass = RoomVariants[FMath::RandRange(0, RoomVariants.Num() - 1)];
        FVector SpawnLocation = CalculateNextRoomLocation(LeftBranchLastRoom, 1); // Direction gauche

        ADungeonRoom* NewRoom = GetWorld()->SpawnActor<ADungeonRoom>(
            RoomClass,
            SpawnLocation,
            FRotator::ZeroRotator,
            SpawnParams
        );

        if (NewRoom)
        {
            GeneratedRooms.Add(NewRoom);
            LeftBranchLastRoom = NewRoom;
        }
    }

    // Crée une branche latérale (droite)
    ADungeonRoom* RightBranchStart = StartRoom;
    ADungeonRoom* RightBranchLastRoom = RightBranchStart;
    int32 RightBranchRooms = NumRooms - MainPathRooms - LeftBranchRooms;

    for (int32 i = 0; i < RightBranchRooms; i++)
    {
        TSubclassOf<ADungeonRoom> RoomClass = RoomVariants[FMath::RandRange(0, RoomVariants.Num() - 1)];
        FVector SpawnLocation = CalculateNextRoomLocation(RightBranchLastRoom, 2); // Direction droite

        ADungeonRoom* NewRoom = GetWorld()->SpawnActor<ADungeonRoom>(
            RoomClass,
            SpawnLocation,
            FRotator::ZeroRotator,
            SpawnParams
        );

        if (NewRoom)
        {
            GeneratedRooms.Add(NewRoom);
            RightBranchLastRoom = NewRoom;
        }
    }

    // Spawn la salle du boss à la fin du chemin principal
    FVector BossLocation = CalculateNextRoomLocation(MainPathLastRoom, 0);
    ADungeonRoom* BossRoom = GetWorld()->SpawnActor<ADungeonRoom>(
        BossRoomClass,
        BossLocation,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (BossRoom)
    {
        BossRoom->bIsBossRoom = true;
        GeneratedRooms.Add(BossRoom);
    }
}

FVector ADungeonGenerator::CalculateNextRoomLocation(ADungeonRoom* PreviousRoom, int32 Direction)
{
    if (!PreviousRoom) return FVector::ZeroVector;

    FVector CurrentPos = PreviousRoom->GetActorLocation();
    FVector RoomSize = PreviousRoom->RoomSize;

    FVector Offset = FVector::ZeroVector;

    switch (Direction)
    {
    case 0: // Devant (axe X)
        Offset = FVector(RoomSize.X * 1.5f, 0, 0);
        break;
    case 1: // Gauche (axe Y+)
        Offset = FVector(0, RoomSize.Y * 1.5f, 0);
        break;
    case 2: // Droite (axe Y-)
        Offset = FVector(0, -RoomSize.Y * 1.5f, 0);
        break;
    }

    return CurrentPos + Offset;
}