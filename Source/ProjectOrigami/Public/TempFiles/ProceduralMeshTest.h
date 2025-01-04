// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshTest.generated.h"

class UProceduralMeshComponent;

UCLASS()
class PROJECTORIGAMI_API AProceduralMeshTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralMeshTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The Procedural Mesh Component for rendering the mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UProceduralMeshComponent* ProceduralMesh;

	// Dimensions and subdivisions for the paper
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Properties",
		meta = (ClampMin = "10.0", UIMin = "10.0"))
	float Width = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Properties",
		meta = (ClampMin = "10.0", UIMin = "10.0"))
	float Height = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Properties", meta = (ClampMin = "1", UIMin = "1"))
	int32 SubdivisionsX = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Properties", meta = (ClampMin = "1", UIMin = "1"))
	int32 SubdivisionsY = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper Properties")
	UMaterialInterface* PaperMaterial;

	// Create the paper mesh
	void CreatePaperMesh();

private:
	// Helper function to generate a flat plane
	void GeneratePlaneMesh(float MeshWidth, float MeshHeight, int32 MeshSubdivisionsX, int32 MeshSubdivisionsY,
	                       TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals,
	                       TArray<FVector2D>& UVs);
};
