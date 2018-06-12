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
#ifndef __ENGINE_QUATERNION_H__
#define __ENGINE_QUATERNION_H__

#include "math/mathf.h"
#include "math/vec3.h"
#include "math/vec4.h"

#include <assert.h>

template< class tN >
class Quaternion;

typedef Quaternion< F32 > Quatf;
typedef Quaternion< F64 > Quatd;
typedef Quaternion< S32 > Quati;
typedef Quaternion< U32 > Quatu;
typedef Quaternion< Scalar > Quat;

template< class tN >
class Quaternion
{
public:

    inline Quaternion()
    {
    }

    inline Quaternion(tN yaw, tN pitch, tN roll)
    {
        Euler(yaw, pitch, roll);
    }

    inline Quaternion(tN x, tN y, tN z, tN w)
    {
        Set(x, y, z, w);
    }

    inline Quaternion(const Vector3< tN > &axis, tN angle)
    {
        SetRotation(axis, angle);
    }

    inline Quaternion(const Quaternion &other)
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
        mValues[3] = other.mValues[3];
    }

    inline Quaternion(const Vector4< tN > &axis)
    {
        Set(axis[0], axis[1], axis[2], axis[3]);
    }

    inline Quaternion &operator=(const Quaternion &q)
    {
        mValues[0] = q[0];
        mValues[1] = q[1];
        mValues[2] = q[2];
        mValues[3] = q[3];

        return *this;
    }

    inline Quaternion &operator+=(const Quaternion &q)
    {
        mValues[0] += q[0];
        mValues[1] += q[1];
        mValues[2] += q[2];
        mValues[3] += q[3];

        return *this;
    }

    inline Quaternion &operator-=(const Quaternion &q)
    {
        mValues[0] -= q[0];
        mValues[1] -= q[1];
        mValues[2] -= q[2];
        mValues[3] -= q[3];

        return *this;
    }

    inline Quaternion &operator*=(const Quaternion &q)
    {
        Set(mValues[3] * q[0] + mValues[0] * q[3] + mValues[1] * q[2] - mValues[2] * q[1],
            mValues[3] * q[1] + mValues[1] * q[3] + mValues[2] * q[0] - mValues[0] * q[2],
            mValues[3] * q[2] + mValues[2] * q[3] + mValues[0] * q[1] - mValues[1] * q[0],
            mValues[3] * q[3] - mValues[0] * q[0] - mValues[1] * q[1] - mValues[2] * q[2]);

        return *this;
    }

    inline Quaternion &operator*=(tN s)
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;
        mValues[3] *= s;

        return *this;
    }

    inline Quaternion &operator/=(tN s)
    {
        assert(s != 0.0);
        return *this / s;
    }

    inline Quaternion operator+(const Quaternion &q) const
    {
        return Quaternion(mValues[0] + q[0], mValues[1] + q[1], mValues[2] + q[2], mValues[3] + q[3]);
    }

    inline Quaternion operator-(const Quaternion &q) const
    {
        return Quaternion(mValues[0] - q[0], mValues[1] - q[1], mValues[2] - q[2], mValues[3] - q[3]);
    }

    inline Quaternion operator*(tN s) const
    {
        return Quaternion(mValues[0] * s, mValues[1] * s, mValues[2] * s, mValues[3] * s);
    }

    inline Quaternion operator/(tN s) const
    {
        assert(s != 0.0);
        return *this / s;
    }

    inline Quaternion operator-() const
    {
        return Quaternion(-mValues[0], -mValues[1],  -mValues[2],  -mValues[3]);
    }

    inline tN operator[](U8 axis) const
    {
        return mValues[ axis ];
    }

    inline tN operator[](U8 axis)
    {
        return mValues[ axis ];
    }

    inline void Euler(tN yaw, tN pitch, tN roll)
    {
        const Scalar p = yaw * (Scalar)0.5;
        const Scalar y = pitch * (Scalar)0.5;
        const Scalar r = roll * (Scalar)0.5;

        const Scalar siny = Mathf::Sin(y);
        const Scalar sinp = Mathf::Sin(p);
        const Scalar sinr = Mathf::Sin(r);
        const Scalar cosy = Mathf::Cos(y);
        const Scalar cosp = Mathf::Cos(p);
        const Scalar cosr = Mathf::Cos(r);

        Set(cosr * sinp * cosy + sinr * cosp * siny,
            cosr * cosp * siny - sinr * sinp * cosy,
            sinr * cosp * cosy - cosr * sinp * siny,
            cosr * cosp * cosy + sinr * sinp * siny);
    }

    inline void SetRotation(const Vector3< tN > &axis, Scalar angle)
    {
        assert(axis.Length() != 0.0);

        Scalar s = Mathf::Sin(angle * 0.5) / axis.Length();
        Set(axis[0] * s, axis[1] * s, axis[2] * s, Mathf::Cos(angle * 0.5));
    }

    inline void Set(tN x, tN y, tN z, tN w)
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    inline Quaternion Inverse() const
    {
        return Quaternion(-mValues[0], -mValues[1], -mValues[2], mValues[3]);
    }

    inline Quaternion SafeNormalise()
    {
        const Vector4< tN > absv = Vector4< tN >(mValues[0], mValues[1], mValues[2], mValues[3]).Absolute();
        const U8 max = absv.MaxAxis();

        if (absv[max] > 0)
        {
            *this /= absv[max];

            return *this /= Length();
        }
        else
        {
            Set(1.0, 0.0, 0.0, 0.0);
        }

        return *this;
    }

    inline Quaternion Normalise()
    {
        assert(Length() != 0.0);

        return *this /= Length();
    }

    inline Vector3< tN > RotateVector(const Vector3< tN > &vec) const
    {
        //     Quaternion q = vec * ( *this );
        //
        //     q *= ( *this ).Inverse();
        //
        //     return Vec3( q[0], q[1], q[2] );

        // Faster path ! https://molecularmusings.wordpress.com/2013/05/24/a-faster-quaternion-vector-multiplication/

        Vector3< tN > qXYZ = this->XYZ();
        Vector3< tN > t = 2 * qXYZ.Cross(vec);

        return (vec + mValues[3] * t + qXYZ.Cross(t));
    }

    inline Quaternion ViewRotation() const
    {
        return Inverse();
    }

    inline tN AngleFromQuaternion(const Quaternion &q) const
    {
        const tN s = Mathf::Sqrt(Length2() * q.Length2());

        assert(s != 0.0);

        return Mathf::Acos(Mathf::Clamp(Dot(q) / s, (tN) - 1.0, (tN)1.0));
    }

    inline tN Angle() const
    {
        return 2.0 * Mathf::Acos(Mathf::Clamp(mValues[3], (tN) - 1.0, (tN)1.0));
    }

    inline Vector3< tN > Axis() const
    {
        const tN s2 = 1.0 - mValues[3] * mValues[3];

        if (s2 < Mathf::Epsilon< tN >())
        {
            return Vector3< tN >(1.0, 0.0, 0.0);
        }

        const tN s = 1.0 / Mathf::Sqrt(s2);
        return Vector3< tN >(mValues[0] * s, mValues[1] * s, mValues[2] * s);
    }

    inline tN Dot(const Quaternion &q) const
    {
        return mValues[0] * q.mValues[0] + mValues[1] * q.mValues[1] + mValues[2] * q.mValues[2] + mValues[3] * q.mValues[3];
    }

    inline Scalar Length2() const
    {
        return Dot(*this);
    }

    inline Scalar Length() const
    {
        return Mathf::Sqrt(Length2());
    }

    inline Quaternion Slerp(const Quaternion &q, tN t) const
    {
        const tN dotp = Dot(q);

        if (dotp > (1.0 - Mathf::Epsilon< tN >()))
        {
            return Lerp(q, t);
        }

        const tN theta = Mathf::Acos(Mathf::Clamp(dotp, (tN) - 1.0, (tN)1.0)) * t;
        Quaternion q2 = q - *this * dotp;
        q2.Normalise();

        return *this * Mathf::Cos(theta) + q2 * Mathf::Sin(theta);
    }

    inline Quaternion Nlerp(const Quaternion &q, tN t) const
    {
        const Vector4< tN > tv(mValues[0], mValues[1], mValues[2], mValues[3]);
        const Vector4< tN > qv(q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3]);
        return Quaternion(tv.Lerp(qv, t).Normalise());
    }


    inline Quaternion Lerp(const Quaternion &q, tN t) const
    {
        const Vector4< tN > tv(mValues[0], mValues[1], mValues[2], mValues[3]);
        const Vector4< tN > qv(q.mValues[0], q.mValues[1], q.mValues[2], q.mValues[3]);
        return Quaternion(tv.Lerp(qv, t));
    }

    inline void Clear()
    {
        Set(0.0, 0.0, 0.0, 1.0);
    }

    inline Quaternion Identity()
    {
        return Quaternion(0.0, 0.0, 0.0, 1.0);
    }

    static Quaternion Zeros()
    {
        return Quaternion(0.0, 0.0, 0.0, 0.0);
    }

