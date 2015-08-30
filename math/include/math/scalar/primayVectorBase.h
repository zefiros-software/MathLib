#pragma once
#ifndef __INTEGER_VECTOR_H__
#define __INTEGER_VECTOR_H__

#include "math/config.h"
#include "math/scalar/genericVectorData.h"

template< class TYPE, U32 N >
class PrimayVectorBase : public GenericVectorData< TYPE, N >
{
public:

    // STATICS
    static U32 GetLength()
    {
        return N;
    }

    // Accessors
    inline const TYPE & operator[](U32 i) const
    {
        assert(i < N);

        return this->mValues[i];
    }

    inline TYPE &operator[](U32 i)
    {
        assert(i < N);

        return this->mValues[i];
    }

    // Self operators
    inline PrimayVectorBase< TYPE, N > &operator+=(const PrimayVectorBase< TYPE, N > &v)
    {
        for (U32 i = 0; i < N; ++i)
        {
            this->mValues[i] += v[i];
        }

        return *(PrimayVectorBase< TYPE, N >*)this;
    }

    inline PrimayVectorBase< TYPE, N > &operator /= (const TYPE s)
    {
        assert(s != 0.0f);

        for (U32 i = 0; i < N; ++i)
        {
            this->mValues[i] /= s;
        }

        return *(PrimayVectorBase< TYPE, N >*)this;
    }

    inline PrimayVectorBase< TYPE, N > &operator *= (const TYPE s)
    {
        for (U32 i = 0; i < N; ++i)
        {
            this->mValues[i] *= s;
        }

        return *(PrimayVectorBase< TYPE, N >*)this;
    }

    // Equality
    inline bool operator==(const PrimayVectorBase< TYPE, N > &other) const
    {
        bool result = true;

        for (U32 i = 0; i < N; ++i)
        {
            result &= Mathf::Equal(this->mValues[i], other.mValues[i]);
        }

        return result;
    }

    inline bool operator!=(const PrimayVectorBase< TYPE, N > &other) const
    {
        return !(PrimayVectorBase< TYPE, N >(*this) == other);
    }

    // Internal intrinsics
    inline TYPE Dot(const PrimayVectorBase< TYPE, N > &v) const
    {
        TYPE result = this->mValues[0] * v.mValues[0];

        for (U32 i = 1; i < N; ++i)
        {
            result += this->mValues[i] * v.mValues[i];
        }

        return  result;
    }

    inline TYPE Length2() const
    {
        return Dot(PrimayVectorBase< TYPE, N >(*this));
    }

    inline TYPE Distance2(const PrimayVectorBase< TYPE, N > &v) const
    {
        return (PrimayVectorBase< TYPE, N >(*this) - v).Length2();
    }

    inline void SetValue(U32 axis, TYPE val)
    {
        this->mValues[axis] = val;
    }

    inline PrimayVectorBase< TYPE, N > Absolute() const
    {
        PrimayVectorBase< TYPE, N > newVec;

        for (U32 i = 0; i < N; ++i)
        {
            newVec.SetValue(i, Mathf::Abs(this->mValues[i]));
        }

        return newVec;
    }

    inline U8 MinAxis() const
    {
        U8 axis = 0;
        TYPE val = this->mValues[0];

        for (U8 i = 1; i < N; ++i)
        {
            const TYPE considerate = this->mValues[i];

            if (considerate < val)
            {
                val = considerate;
                axis = i;
            }
        }

        return axis;
    }

    inline U8 MaxAxis() const
    {
        U8 axis = 0;
        TYPE val = this->mValues[0];

        for (U8 i = 1; i < N; ++i)
        {
            const TYPE considerate = this->mValues[i];

            if (considerate > val)
            {
                val = considerate;
                axis = i;
            }
        }

        return axis;
    }

    inline void SetZero()
    {
        for (U32 i = 0; i < N; ++i)
        {
            SetValue(i, 0);
        }
    }

    inline bool IsZero() const
    {
        bool result = true;

        for (U32 i = 0; i < N; ++i)
        {
            result &= (this->mValues[i] == 0);
        }

        return result;
    }

    inline bool IsFuzzyZero() const
    {
        return Length2() < Mathf::GetEpsilon();
    }

    inline void Clear()
    {
        SetZero();
    }
};

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator+(const PrimayVectorBase< TYPE, N > &v1, const PrimayVectorBase< TYPE, N > &v2)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = v1[i] + v2[i];
    }

    return newVec;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator*(const PrimayVectorBase< TYPE, N > &v1, const PrimayVectorBase< TYPE, N > &v2)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = v1[i] * v2[i];
    }

    return newVec;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator-(const PrimayVectorBase< TYPE, N > &v1, const PrimayVectorBase< TYPE, N > &v2)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = v1[i] - v2[i];
    }

    return newVec;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator-(const PrimayVectorBase< TYPE, N > &v)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = -v[i];
    }

    return newVec;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator*(const PrimayVectorBase< TYPE, N > &v, const TYPE s)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = v[i] * s;
    }

    return newVec;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator*(TYPE s, const PrimayVectorBase< TYPE, N > &v)
{
    return v * s;
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator/(const PrimayVectorBase< TYPE, N > &v, TYPE s)
{
    assert(s != 0.0f);
    return v * (Real(1.0) / s);
}

template< class TYPE, U32 N >
inline PrimayVectorBase< TYPE, N > operator/(const PrimayVectorBase< TYPE, N > &v1, const PrimayVectorBase< TYPE, N > &v2)
{
    PrimayVectorBase< TYPE, N > newVec;

    for (U32 i = 0; i < PrimayVectorBase< TYPE, N >::GetLength(); ++i)
    {
        newVec[i] = v1[i] / v2[i];
    }

    return newVec;
}


#endif