#ifndef GRAPHICSALGORITHMS_ARRAY_H
#define GRAPHICSALGORITHMS_ARRAY_H

#include <cstdint>
#include <stdexcept>

template <typename T>
class Array
{
public:
    inline explicit Array(uint32_t capacity = 1) : mCapacity(capacity)
    {
        mData = static_cast<T*>(::operator new(mCapacity * sizeof(T)));
    }

    inline Array(const Array& array) : mSize(array.mSize)
    {
        for (uint32_t i = 0; i < mSize; i++)
            new (&mData[i]) T(array.mData[i]);
    }

    inline Array(Array&& array) noexcept
    {
        swap(array);
    }

    inline ~Array()
    {
        clear();
        ::operator delete(mData);
    }

    inline Array& operator=(const Array& array)
    {
        if (this == &array)
            return *this;

        delete[] mData;
        mSize = array.mSize;
        mData = new T[mSize];
        memcpy(mData, array.mData, mSize * sizeof(T));
    }

    inline Array& operator=(Array&& array) noexcept
    {
        if (this == &array)
            return *this;

        clear();
        ::operator delete(mData);

        mData = array.mData;
        mSize = array.mSize;
        mCapacity = array.mCapacity;

        array.mData = nullptr;
        array.mSize = 0;
        array.mCapacity = 0;

        return *this;
    }

    inline T& operator[](uint32_t index) const
    {
        return get(index);
    }

    inline void append(const T& item)
    {
        if (mCapacity == mSize)
            reserve(mCapacity + 1);

        new (&mData[mSize]) T(item);
        mSize++;
    }

    inline void reserve(uint32_t capacity)
    {
        if (capacity <= mCapacity)
            return;

        T* newArray = static_cast<T*>(::operator new(capacity * sizeof(T)));

        for (uint32_t index = 0; index < mSize; index++)
        {
            new (&newArray[index]) T(std::move(mData[index]));
            mData[index].~T();
        }

        ::operator delete(mData);

        mData = newArray;
        mCapacity = capacity;
    }

    inline void resize(uint32_t size)
    {
        if (size <= mSize)
        {
            for (uint32_t index = size; index < mSize; index++)
                mData[index].~T();

            mSize = size;
            return;
        }

        if (size > mCapacity)
            reserve(size);

        for (uint32_t index = mSize; index < size; index++)
            new (&mData[index]) T();

        mSize = size;
    }

    inline void clear()
    {
        for (uint32_t index = 0; index < mSize; index++)
            mData[index].~T();

        mSize = 0;
    }

    inline void swap(Array& array) noexcept
    {
        std::swap(mData, array.mData);
        std::swap(mSize, array.mSize);
        std::swap(mCapacity, array.mCapacity);
    }

    inline T& get(uint32_t index) const
    {
        if (index >= mSize)
            throw std::out_of_range("Index out of range!");

        return mData[index];
    }

    inline T* data() const
    {
        return mData;
    }

    inline uint32_t size() const
    {
        return mSize;
    }

    inline uint32_t capacity() const
    {
        return mCapacity;
    }

private:
    T* mData = nullptr;

    uint32_t mSize = 0;
    uint32_t mCapacity = 0;
};

#endif //GRAPHICSALGORITHMS_ARRAY_H
