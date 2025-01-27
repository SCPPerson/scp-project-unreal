

#include "RotatingReflectionCaptures/RotatingBoxReflectionCapture.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxReflectionCaptureComponent.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/TextureRenderTargetCube.h"
#include "Engine/TextureCube.h"

DEFINE_LOG_CATEGORY(LogRotatingRefCap);

// Sets default values
ARotatingBoxReflectionCapture::ARotatingBoxReflectionCapture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = false;

	// Root component
	this->Root = CreateDefaultSubobject<USceneComponent >("Root", false);
	this->Root->SetMobility(EComponentMobility::Static);
	this->Root->SetWorldScale3D(FVector(500, 500, 200));
	this->SetRootComponent(this->Root);

#if WITH_EDITOR
	// Sprite component
	this->Sprite = CreateDefaultSubobject<UBillboardComponent>("Sprite", false);
	this->Sprite->SetSprite(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Engine/EditorResources/S_ReflActorIcon.S_ReflActorIcon'")).Object);
	this->Sprite->bIsScreenSizeScaled = true;
	this->Sprite->ScreenSize = 0.0025f;
	this->Sprite->SetRelativeLocation(FVector(0, 0, 0));
	this->Sprite->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
	
	// Box component
	this->Box = CreateDefaultSubobject<UBoxComponent >("Box", false);
	this->Box->SetBoxExtent(FVector(1, 1, 1), false);
	this->Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->Box->SetRelativeLocation(FVector(0, 0, 0));
	this->Box->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
#endif

	// Reflection capture rotation 0
	this->RefCap0 = CreateDefaultSubobject<UBoxReflectionCaptureComponent>("BoxReflectionCaptureRot0", false);
	this->RefCap0->ReflectionSourceType = EReflectionSourceType::SpecifiedCubemap;
	this->RefCap0->SourceCubemapAngle = 0;
	this->RefCap0->SetRelativeLocation(FVector(0, 0, 0));
	this->RefCap0->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
	this->RefCap0->SetVisibility(true);

	// Reflection capture rotation 90
	this->RefCap90 = CreateDefaultSubobject<UBoxReflectionCaptureComponent>("BoxReflectionCaptureRot90", false);
	this->RefCap90->ReflectionSourceType = EReflectionSourceType::SpecifiedCubemap;
	this->RefCap90->SourceCubemapAngle = 90;
	this->RefCap90->SetRelativeLocation(FVector(0, 0, 0));
	this->RefCap90->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
	this->RefCap90->SetVisibility(true);

	// Reflection capture rotation 180
	this->RefCap180 = CreateDefaultSubobject<UBoxReflectionCaptureComponent>("BoxReflectionCaptureRot180", false);
	this->RefCap180->ReflectionSourceType = EReflectionSourceType::SpecifiedCubemap;
	this->RefCap180->SourceCubemapAngle = 180;
	this->RefCap180->SetRelativeLocation(FVector(0, 0, 0));
	this->RefCap180->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
	this->RefCap180->SetVisibility(true);

	// Reflection capture rotation 270
	this->RefCap270 = CreateDefaultSubobject<UBoxReflectionCaptureComponent>("BoxReflectionCaptureRot270", false);
	this->RefCap270->ReflectionSourceType = EReflectionSourceType::SpecifiedCubemap;
	this->RefCap270->SourceCubemapAngle = 270;
	this->RefCap270->SetRelativeLocation(FVector(0, 0, 0));
	this->RefCap270->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
	this->RefCap270->SetVisibility(true);

	// Scene capture cube
#if WITH_EDITOR
	this->SceneCaptureCube = CreateDefaultSubobject<USceneCaptureComponentCube>("SceneCaptureCube", false);
	this->SceneCaptureCube->bCaptureEveryFrame = false;
	this->SceneCaptureCube->bCaptureOnMovement = false;
	this->SceneCaptureCube->ShowFlags.ReflectionEnvironment = false;
	this->SceneCaptureCube->SetRelativeLocation(FVector(0, 0, 0));
	this->SceneCaptureCube->SetRelativeScale3D(FVector(0.00001, 0.00001, 0.00001));
	this->SceneCaptureCube->AttachToComponent(this->Root, FAttachmentTransformRules::KeepRelativeTransform);
#endif
}

