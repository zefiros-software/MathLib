/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */

#pragma once
#ifndef __ENGINE_VEC2_H__
#define __ENGINE_VEC2_H__

#include "math/types.h"
#include "math/mathf.h"

#include <assert.h>
#include <cstddef>

template< class tN >
class Vector2;

typedef Vector2< F32 > Vec2f;
typedef Vector2< F64 > Vec2d;
typedef Vector2< S32 > Vec2i;
typedef Vector2< U32 > Vec2u;
typedef Vector2< Scalar > Vec2;


template< class tN >
class Vector2
{
    template< class T >
    friend Vector2< T > operator+(const Vector2< T > &, const Vector2< T > &);

    template< class T >
    friend Vector2< T > operator*(const Vector2< T > &, const Vector2< T > &);

    template< class T >
    friend Vector2< T > operator-(const Vector2< T > &, const Vector2< T > &);

    template< class T >
    friend Vector2< T > operator-(const Vector2< T > &);

    template< class T, class N >
    friend Vector2< T > operator*(const Vector2< T > &, N);

    template< class T, class N >
    friend Vector2< T > operator*(N, const Vector2< T > &);

    template< class T, class N >
    friend Vector2< T > operator/(const Vector2< T > &, N);

    template< class T >
    friend Vector2< T > operator/(const Vector2< T > &, const Vector2< T > &);

public:


    inline Vector2()
    {
        mValues[0] = (tN)0.0;
        mValues[1] = (tN)0.0;
    }


    inline Vector2(tN num)
    {
        mValues[0] = num;
        mValues[1] = num;
    }


    template< class tT >
    inline Vector2(tT x, tT y)
    {
        mValues[0] = (tN)x;
        mValues[1] = (tN)y;
    }


    template< class tT >
    inline Vector2(const Vector2< tT > &v)
    {
        mValues[0] = (tN)v.X();
        mValues[1] = (tN)v.Y();
    }


    inline Vec2i ToVec2i() const
    {
        return Vec2i((S32) mValues[0],
                     (S32) mValues[1]);
    }


