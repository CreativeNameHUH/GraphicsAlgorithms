#ifndef GRAPHICSALGORITHMS_HERMITE_H
#define GRAPHICSALGORITHMS_HERMITE_H

#include "../math/badMath.h"

class HermiteInterpolation
{
public:
    inline static Points hermiteInterpolation(const Points& points, uint32_t numberOfPoints)
    {
        const float* ts = linspace(points[0].x, points[points.size() - 1].x, numberOfPoints);
        Array<float> dy = derivatives(points);

        Points interpolatedPoints;
        interpolatedPoints.reserve(numberOfPoints);

        for (uint32_t index = 0; index < numberOfPoints; index++)
        {
            const float t = ts[index];
            const uint32_t i = interval(points, t);
            const float height = points[i + 1].x - points[i].x;

            const float tNormalized = (t - points[i].x) / height;
            const float tNormalizedSquare = tNormalized * tNormalized;
            const float tNormalizedCube = tNormalizedSquare * tNormalized;

            const float tA = 2 * tNormalizedCube;
            const float tB = 3 * tNormalizedSquare;

            const float h0 = tA - tB + 1;
            const float h1 = -tA + tB;
            const float h2 = tNormalizedCube - 2 * tNormalizedSquare + tNormalized;
            const float h3 = tNormalizedCube - tNormalizedSquare;

            interpolatedPoints.append(Vec2<float>(h0 * points[i].y + h1 * points[i + 1].y + h2 * height * dy[i] + h3 * height * dy[i + 1], t));
        }

        delete[] ts;
        return interpolatedPoints;
    }
};

#endif //GRAPHICSALGORITHMS_HERMITE_H
