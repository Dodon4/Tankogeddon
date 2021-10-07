// Fill out your copyright notice in the Description page of Project Settings.


#include "SMiniMap.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMiniMap::Construct(const FArguments & InArgs)
{
    PlayerImage = InArgs._PlayerImage;

    /*ChildSlot
    [

    ];*/
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SMiniMap::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    FVector2D localSize = AllottedGeometry.GetLocalSize();

    FSlateBrush brush;
    brush.SetResourceObject(PlayerImage); // PlayerImage это UTexture2D, его можно передать через аргумент или атрибут

    // Рисуем границу уровня, желательно передавать border через атрибут или аргумент, чтобы их можно было быстро и удобно менять через БП

    TArray<FVector2D> border;
    border.Add(localSize * FVector2D(0.f, 0.f));
    border.Add(localSize * FVector2D(0.f, 1.f));
    border.Add(localSize * FVector2D(1.f, 1.f));
    border.Add(localSize * FVector2D(1.f, 0.f));
    border.Add(localSize * FVector2D(0.f, 0.f));

    FSlateDrawElement::MakeLines(
        OutDrawElements,
        LayerId,
        AllottedGeometry.ToPaintGeometry(),
        border
    );

    // Рисуем препятствия на карте, поскольку БП не поддерживаем вложенные массивы (TArray<TArray<FVector2D>>), а нам нужно задать сразу
    // много препядствий, используем массив FBox2D, который содержит в себе 2 FVector

    TArray<FBox2D> obstacles;
    // X Y
    obstacles.Add(FBox2D(localSize * FVector2D(0.4f, 0.4f), localSize * FVector2D(1.f, 0.4f)));
    obstacles.Add(FBox2D(localSize * FVector2D(0.45f, 0.4f), localSize * FVector2D(0.45f, 0.2f)));
    obstacles.Add(FBox2D(localSize * FVector2D(0.1f, 0.4f), localSize * FVector2D(0.1f, 1.f)));

    for (auto& obs : obstacles)
    {
        TArray<FVector2D> points;
        points.Add(obs.Min);
        points.Add(obs.Max);

        FSlateDrawElement::MakeLines(
            OutDrawElements,
            LayerId,
            AllottedGeometry.ToPaintGeometry(),
            points
        );
    }
    // Игрок
    FSlateDrawElement::MakeBox(
        OutDrawElements,
        LayerId,
        AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.7f, 0.7f), brush.ImageSize),
        &brush,
        ESlateDrawEffect::None,
        FLinearColor::Green
    );
    // Враги
    FSlateDrawElement::MakeBox(
        OutDrawElements,
        LayerId,
        AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.3f, 0.7f), brush.ImageSize),
        &brush,
        ESlateDrawEffect::None,
        FLinearColor::Red
    );

    FSlateDrawElement::MakeBox(
        OutDrawElements,
        LayerId,
        AllottedGeometry.ToPaintGeometry(localSize * FVector2D(0.2f, 0.75f), brush.ImageSize),
        &brush,
        ESlateDrawEffect::None,
        FLinearColor::Red
    );
    return 0;
}