    inline Vector2 &operator=(const Vector2 &other)
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];

        return *this;
    }


    inline Vector2 &operator-=(const Vector2 &v)
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];

        return *this;
    }


    inline Vector2 &operator+=(const Vector2 &v)
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];

        return *this;
    }


    inline Vector2 &operator/=(tN s)
    {
        assert(s != 0.0);

        mValues[0] /= s;
        mValues[1] /= s;

        return *this;
    }


    inline Vector2 &operator*=(tN s)
    {
        mValues[0] *= s;
        mValues[1] *= s;

        return *this;
    }


    inline bool operator==(const Vector2 &other) const
    {
        return Mathf::Equal< tN >(mValues[0], other.mValues[0]) && Mathf::Equal< tN >(mValues[1], other.mValues[1]);
    }


    inline bool operator!=(const Vector2 &other) const
    {
        return !(*this == other);
    }


    inline tN &operator[](U32 axis)
    {
        return mValues[ axis ];
    }


    inline tN operator[](U32 axis) const
    {
        return mValues[ axis ];
    }

    inline tN *Data()
    {
        return &mValues[0];
    }

    inline const tN *Data() const
    {
        return &mValues[0];
    }

    inline void Set(tN x, tN y)
    {
        mValues[0] = x;
        mValues[1] = y;
    }


    inline tN Dot(const Vector2 &v) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1];
    }


    inline Scalar Length2() const
    {
        return (Scalar)Dot(*this);
    }


    inline Scalar Length() const
    {
        return Mathf::Sqrt(Length2());
    }


    inline Scalar Distance2(const Vector2 &v) const
    {
        return (*this - v).Length2();
    }


    inline Scalar Distance(const Vector2 &v) const
    {
        return (*this - v).Length();
    }


    inline Vector2 SafeNormalise()
    {
        Vector2 absv = Absolute();
        U32 max = absv.MaxAxis();

        if (absv.mValues[max] > 0)
        {
            *this /= absv.mValues[max];
            return *this /= (tN)Length();
        }

        Set((tN)1.0, (tN)0.0);
        return *this;
    }


    inline Vector2 Normalise()
    {
        assert(Length() != 0.0);

        return *this /= (tN)Length();
    }


    inline Vector2 Lerp(const Vector2 &v, Scalar t) const
    {
        return Vector2(mValues[0] + (v.mValues[0] - mValues[0]) * t, mValues[1] + (v.mValues[1] - mValues[1]) * t);
    }


    inline Vector2 Nlerp(const Vector2 &v, Scalar t) const
    {
        return Lerp(v, t).Normalise();
    }


    inline Vector2 Rotate(Scalar angle) const
    {
        return Vector2(Mathf::Cos(angle) * mValues[0] - Mathf::Sin(angle) * mValues[1],
                       Mathf::Sin(angle) * mValues[0] - Mathf::Cos(angle) * mValues[1]);
    }


    inline Vector2 Absolute() const
    {
        return Vector2(Mathf::Abs(mValues[0]), Mathf::Abs(mValues[1]));
    }


    inline U32 MinAxis() const
    {
        return mValues[0] < mValues[1] ? 0 : 1;
    }


    inline U32 MaxAxis() const
    {
        return mValues[0] > mValues[1] ? 0 : 1;
    }


    inline Scalar Angle(const Vector2 &v) const
    {
        const Scalar s = Mathf::Sqrt(Length2() * v.Length2());

        assert(s != 0.0);

        return Mathf::Acos((Scalar)Mathf::Clamp< Scalar >(Dot(v) / s, -1.0, 1.0));
    }


    inline void X(tN x)
    {
        mValues[0] = x;
    }


    inline tN X() const
    {
        return mValues[0];
    }


    inline void Y(tN y)
    {
        mValues[1] = y;
    }


    inline tN Y() const
    {
        return mValues[1];
    }


    inline bool IsZero() const
    {
        return mValues[0] == 0.0 && mValues[1] == 0.0;
    }


    inline bool IsFuzzyZero() const
    {
        return Length2() <= Mathf::Epsilon< tN >() * 10;
    }


    inline void Clear()
    {
        Set((tN)0.0, (tN)0.0);
    }


    static inline Vector2 Zeros()
    {
        return Vector2(0.0, 0.0);
    }


    static inline Vector2 Ones()
    {
        return Vector2(1.0, 1.0);
    }


    static inline Vector2 Down()
    {
        return Vector2(0.0, -1.0);
    }


    static inline Vector2 Up()
    {
        return Vector2(0.0, 1.0);
    }


    static inline Vector2 Left()
    {
        return Vector2(-1.0, 0.0);
    }


    static inline Vector2 Right()
    {
        return Vector2(1.0, 0.0);
    }

private:

    tN mValues[2];
};


template< class tN >
inline Vector2< tN > operator+(const Vector2< tN > &v1, const Vector2< tN > &v2)
{
    return Vector2< tN >(v1.mValues[0] + v2.mValues[0],
                         v1.mValues[1] + v2.mValues[1]);
}


template< class tN >
inline Vector2< tN > operator*(const Vector2< tN > &v1, const Vector2< tN > &v2)
{
    return Vector2< tN >(v1.mValues[0] * v2.mValues[0],
                         v1.mValues[1] * v2.mValues[1]);
}


template< class tN >
inline Vector2< tN > operator-(const Vector2< tN > &v1, const Vector2< tN > &v2)
{
    return Vector2< tN >(v1.mValues[0] - v2.mValues[0],
                         v1.mValues[1] - v2.mValues[1]);
}


template< class tN >
inline Vector2< tN > operator-(const Vector2< tN > &v)
{
    return Vector2< tN >(-v.mValues[0], -v.mValues[1]);
}


template< class tN, class tT >
inline Vector2< tN > operator*(const Vector2< tN > &v, tT s)
{
    return Vector2< tN >(v.mValues[0] * s, v.mValues[1] * s);
}


template< class tN, class tT >
inline Vector2< tN > operator*(tT s, const Vector2< tN > &v)
{
    return v * s;
}


template< class tN, class tT >
inline Vector2< tN > operator/(const Vector2< tN > &v, tT s)
{
    assert(s != 0.0);

    return Vector2< tN >(v) /= s;
}


template< class tN >
inline Vector2< tN > operator/(const Vector2< tN > &v1, const Vector2< tN > &v2)
{
    return Vector2< tN >(v1.mValues[0] / v2.mValues[0],
                         v1.mValues[1] / v2.mValues[1]);
}

#endif