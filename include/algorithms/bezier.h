#ifndef GRAPHICSALGORITHMS_BEZIER_H
#define GRAPHICSALGORITHMS_BEZIER_H

#include "../math/badMath.h"

class Bezier
{
public:
    static Points quadraticBezier(const Vec2<float> &pointFrom, const Vec2<float> &controlPoint, const Vec2<float> &pointTo,
                                  uint32_t numberOfPoints)
    {
        if (!numberOfPoints)
            return Points();

        float *ts = linspace(0, 1, numberOfPoints);

        Points points{};
        points.reserve(numberOfPoints);
        for (uint32_t index = 0; index < numberOfPoints; index++)
        {
            const float t = ts[index];
            const float tSquare = t * t;

            const float a = 1 - t;
            const float aSquare = a * a;

            const float b = 2 * a * t;

            const float x = aSquare * pointFrom.x + b * controlPoint.x + tSquare * pointTo.x;
            const float y = aSquare * pointFrom.y + b * controlPoint.y + tSquare * pointTo.y;

            points.append(Vec2<float>(x, y));
        }

        delete[] ts;
        return points;
    }

    static Points cubicBezier(const Vec2<float> &pointFrom, const Vec2<float> &controlPointA, const Vec2<float> &controlPointB,
                              const Vec2<float> &pointTo, uint32_t numberOfPoints)
    {
        float *ts = linspace(0, 1, numberOfPoints);

        Points points;
        points.reserve(numberOfPoints);
        for (uint32_t index = 0; index < numberOfPoints; index++)
        {
            const float t = ts[index];
            const float tSquare = t * t;
            const float tCube = tSquare * t;

            const float a = 1 - t;
            const float aSquare = a * a;
            const float aCube = aSquare * a;

            const float b = 3 * aSquare * t;

            const float c = 3 * a * tSquare;

            const float x = aCube * pointFrom.x + b * controlPointA.x + c * controlPointB.x + tCube * pointTo.x;
            const float y = aCube * pointFrom.y + b * controlPointA.y + c * controlPointB.y + tCube * pointTo.y;

            points.append(Vec2<float>(x, y));
        }

        delete[] ts;
        return points;
    }
};

#endif //GRAPHICSALGORITHMS_BEZIER_H
