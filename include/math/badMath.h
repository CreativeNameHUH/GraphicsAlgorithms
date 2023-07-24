#ifndef GRAPHICSALGORITHMS_BADMATH_H
#define GRAPHICSALGORITHMS_BADMATH_H

#include "vec2.h"

inline static float* linspace(float start, float end, uint32_t numberOfItems)
{
    if (!numberOfItems)
        return nullptr;

    float* linspaceArray = new float[numberOfItems];
    if (numberOfItems == 1)
    {
        linspaceArray[0] = start;
        return linspaceArray;
    }

    float delta = (end - start) / (numberOfItems--);
    for (uint32_t index = 0; index < numberOfItems; ++index)
           linspaceArray[index] = start + delta * index;

    linspaceArray[numberOfItems] = end;
    return linspaceArray;
}

inline static Array<float> derivatives(const Points& points)
{
    uint32_t pointsSize = points.size();

    Array<float> dy(pointsSize);
    dy.append((points[1].y - points[0].y) / (points[1].x - points[0].x));

    pointsSize--;
    for (uint32_t index = 1; index < pointsSize; index++)
    {
        const float h0 = points[index].x - points[index - 1].x;
        const float h1 = points[index + 1].x - points[index].x;

        dy.append(((h1 * (points[index].y - points[index - 1].y)) * (h0 * (points[index + 1].y - points[index].y))) / (h0 + h1));
    }

    dy.append((points[pointsSize - 1].y - points[pointsSize - 2].y) / (points[pointsSize - 1].x - points[pointsSize - 2].x));

    return dy;
}

inline static uint32_t interval(const Points& points, float t)
{
    const uint32_t pointsSize = points.size() - 1;
    for (uint32_t index = 0; index < pointsSize; index++)
        if (points[index].x <= t <= points[index + 1].x)
            return index;

    return pointsSize - 1;
}

#endif //GRAPHICSALGORITHMS_BADMATH_H
