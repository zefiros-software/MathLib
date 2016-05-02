/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016 Koen Visscher, Paul Visscher and individual contributors.
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

#include "math/scalar/matrix3.h"

class Vec4;

class Quaternion
{
public:
    Quaternion();
    Quaternion( const Real yaw, const Real pitch, const Real roll );
    Quaternion( const Real x, const Real y, const Real z, const Real w );

    Quaternion( const Vec3 &axis, const Real angle );
    Quaternion( const Quaternion &other );
    Quaternion( const Matrix3 &m );
    Quaternion( const Vec4 &axis );

    Quaternion &operator=( const Quaternion &v );

    Quaternion &operator+=( const Quaternion &q );
    Quaternion &operator-=( const Quaternion &q );
    Quaternion &operator*=( const Quaternion &q );
    Quaternion &operator*=( const Real s );
    Quaternion &operator/=( const Real s );

    Quaternion operator+( const Quaternion &q ) const;
    Quaternion operator-( const Quaternion &q ) const;
    Quaternion operator*( const Real s ) const;
    Quaternion operator/( const Real s ) const;

    Quaternion operator-() const;

    Real operator[]( const U8 axis ) const;
    Real operator[]( const U8 axis );

    void Clear();

    void SetEuler( const Real yaw, const Real pitch, const Real roll );
    void SetRotation( const Vec3 &axis, const Real angle );
    void SetValue( const Real x, const Real y, const Real z, const Real w );

    Quaternion GetInverse() const;
    Quaternion SafeNormalise();
    Quaternion Normalise();

    Vec3 RotateVector( const Vec3 &vec ) const;

    Quaternion GetViewRotation() const;

    Real GetAngleFromQuaternion( const Quaternion &q ) const;
    Real GetAngle() const;
    Vec3 GetAxis() const;

    Real Dot( const Quaternion &q ) const;
    Real Length2() const;
    Real Length() const;

    Quaternion Slerp( const Quaternion &q, const Real t ) const;
    Quaternion Nlerp( const Quaternion &q, const Real t ) const;
    Quaternion Lerp( const Quaternion &q, const Real t ) const;

    static Quaternion GetIdentity();

private:

    Vec3 xyz() const;

    Real mValues[4];
};

Quaternion operator*( const Quaternion &q1, const Quaternion &q2 );
Quaternion operator*( const Quaternion &q, const Vec3 &v );
Quaternion operator*( const Vec3 &v, const Quaternion &q );

#endif