#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class AEnemySpawner : public AActor
{
    GENERATED_BODY()

public:
    AEnemySpawner();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void InitializePool();
    void SpawnEnemyFromPool();

    // Timer pour spawn
    FTimerHandle SpawnTimer;

    // Pool d'ennemis
    UPROPERTY()
    TArray<AActor*> EnemyPool;

    int32 CurrentIndex = 0;
    int32 ActiveEnemyCount = 0;

public:
    // Types d'ennemis à spawner
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TArray<TSubclassOf<AActor>> EnemyTypes;

    // Taille du pool
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 PoolSize = 10;

    // Spawn aléatoire parmi les types
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    bool bRandomSpawn = true;

    // Nombre maximal d'ennemis actifs
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 MaxEnemies = 5;

    // Intervalle entre les spawns
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnInterval = 2.0f;

    // Composant pour définir le point de spawn
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* SpawnPoint;

    // Rayon pour spawn aléatoire autour du SpawnPoint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float SpawnRadius = 300.0f;
};
