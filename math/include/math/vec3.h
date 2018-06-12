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
#ifndef __ENGINE_VEC3_H__
#define __ENGINE_VEC3_H__

#include "math/types.h"
#include "math/mathf.h"
#include "math/vec2.h"

#include <assert.h>
#include <cstddef>

template< class tN >
class Vector3;

typedef Vector3< F32 > Vec3f;
typedef Vector3< F64 > Vec3d;
typedef Vector3< S32 > Vec3i;
typedef Vector3< U32 > Vec3u;
typedef Vector3< Scalar > Vec3;

template< class tN >
class Vector3
{
    template< class T >
    friend Vector3< T > operator+(const Vector3< T > &, const Vector3< T > &);

    template< class T >
    friend Vector3< T > operator*(const Vector3< T > &, const Vector3< T > &);

    template< class T >
    friend Vector3< T > operator-(const Vector3< T > &, const Vector3< T > &);

    template< class T >
    friend Vector3< T > operator-(const Vector3< T > &);

    template< class T, class N  >
    friend Vector3< T > operator*(const Vector3< T > &, N);

    template< class T, class N  >
    friend Vector3< T > operator*(N, const Vector3< T > &);

    template< class T, class N  >
    friend Vector3< T > operator/(const Vector3< T > &, N);

    template< class T >
    friend Vector3< T > operator/(const Vector3< T > &, const Vector3< T > &);

public:

    inline Vector3()
    {
        mValues[0] = (tN)0.0;
        mValues[1] = (tN)0.0;
        mValues[2] = (tN)0.0;
    }


    inline Vector3(tN num)
    {
        mValues[0] = (tN)num;
        mValues[1] = (tN)num;
        mValues[2] = (tN)num;
    }

    template< class tT >
    inline Vector3(tT x, tT y, tT z)
    {
        mValues[0] = (tN)x;
        mValues[1] = (tN)y;
        mValues[2] = (tN)z;
    }

    template< class tT >
    inline Vector3(const Vector3< tT > &v)
    {
        mValues[0] = (tN)v.X();
        mValues[1] = (tN)v.Y();
        mValues[2] = (tN)v.Z();
    }

    template< class tT >
    inline Vector3(const Vector2< tT > &v, tN z)
    {
        mValues[0] = (tN)v[0];
        mValues[1] = (tN)v[1];
        mValues[2] = z;
    }

    template< class tT >
    inline Vector3(tN x, const Vector2< tT > &v)
    {
        mValues[0] = x;
        mValues[1] = (tN)v[0];
        mValues[2] = (tN)v[1];
    }

