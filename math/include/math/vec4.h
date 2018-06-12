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
#ifndef __ENGINE_VEC4_H__
#define __ENGINE_VEC4_H__

#include "math/types.h"
#include "math/mathf.h"
#include "math/vec2.h"
#include "math/vec3.h"

#include <assert.h>
#include <cstddef>

template< class tN >
class Vector4;

typedef Vector4< F32 > Vec4f;
typedef Vector4< F64 > Vec4d;
typedef Vector4< S32 > Vec4i;
typedef Vector4< U32 > Vec4u;
typedef Vector4< Scalar > Vec4;

template< class tN >
class Vector4
{
    friend Vector4 operator+(const Vector4< tN > &, const Vector4< tN > &);
    friend Vector4 operator*(const Vector4< tN > &, const Vector4< tN > &);
    friend Vector4 operator-(const Vector4< tN > &, const Vector4< tN > &);
    friend Vector4 operator-(const Vector4< tN > &);
    friend Vector4 operator*(const Vector4< tN > &, tN);
    friend Vector4 operator*(tN, const Vector4< tN > &);
    friend Vector4 operator/(const Vector4< tN > &, tN);
    friend Vector4 operator/(const Vector4< tN > &, const Vector4< tN > &);

public:

    inline Vector4()
    {
        mValues[0] = (tN)0.0;
        mValues[1] = (tN)0.0;
        mValues[2] = (tN)0.0;
        mValues[3] = (tN)0.0;
    }

    inline Vector4(tN x, tN y, tN z, tN w)
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    template< class tT >
    inline Vector4(const Vector4< tT > &v)
    {
        mValues[0] = (tN)v.X();
        mValues[1] = (tN)v.Y();
        mValues[2] = (tN)v.Z();
        mValues[3] = (tN)v.W();
    }

    template< class tT >
    inline Vector4(tN x, const Vector3< tT > &v)
    {
        mValues[0] = x;
        mValues[1] = (tN)v[0];
        mValues[2] = (tN)v[1];
        mValues[3] = (tN)v[2];
    }

    template< class tT >
    inline Vector4(const Vector3< tT > &v, tN w)
    {
        mValues[0] = (tN)v[0];
        mValues[1] = (tN)v[1];
        mValues[2] = (tN)v[2];
        mValues[3] = w;
    }

    template< class tT >
    inline Vector4(const Vector2< tT > &v1, const Vector2< tT > &v2)
    {
        mValues[0] = (tN)v1[0];
        mValues[1] = (tN)v1[1];
        mValues[2] = (tN)v2[0];
        mValues[3] = (tN)v2[1];
    }

    inline Vector4 &operator=(const Vector4 &other)
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
        mValues[3] = other.mValues[3];