private:

    Vector3< tN > XYZ() const
    {
        return Vector3< tN >(mValues[0], mValues[1], mValues[2]);
    }

    tN mValues[4];
};

template< class tN >
inline Quaternion< tN > operator*(const Quaternion< tN > &q1, const Quaternion< tN > &q2)
{
    return Quaternion< tN >(q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1],
                            q1[3] * q2[1] + q1[1] * q2[3] + q1[2] * q2[0] - q1[0] * q2[2],
                            q1[3] * q2[2] + q1[2] * q2[3] + q1[0] * q2[1] - q1[1] * q2[0],
                            q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2]);
}

template< class tN >
inline Quaternion< tN > operator*(const Quaternion< tN > &q, const Vector3< tN > &v)
{
    return Quaternion< tN >(+q[3] * v[0] + q[1] * v[2] - q[2] * v[1],
                            +q[3] * v[1] + q[2] * v[0] - q[0] * v[2],
                            +q[3] * v[2] + q[0] * v[1] - q[1] * v[0],
                            -q[0] * v[0] - q[1] * v[1] - q[2] * v[2]);
}

template< class tN >
inline Quaternion< tN > operator*(const Vector3< tN > &v, const Quaternion< tN > &q)
{
    return Quaternion< tN >(+v[0] * q[3] + v[1] * q[2] - v[2] * q[1],
                            +v[1] * q[3] + v[2] * q[0] - v[0] * q[2],
                            +v[2] * q[3] + v[0] * q[1] - v[1] * q[0],
                            -v[0] * q[0] - v[1] * q[1] - v[2] * q[2]);
}

#endif