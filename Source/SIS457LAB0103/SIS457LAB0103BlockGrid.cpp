// Copyright Epic Games, Inc. All Rights Reserved.

#include "SIS457LAB0103BlockGrid.h"
#include "SIS457LAB0103Block.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ASIS457LAB0103BlockGrid::ASIS457LAB0103BlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Mi nombre es Alexander Paul Fernandez Acho, nacido el 8 de abril del 2003, segundo hijo de los señores Jaime Fernandez Cervantes y Ruth Bethzabeth Acho Sánchez.Graduado del colegio San Juanillo con honores el año 2020 con conociminetos deradioelectrónica y electricidad.Egresado del Centro Boliviano Americano(CBA) con conocimientosde ingles avanzado.Vivo en la ciudad de Sucre - Bolivia desde que nací,aunque siempre quise vivir en Santa Cruz.Me gusta el Voleyball y los videojuegos, me gusta ser competitivo en esas cosas.Ingresé a la Carrera de Ingeniería de Sistemas porque me llama mucho la atención,tomando en cuenta de que es de las carreras con más demanda en los últimos años."), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 0;
	BlockSpacing = 300.f;
}


void ASIS457LAB0103BlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ASIS457LAB0103Block* NewBlock = GetWorld()->SpawnActor<ASIS457LAB0103Block>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}


void ASIS457LAB0103BlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Mi nombre es Alexander Paul Fernandez Acho, nacido el 8 de abril del 2003, segundo hijo de los señores Jaime Fernandez Cervantes y Ruth Bethzabeth Acho Sánchez.Graduado del colegio San Juanillo con honores el año 2020 con conociminetos deradioelectrónica y electricidad.Egresado del Centro Boliviano Americano(CBA) con conocimientosde ingles avanzado.Vivo en la ciudad de Sucre - Bolivia desde que nací,aunque siempre quise vivir en Santa Cruz.Me gusta el Voleyball y los videojuegos, me gusta ser competitivo en esas cosas.Ingresé a la Carrera de Ingeniería de Sistemas porque me llama mucho la atención,tomando en cuenta de que es de las carreras con más demanda en los últimos años."), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