#if WITH_EDITOR
void ARotatingBoxReflectionCapture::UpdateCapture()
{
	// Only allow updates every two seconds (to avoid performance problems)
	if ((FDateTime::UtcNow() - this->LastUpdate).GetTotalSeconds() < 0.5f)
	{
		UE_LOG(LogRotatingRefCap, Warning, TEXT("%s: Not updating, last update was at least 0.5s ago"), *this->GetName());
		return;
	}

	if (this->GetWorld()->WorldType != EWorldType::Editor)
	{
		UE_LOG(LogRotatingRefCap, Error, TEXT("%s: Cannot update inside a non-editor mode"), *this->GetName());
		return;
	}

	this->LastUpdate = FDateTime::UtcNow();

	// Dispose old render target and static texture
	if (IsValid(this->RenderTarget))
	{
		this->RenderTarget->ConditionalBeginDestroy();
	}

	if (IsValid(this->StaticTexture))
	{
		this->StaticTexture->ConditionalBeginDestroy();
	}

	// Create new render target
	this->RenderTarget = NewObject<UTextureRenderTargetCube>(this, FName(), RF_Transient);
	this->RenderTarget->ClearColor = FLinearColor::Green;
	this->RenderTarget->Init(256, EPixelFormat::PF_FloatRGBA);
	this->RenderTarget->UpdateResourceImmediate(true);
	UE_LOG(LogRotatingRefCap, Log, TEXT("%s: Created new render target"), *this->GetName());

	// Capture scence
	this->SceneCaptureCube->TextureTarget = this->RenderTarget;
	this->SceneCaptureCube->CaptureScene();
	UE_LOG(LogRotatingRefCap, Log, TEXT("%s: Captured scene"), *this->GetName());

	// Create new static texture
	this->StaticTexture = NewObject<UTextureCube>(this, FName(), RF_Transient);

	// Draw render target to static texture
	this->StaticTexture = this->RenderTarget->ConstructTextureCube(this->StaticTexture->GetOuter(), this->StaticTexture->GetName(), this->RenderTarget->GetMaskedFlags());
	this->StaticTexture->Modify();
	this->StaticTexture->MarkPackageDirty();
	this->StaticTexture->PostEditChange();
	this->StaticTexture->UpdateResource();
	UE_LOG(LogRotatingRefCap, Log, TEXT("%s: Created new static texture"), *this->GetName());

	// Apply new static texture to reflection capture
	this->RefCap0->Cubemap = this->StaticTexture;
	this->RefCap90->Cubemap = this->StaticTexture;
	this->RefCap180->Cubemap = this->StaticTexture;
	this->RefCap270->Cubemap = this->StaticTexture;
	UE_LOG(LogRotatingRefCap, Log, TEXT("%s: Updated reflection captures"), *this->GetName());
	GEngine->SetTimeUntilNextGarbageCollection(0.25);
}


void ARotatingBoxReflectionCapture::OnConstruction(const FTransform& Transform)
{
	if (this->GetWorld()->WorldType != EWorldType::Editor)
	{
		return;
	}

	this->UpdateCapture();
	this->PlacedRotation = this->GetActorRotation();
}
#endif

// Called when the game starts or when spawned
void ARotatingBoxReflectionCapture::BeginPlay()
{
	Super::BeginPlay();

	if (this->bRemovedUnnecessaryComponents)
	{
		return;
	}

	// Delete reflection captures based on our "new" rotation
    int Rotation = FMath::DivideAndRoundNearest((this->GetActorRotation() - this->PlacedRotation).GetDenormalized().Yaw, 90.0f);
	UE_LOG(LogRotatingRefCap, Log, TEXT("%s: Detected rotation %d"), *this->GetName(), Rotation);
	switch (Rotation)
	{
	case 0:
		this->RefCap0->SetVisibility(true);
		this->RefCap90->DestroyComponent();
		this->RefCap180->DestroyComponent();
		this->RefCap270->DestroyComponent();
		this->bRemovedUnnecessaryComponents = true;
		break;
	case 1:
		this->RefCap270->SetVisibility(true); //Soruce angle rotates in the opposite direction
		this->RefCap0->DestroyComponent();
		this->RefCap90->DestroyComponent();
		this->RefCap180->DestroyComponent();
		this->bRemovedUnnecessaryComponents = true;
		break;
	case 2:
		this->RefCap180->SetVisibility(true);
		this->RefCap270->DestroyComponent();
		this->RefCap0->DestroyComponent();
		this->RefCap90->DestroyComponent();
		this->bRemovedUnnecessaryComponents = true;
		break;
	case 3:
		this->RefCap90->SetVisibility(true); //Soruce angle rotates in the opposite direction
		this->RefCap180->DestroyComponent();
		this->RefCap270->DestroyComponent();
		this->RefCap0->DestroyComponent();
		this->bRemovedUnnecessaryComponents = true;
		break;
	default:
		UE_LOG(LogRotatingRefCap, Error, TEXT("%s: Rotation is invalid (%d)"), *this->GetName(), Rotation)
	}
}

// Called every frame
void ARotatingBoxReflectionCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

