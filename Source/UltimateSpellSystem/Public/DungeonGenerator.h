#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoom.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class ADungeonGenerator : public AActor
{
	GENERATED_BODY()
public:
	ADungeonGenerator();
protected:
	virtual void BeginPlay() override;
public:
	// Classes de salles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<ADungeonRoom> StartRoomClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TArray<TSubclassOf<ADungeonRoom>> RoomVariants;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TSubclassOf<ADungeonRoom> BossRoomClass;
	// Nombre de salles intermédiaires
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 NumRooms = 5;
	// Stock toutes les salles générées
	UPROPERTY()
	TArray<ADungeonRoom*> GeneratedRooms;

	void GenerateDungeon();
private:
	// Fonction helper pour calculer la position suivante
	FVector CalculateNextRoomLocation(ADungeonRoom* PreviousRoom, int32 Direction);
};