        return *this;
    }

    inline Vector4 &operator-=(const Vector4 &v)
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];
        mValues[2] -= v.mValues[2];
        mValues[3] -= v.mValues[3];

        return *this;
    }

    inline Vector4 &operator+=(const Vector4 &v)
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];
        mValues[2] += v.mValues[2];
        mValues[3] += v.mValues[3];

        return *this;
    }

    inline Vector4 &operator/=(tN s)
    {
        assert(s != 0.0);

        mValues[0] /= s;
        mValues[1] /= s;
        mValues[2] /= s;
        mValues[3] /= s;

        return *this;
    }

    inline Vector4 &operator*=(tN s)
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;
        mValues[3] *= s;

        return *this;
    }

    inline bool operator==(const Vector4 &other) const
    {
        return Mathf::Equal(mValues[0], other.mValues[0]) && Mathf::Equal(mValues[1], other.mValues[1]) &&
               Mathf::Equal(mValues[2], other.mValues[2]) && Mathf::Equal(mValues[3], other.mValues[3]);
    }

    inline bool operator!=(const Vector4 &other) const
    {
        return !(*this == other);
    }

    inline tN &operator[](U8 axis) const
    {
        return mValues[ axis ];
    }

    inline tN *Data()
    {
        return &mValues[0];
    }

    inline tN *Data() const
    {
        return &mValues[0];
    }

    inline tN Dot(const Vector4 &v) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1] + mValues[2] * v.mValues[2] + mValues[3] * v.mValues[3];
    }

    inline tN Length2() const
    {
        return Dot(*this);
    }

    inline tN Length() const
    {
        return Mathf::Sqrt(Length2());
    }

    inline tN Distance2(const Vector4 &v) const
    {
        return (*this - v).Length2();
    }

    inline tN Distance(const Vector4 &v) const
    {
        return (*this - v).Length();
    }

    inline void Set(tN x, tN y, tN z, tN w)
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    inline Vector4 SafeNormalise()
    {
        Vector4 absv = Absolute();
        U8 max = absv.MaxAxis();

        if (absv.mValues[max] > 0)
        {
            assert(absv[max] != 0.0);
            assert(Length() != 0.0);

            *this /= absv.mValues[max];
            return *this /= Length();
        }

        Set(1.0, 0.0, 0.0, 0.0);
        return *this;
    }

    inline Vector4 Normalise()
    {
        return *this /= Length();
    }

    inline Vector4 Lerp(const Vector4 &v, Scalar t) const
    {
        return Vector4(mValues[0] + (v.mValues[0] - mValues[0]) * t, mValues[1] + (v.mValues[1] - mValues[1]) * t,
                       mValues[2] + (v.mValues[2] - mValues[2]) * t, mValues[3] + (v.mValues[3] - mValues[3]) * t);
    }

    inline Vector4 Absolute() const
    {
        return Vector4(Mathf::Abs(mValues[0]), Mathf::Abs(mValues[1]), Mathf::Abs(mValues[2]), Mathf::Abs(mValues[3]));
    }

    inline U8 MinAxis() const
    {
        U8 axis = 0;
        tN minvalue = mValues[0];

        for (U8 i = 1; i < 4; ++i)
        {
            if (minvalue > mValues[i])
            {
                minvalue = mValues[i];
                axis = i;
            }
        }

        return axis;
    }

    inline U8 MaxAxis() const
    {
        U8 axis = 0;
        tN maxvalue = mValues[0];

        for (U8 i = 1; i < 4; ++i)
        {
            if (maxvalue < mValues[i])
            {
                maxvalue = mValues[i];
                axis = i;
            }
        }

        return axis;
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

    inline void W(tN w)
    {
        mValues[3] = w;
    }

    inline tN W() const
    {
        return mValues[3];
    }

    inline void Clear()
    {
        Set(0.0, 0.0, 0.0, 0.0);
    }

    inline bool IsZero() const
    {
        return mValues[0] == 0.0 && mValues[1] == 0.0 && mValues[2] == 0.0 && mValues[3] == 0.0;
    }

    inline bool IsFuzzyZero() const
    {
        return Length2() <= Mathf::Epsilon< tN >() * 10;
    }

    static inline Vector4 Zeros()
    {
        return Vector4(0.0, 0.0, 0.0, 0.0);
    }

    static inline Vector4 Ones()
    {
        return Vector4(1.0, 1.0, 1.0, 1.0);
    }

private:

    tN mValues[4];
};

template< class tN >
inline Vector4< tN > operator+(const Vector4< tN > &v1, const Vector4< tN > &v2)
{
    return Vector4< tN >(v1.mValues[0] + v2.mValues[0],
                         v1.mValues[1] + v2.mValues[1],
                         v1.mValues[2] + v2.mValues[2],
                         v1.mValues[3] + v2.mValues[3]);
}

template< class tN >
inline Vector4< tN > operator*(const Vector4< tN > &v1, const Vector4< tN > &v2)
{
    return Vector4< tN >(v1.mValues[0] * v2.mValues[0],
                         v1.mValues[1] * v2.mValues[1],
                         v1.mValues[2] * v2.mValues[2],
                         v1.mValues[3] * v2.mValues[3]);
}

template< class tN >
inline Vector4< tN > operator-(const Vector4< tN > &v1, const Vector4< tN > &v2)
{
    return Vector4< tN >(v1.mValues[0] - v2.mValues[0],
                         v1.mValues[1] - v2.mValues[1],
                         v1.mValues[2] - v2.mValues[2],
                         v1.mValues[3] - v2.mValues[3]);
}

template< class tN >
inline Vector4< tN > operator-(const Vector4< tN >  &v)
{
    return Vector4< tN > (-v.mValues[0], -v.mValues[1], -v.mValues[2], -v.mValues[3]);
}

template< class tN >
inline Vector4< tN >  operator*(const Vector4< tN >  &v, tN s)
{
    return Vector4< tN > (v.mValues[0] * s, v.mValues[1] * s, v.mValues[2] * s, v.mValues[3] * s);
}

template< class tN >
Vector4< tN >  operator*(tN s, const Vector4< tN >  &v)
{
    return v * s;
}

template< class tN >
inline Vector4< tN >  operator/(const Vector4< tN >  &v, tN s)
{
    assert(s != 0.0);

    return Vector4< tN >(v) /= s;
}

template< class tN >
inline Vector4< tN >  operator/(const Vector4< tN >  &v1, const Vector4< tN >  &v2)
{
    return Vector4< tN > (v1.mValues[0] / v2.mValues[0],
                          v1.mValues[1] / v2.mValues[1],
                          v1.mValues[2] / v2.mValues[2],
                          v1.mValues[3] / v2.mValues[3]);
}

#endif