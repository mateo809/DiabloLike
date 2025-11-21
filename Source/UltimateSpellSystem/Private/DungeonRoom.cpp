//#include "DungeonRoom.h"
//#include "Components/StaticMeshComponent.h"
//
//ADungeonRoom::ADungeonRoom()
//{
//	PrimaryActorTick.bCanEverTick = false;
//	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
//}
//
//void ADungeonRoom::OnConstruction(const FTransform& Transform)
//{
//	Super::OnConstruction(Transform);
//
//	Doors.Empty();
//
//	// Trouve toutes les StaticMeshComponents
//	TArray<UStaticMeshComponent*> Components;
//	GetComponents<UStaticMeshComponent>(Components);
//
//	// Ne garder que les portes (tag "Door")
//	for (UStaticMeshComponent* C : Components)
//	{
//		if (C->ComponentHasTag("Door"))
//		{
//			Doors.Add(C);
//		}
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("%s -> Doors detected: %d"), *GetName(), Doors.Num());
//}
//
//UStaticMeshComponent* ADungeonRoom::GetRandomDoor() const
//{
//	if (Doors.Num() == 0)
//		return nullptr;
//
//	return Doors[FMath::RandRange(0, Doors.Num() - 1)];
//}
