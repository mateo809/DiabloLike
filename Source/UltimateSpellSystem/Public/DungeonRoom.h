#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoom.generated.h"

UCLASS()
class ADungeonRoom : public AActor
{
    GENERATED_BODY()

public:
    ADungeonRoom();

    // Les sockets pour connecter d'autres salles
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    TArray<FVector> DoorSockets;

    // Taille approximative de la salle (pour éviter collision)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    FVector RoomSize;

    // Booléen pour savoir si c'est salle de départ ou boss
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    bool bIsStartRoom = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    bool bIsBossRoom = false;
};
