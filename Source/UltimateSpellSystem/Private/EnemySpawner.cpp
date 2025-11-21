#include "EnemySpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    // Créer le spawn point
    SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
    RootComponent = SpawnPoint;
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();

    InitializePool();

    // Lancer le timer pour spawn régulièrement
    if (EnemyPool.Num() > 0)
    {
        GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemyFromPool, SpawnInterval, true);
    }
}

void AEnemySpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Initialise le pool d'ennemis
void AEnemySpawner::InitializePool()
{
    if (EnemyTypes.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Aucun ennemi défini dans EnemyTypes !"));
        return;
    }

    for (int32 i = 0; i < PoolSize; i++)
    {
        TSubclassOf<AActor> EnemyClass;

        if (bRandomSpawn)
            EnemyClass = EnemyTypes[FMath::RandRange(0, EnemyTypes.Num() - 1)];
        else
        {
            EnemyClass = EnemyTypes[CurrentIndex];
            CurrentIndex = (CurrentIndex + 1) % EnemyTypes.Num();
        }

        AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyClass, FVector::ZeroVector, FRotator::ZeroRotator);

        if (Enemy)
        {
            Enemy->SetActorHiddenInGame(true);
            Enemy->SetActorEnableCollision(false);
            Enemy->SetActorTickEnabled(false);

            EnemyPool.Add(Enemy);
        }
    }
}

// Spawner un ennemi depuis le pool
void AEnemySpawner::SpawnEnemyFromPool()
{
    if (ActiveEnemyCount >= MaxEnemies)
        return;

    for (AActor* Enemy : EnemyPool)
    {
        if (Enemy && Enemy->IsHidden())
        {
            FVector SpawnLocation = SpawnPoint->GetComponentLocation();
            // Spawn aléatoire autour du point
            SpawnLocation.X += FMath::RandRange(-SpawnRadius, SpawnRadius);
            SpawnLocation.Y += FMath::RandRange(-SpawnRadius, SpawnRadius);

            Enemy->SetActorLocation(SpawnLocation);
            Enemy->SetActorRotation(SpawnPoint->GetComponentRotation());

            Enemy->SetActorHiddenInGame(false);
            Enemy->SetActorEnableCollision(true);
            Enemy->SetActorTickEnabled(true);

            ActiveEnemyCount++;
            return;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Pool plein, aucun ennemi disponible"));
}
