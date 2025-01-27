

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AItemBase;

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryComponentChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName = "Inventory Component"))
class SCPPU_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	//// Properties ////
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Size = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bUseWhitelistAsBlacklist = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<AItemBase>> Whitelist;

	UPROPERTY()
		TMap<int, AItemBase*> ItemMap;

	UPROPERTY(BlueprintAssignable)
		FInventoryComponentChanged OnInventoryChanged;

	//// Functions ////	
public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
		bool AddItem(AItemBase* Item, int Slot);

	UFUNCTION(BlueprintCallable)
		bool DropItem(int Slot, FVector DropLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		AItemBase* GetItem(int Slot);

	UFUNCTION(BlueprintCallable)
		bool MoveItem(int FromSlot, int ToSlot, bool bSwapIfNecessary);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int FindSlotOfItem(AItemBase* Item);

	UFUNCTION(BlueprintCallable)
		void Resize(int NewSize, bool bDropExcessiveItems = true, FVector DropLocation = FVector(0, 0, 0));

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsSlotEmpty(int Slot);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetFirstEmptySlot();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CanItemBeAdded(AItemBase* Item);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
