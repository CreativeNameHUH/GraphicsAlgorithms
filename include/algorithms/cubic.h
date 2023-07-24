#ifndef GRAPHICSALGORITHMS_CUBIC_H
#define GRAPHICSALGORITHMS_CUBIC_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"

#include "../math/badMath.h"

class CubicInterpolation
{
public:
    inline static Points cubicInterpolation(const Points& points, uint32_t numberOfPoints)
    {
        float const* ts = linspace(0, 1, numberOfPoints);

        Points interpolatedPoints;
        interpolatedPoints.reserve(numberOfPoints);

        for (uint32_t index = 0; index < numberOfPoints; index++)
        {
            const float t = ts[index];
            uint32_t i = interval(points, t);
            float* coefficients = calculateCoefficients(&points, i);

            interpolatedPoints.append(Vec2<float>(t, cubicSpline(points[i].x, t, coefficients)));

            delete[] coefficients;
        }

        delete[] ts;
        return interpolatedPoints;
    }

private:
    static constexpr float ONE_THIRD = 1 / 3;
    static constexpr float ONE_MINUS_ONE_THIRD = 1 - ONE_THIRD;

    inline static float* calculateCoefficients(const Points* points, uint32_t index)
    {
        const Vec2<float>* pointA = &points->operator[](index + 1);
        const Vec2<float>* pointB = &points->operator[](index);

        const float height = pointA->x - pointB->x;

        float* coefficients = new float[4];
        coefficients[0] = pointB->y;             // lower limit
        coefficients[1] = pointA->y - pointB->y; // upper limit

        float t = coefficients[1] / height;

        const Vec2<float>* pointC = &points->operator[](index - 1);
        if (index)
            t = ONE_MINUS_ONE_THIRD * t + ONE_THIRD * ((pointB->y - pointC->y) / (pointB->x - pointC->y));

        pointC = &points->operator[](index + 2);
        if (index < points->size() - 2)
            t = ONE_MINUS_ONE_THIRD * t + ONE_THIRD * ((pointB->y - pointC->y) / (pointB->x - pointC->y));

        const float heightSquare = height * height;

        coefficients[2] = (3 * (pointA->y - pointB->y) - 2 * t * height - (pointC->y - pointB->y)) / heightSquare;
        coefficients[3] = (t * (pointB->y - pointA->y) + (pointC->y - pointB->y)) / (heightSquare * height);

        return coefficients;
    }

    inline static float cubicSpline(const float x, const float t, const float* coefficients)
    {
        float dt = t - x;
        return coefficients[0] + coefficients[1] * dt + coefficients[2] * dt + coefficients[3] * (dt * dt * dt);
    }
};
#endif //GRAPHICSALGORITHMS_CUBIC_H

#pragma clang diagnostic pop