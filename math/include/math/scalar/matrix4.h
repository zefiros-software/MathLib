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
#ifndef __ENGINE_MATRIX4_H__
#define __ENGINE_MATRIX4_H__

#include "math/scalar/matrix3.h"
#include "math/scalar/vec4.h"

class Vec3;
class Quaternion;

class Matrix4
{
    friend Matrix4 operator+( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator-( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m, const Real s );
    friend Vec4 operator*( const Matrix4 &m, const Vec4 &v );

public:

    Matrix4();

    Matrix4( const Real a11, const Real a12, const Real a13, const Real a14,
             const Real a21, const Real a22, const Real a23, const Real a24,
             const Real a31, const Real a32, const Real a33, const Real a34,
             const Real a41, const Real a42, const Real a43, const Real a44 );

    Matrix4( const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4 );

    Matrix4( const Matrix4 &other );

    Matrix4 &operator=( const Matrix4 &m );

    Matrix4 &operator*=( const Matrix4 &m );

    Matrix4 &operator+=( const Matrix4 &m );

    Matrix4 &operator-=( const Matrix4 &m );

    bool operator==( const Matrix4 &m ) const;

    bool operator!=( const Matrix4 &m ) const;

    const Vec4 &operator[]( const U8 row ) const;

    void SetColumn( const U8 column, const Vec4 &v );

    Vec4 GetColumn( const U8 column ) const;

    void SetRow( const U8 row, const Vec4 &v );

    Vec4 GetRow( const U8 row ) const;

    Matrix4 Scale( const Vec4 &v ) const;

    Matrix4 GetTranspose() const;

    Matrix4 GetAbsolute() const;

    Matrix4 GetAdjoint() const;

    Matrix4 GetInverse() const;

    Matrix3 Extract3x3() const;

    void Compose( const Vec3 &scaling, const Quaternion &rotation, const Vec3 &translation );
    void Decompose( Vec3 &scaling, Quaternion &rotation, Vec3 &translation ) const;

    void SetIdentity();

    Real GetCofactor( const U8 row, const U8 column ) const;

    Real GetDeterminant() const;

    void SetValue( const Real a11, const Real a12, const Real a13, const Real a14,
                   const Real a21, const Real a22, const Real a23, const Real a24,
                   const Real a31, const Real a32, const Real a33, const Real a34,
                   const Real a41, const Real a42, const Real a43, const Real a44 );

    static Matrix4 GetZero();

    static Matrix4 GetIdentity();

private:

    Vec4 mValues[4];

    inline Real Dotx( const Vec4 &v ) const
    {
        return mValues[0][0] * v[0] + mValues[1][0] * v[1] + mValues[2][0] * v[2] + mValues[3][0] * v[3];
    }

    inline Real Doty( const Vec4 &v ) const
    {
        return mValues[0][1] * v[0] + mValues[1][1] * v[1] + mValues[2][1] * v[2] + mValues[3][1] * v[3];
    }

    inline Real Dotz( const Vec4 &v ) const
    {
        return mValues[0][2] * v[0] + mValues[1][2] * v[1] + mValues[2][2] * v[2] + mValues[3][2] * v[3];
    }

    inline Real Dotw( const Vec4 &v ) const
    {
        return mValues[0][3] * v[0] + mValues[1][3] * v[1] + mValues[2][3] * v[2] + mValues[3][3] * v[3];
    }

};

Matrix4 operator+( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator-( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator*( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator*( const Matrix4 &m, const Real s );
Vec4 operator*( const Matrix4 &m, const Vec4 &v );

#endif