/*
 * queue.hpp
 *
 *  Created on: Jan 10, 2025
 *      Author: Ahmed Elsamadony
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstdint>
#include <array>

namespace utils
{

enum Result
{
    eEmpty = 0,
    eFull,
    eOk,
};

template <typename T, size_t QSize>
class Queue
{
public:
    Queue(std::array<T, QSize>& arrayRef):
        mDataBuffer(arrayRef),
        mFront(),
        mRear(),
        mCount(){}

    Result Enqueue(T const &item)
    {
        if (IsFull())
        {
            return eFull;
        }
        mDataBuffer[mRear] = item;
        mRear = (mRear + 1) % QSize;
        ++mCount;
        return eOk;
    }

    Result Dequeue()
    {
        if (IsEmpty())
        {
            return eEmpty;
        }
        mFront = (mFront + 1) % QSize;
        --mCount;
        return eOk;
    }

    Result Peek(T& item) const
    {
        if (IsEmpty())
        {
            return eEmpty;
        }
        item = mDataBuffer[mFront];
        return eOk;
    }
    
    size_t Size() const
    {
        return mCount;
    }

    bool IsEmpty() const
    {
        return (mCount == 0);
    }

    bool IsFull() const
    {
        return (mCount == QSize);
    }

private:
    std::array<T, QSize>& mDataBuffer;  ///< reference to an array of T
    size_t mFront;                      ///< front points to the front item in the Queue (if any)
    size_t mRear;                       ///< rear points to the last item in the Queue
    size_t mCount;                      ///< current size of the Queue
};

}// namespace utils

#endif // QUEUE_H