    inline Vector3 &operator=(const Vector3< tN> &other)
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];

        return *this;
    }

    inline Vector3 &operator-=(const Vector3 &v)
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];
        mValues[2] -= v.mValues[2];

        return *this;
    }

    inline Vector3 &operator+=(const Vector3 &v)
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];
        mValues[2] += v.mValues[2];

        return *this;
    }

    inline Vector3 &operator/=(tN s)
    {
        assert(s != 0.0f);

        mValues[0] /= s;
        mValues[1] /= s;
        mValues[2] /= s;

        return *this;
    }

    inline Vector3 &operator*=(tN s)
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;

        return *this;
    }

    inline bool operator==(const Vector3 &other) const
    {
        return Mathf::Equal(mValues[0], other.mValues[0]) &&
               Mathf::Equal(mValues[1], other.mValues[1]) &&
               Mathf::Equal(mValues[2], other.mValues[2]);
    }

    inline bool operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    inline tN &operator[](size_t axis)
    {
        return mValues[ axis ];
    }

    inline tN operator[](size_t axis) const
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

    inline tN Dot(const Vector3 &v) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1] + mValues[2] * v.mValues[2];
    }

    inline Scalar Length2() const
    {
        return (Scalar)Dot(*this);
    }

    inline Scalar Length() const
    {
        return (Scalar)Mathf::Sqrt(Length2());
    }

    inline Scalar Distance2(const Vector3 &v) const
    {
        return (*this - v).Length2();
    }

    inline Scalar Distance(const Vector3 &v) const
    {
        return (*this - v).Length();
    }

    inline void Set(tN x, tN y, tN z)
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
    }

    inline Vector3 SafeNormalise()
    {
        Vector3 absv = Absolute();
        U8 max = absv.MaxAxis();

        if (absv.mValues[max] > 0)
        {
            assert(absv[max] != 0.0f);
            assert(Length() != 0.0f);

            *this /= absv.mValues[max];
            return *this /= (tN)Length();
        }

        Set((tN)1.0, (tN)0.0, (tN)0.0);
        return *this;
    }

    inline Vector3 Normalise()
    {
        assert(Length() != 0.0f);

        return *this /= (tN)Length();
    }

    inline Vector3 Lerp(const Vector3 &v, Scalar t) const
    {
        return Vector3(Mathf::Lerp(mValues[0], v.mValues[0], t),
                       Mathf::Lerp(mValues[1], v.mValues[1], t),
                       Mathf::Lerp(mValues[2], v.mValues[2], t));
    }

    inline Vector3 Slerp(const Vector3 &v, Scalar t) const
    {
        tN dotp = Dot(v);

        // Make sure the floating point accuracy doesn't
        // crash our program
        Mathf::Clamp< tN >(dotp, -1.0f, 1.0f);

        tN theta = Mathf::Acos(dotp) * t;
        Vector3 relative = v - *this * dotp;
        relative.Normalise();

        return *this * Mathf::Cos(theta) + relative * Mathf::Sin(theta);

    }

    inline Vector3 Nlerp(const Vector3 &v, Scalar t) const
    {
        return Lerp(v, t).Normalise();
    }

    inline Vector3 Rotate(const Vector3 &axis, Scalar angle) const
    {
        Vector3 v1 = axis * axis.Dot(*this);
        return v1 + (*this - v1) * Mathf::Cos(angle) + axis.Cross(*this) * Mathf::Sin(angle);
    }

    inline Vector3 Cross(const Vector3 &v) const
    {
        return Vector3(mValues[1] * v.mValues[2] - mValues[2] * v.mValues[1],
                       mValues[2] * v.mValues[0] - mValues[0] * v.mValues[2],
                       mValues[0] * v.mValues[1] - mValues[1] * v.mValues[0]);
    }

    inline Vector3 Absolute() const
    {
        return Vector3(Mathf::Abs(mValues[0]), Mathf::Abs(mValues[1]), Mathf::Abs(mValues[2]));
    }

    inline U8 MinAxis() const
    {
        return mValues[0] < mValues[1] ? (mValues[0] < mValues[2] ? 0 : 2) : (mValues[1] < mValues[2] ? 1 : 2);
    }

    inline U8 MaxAxis() const
    {
        return mValues[0] < mValues[1] ? (mValues[1] < mValues[2] ? 2 : 1) : (mValues[0] < mValues[2] ? 2 : 0);
    }

    inline Scalar Angle(const Vector3 &v) const
    {
        Scalar s = Mathf::Sqrt(Length2() * v.Length2());

        assert(s != 0.0f);

        return Mathf::Acos(Mathf::Clamp< Scalar >(Dot(v) / s, -1.0f, 1.0f));
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

    inline void Z(tN z)
    {
        mValues[2] = z;
    }

    inline tN Z() const
    {
        return mValues[2];
    }

    inline void Clear()
    {
        Set((tN)0.0, (tN)0.0, (tN)0.0);
    }

    inline bool IsZero() const
    {
        return mValues[0] == 0.0f && mValues[1] == 0.0f && mValues[2] == 0.0f;
    }

    inline bool IsFuzzyZero() const
    {
        return Length2() <= Mathf::Epsilon< tN >() * 10;
    }

    static inline Vector3 Zeros()
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    static inline Vector3 Ones()
    {
        return Vector3(1.0f, 1.0f, 1.0f);
    }

    static inline Vector3 Back()
    {
        return Vector3(0.0f, -1.0f, 0.0f);
    }

    static inline Vector3 Forward()
    {
        return Vector3(0.0f, 1.0f, 0.0f);
    }

    static inline Vector3 Down()
    {
        return Vector3(0.0f, 0.0f, -1.0f);
    }

    static inline Vector3 Up()
    {
        return Vector3(0.0f, 0.0f, 1.0f);
    }

    static inline Vector3 Left()
    {
        return Vector3(-1.0f, 0.0f, 0.0f);
    }

    static inline Vector3 Right()
    {
        return Vector3(1.0f, 0.0f, 0.0f);
    }

private:

    tN mValues[3];
};

template< class tN >
Vector3< tN > operator+(const Vector3< tN > &v1, const Vector3< tN > &v2)
{
    return Vector3< tN >(v1.mValues[0] + v2.mValues[0],
                         v1.mValues[1] + v2.mValues[1],
                         v1.mValues[2] + v2.mValues[2]);
}

template< class tN >
Vector3< tN > operator*(const Vector3< tN > &v1, const Vector3< tN > &v2)
{
    return Vector3< tN >(v1.mValues[0] * v2.mValues[0],
                         v1.mValues[1] * v2.mValues[1],
                         v1.mValues[2] * v2.mValues[2]);
}

template< class tN >
Vector3< tN > operator-(const Vector3< tN > &v1, const Vector3< tN > &v2)
{
    return Vector3< tN >(v1.mValues[0] - v2.mValues[0],
                         v1.mValues[1] - v2.mValues[1],
                         v1.mValues[2] - v2.mValues[2]);
}

template< class tN >
Vector3< tN > operator-(const Vector3< tN > &v)
{
    return Vector3< tN >(-v.mValues[0], -v.mValues[1], -v.mValues[2]);
}

template< class tN, class tT >
Vector3< tN > operator*(const Vector3< tN > &v, tT s)
{
    return Vector3< tN >(v.mValues[0] * s, v.mValues[1] * s, v.mValues[2] * s);
}

template< class tN, class tT >
Vector3< tN > operator*(tT s, const Vector3< tN > &v)
{
    return v * s;
}

template< class tN, class tT >
Vector3< tN > operator/(const Vector3< tN > &v, tT s)
{
    assert(s != 0.0f);

    return Vector3< tN >(v) /= s;
}

template< class tN >
Vector3< tN > operator/(const Vector3< tN > &v1, const Vector3< tN > &v2)
{
    return Vector3< tN >(v1.mValues[0] / v2.mValues[0],
                         v1.mValues[1] / v2.mValues[1],
                         v1.mValues[2] / v2.mValues[2]);
}


#endif