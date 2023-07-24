#ifndef GRAPHICSALGORITHMS_VEC2_H
#define GRAPHICSALGORITHMS_VEC2_H

#include "array.h"

template <typename T>
class Vec2
{
public:
    T x = 0;
    T y = 0;

    inline Vec2(T x, T y) : x(x), y(y) {}

    inline T& operator[](uint32_t index)
    {
        if (index > 1)
            throw std::out_of_range("Index out of bounds");

        if (!index)
            return x;

        return y;
    };
};

using Points = Array<Vec2<float>>;

#endif //GRAPHICSALGORITHMS_VEC2_H
