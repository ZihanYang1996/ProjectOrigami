// Fill out your copyright notice in the Description page of Project Settings.


#include "TempFiles/ProceduralMeshTest.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AProceduralMeshTest::AProceduralMeshTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and initialize the Procedural Mesh Component
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	RootComponent = ProceduralMesh;
}

void AProceduralMeshTest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Generate the paper mesh when the actor is constructed
	CreatePaperMesh();
}

// Called when the game starts or when spawned
void AProceduralMeshTest::BeginPlay()
{
	Super::BeginPlay();
	//
	// // Generate the paper mesh at startup
	// CreatePaperMesh();
}

// Called every frame
void AProceduralMeshTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Generates the paper mesh
void AProceduralMeshTest::CreatePaperMesh()
{
    // Arrays for mesh data
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;

    // Generate a flat plane with specified parameters
    GeneratePlaneMesh(Width, Height, SubdivisionsX, SubdivisionsY, Vertices, Triangles, Normals, UVs);

	UE_LOG(LogTemp, Warning, TEXT("Vertices Count: %d"), Vertices.Num());
	UE_LOG(LogTemp, Warning, TEXT("Triangles Count: %d"), Triangles.Num());

    // Placeholder for additional mesh data
    TArray<FLinearColor> VertexColors;  // For coloring vertices (optional, not used here)
    TArray<FProcMeshTangent> Tangents;  // Tangent data for lighting (optional, not used here)

    // Create the procedural mesh section
    ProceduralMesh->CreateMeshSection_LinearColor(
        0,         // Section Index (0 for the first section)
        Vertices,  // Array of vertices
        Triangles, // Array of triangle indices
        Normals,   // Array of normals
        UVs,       // Array of UV coordinates for texturing
        VertexColors,  // Array of vertex colors (empty here)
        Tangents,  // Array of tangents (empty here)
        true       // Enable collision (true for interactable meshes)
    );

	if (PaperMaterial)
	{
		ProceduralMesh->SetMaterial(0, PaperMaterial);
	}
}

// Generates a flat plane mesh
void AProceduralMeshTest::GeneratePlaneMesh(float MeshWidth, float MeshHeight, int32 MeshSubdivisionsX, int32 MeshSubdivisionsY,
									TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals,
									TArray<FVector2D>& UVs)
{
	// Clear arrays to avoid duplicates
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	UVs.Empty();

	// Calculate step size for vertices based on subdivisions
	const float StepX = MeshWidth / MeshSubdivisionsX;
	const float StepY = MeshHeight / MeshSubdivisionsY;

	// Generate vertices, normals, and UVs
	for (int32 Y = 0; Y <= MeshSubdivisionsY; ++Y)
	{
		for (int32 X = 0; X <= MeshSubdivisionsX; ++X)
		{
			// Vertex position
			Vertices.Add(FVector(X * StepX, Y * StepY, 0.0f));

			// Normal (pointing upwards)
			Normals.Add(FVector(0.0f, 0.0f, 1.0f));

			// UV coordinates (scaled from 0 to 1)
			UVs.Add(FVector2D(X / static_cast<float>(MeshSubdivisionsX), Y / static_cast<float>(MeshSubdivisionsY)));
		}
	}

	// Generate triangles (two per quad)
	for (int32 Y = 0; Y < MeshSubdivisionsY; ++Y)
	{
		for (int32 X = 0; X < MeshSubdivisionsX; ++X)
		{
			// Indices of the quad's corners
			const int32 BottomLeft = X + (Y * (MeshSubdivisionsX + 1));
			const int32 BottomRight = BottomLeft + 1;
			const int32 TopLeft = BottomLeft + MeshSubdivisionsX + 1;
			const int32 TopRight = TopLeft + 1;

			// Triangle 1
			Triangles.Add(BottomLeft);
			Triangles.Add(TopLeft);
			Triangles.Add(TopRight);

			// Triangle 2
			Triangles.Add(BottomLeft);
			Triangles.Add(TopRight);
			Triangles.Add(BottomRight);

			// Add triangles for the bottom side (flipped winding order)
			Triangles.Add(TopRight);
			Triangles.Add(TopLeft);
			Triangles.Add(BottomLeft);

			Triangles.Add(BottomRight);
			Triangles.Add(TopRight);
			Triangles.Add(BottomLeft);
		}
	}
}

