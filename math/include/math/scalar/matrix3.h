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
#ifndef __ENGINE_MATRIX3_H__
#define __ENGINE_MATRIX3_H__

#include "math/scalar/vec3.h"

class Quaternion;

class Matrix3
{
    friend Matrix3 operator+( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator-( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator*( const Matrix3 &m1, const Matrix3 &m2 );
    friend Matrix3 operator*( const Matrix3 &m, const Real s );
    friend Vec3 operator*( const Matrix3 &m, const Vec3 &v );

public:

    Matrix3();
    Matrix3( const Quaternion &q );
    Matrix3( const Real m11, const Real m12, const Real m13,
             const Real m21, const Real m22, const Real m23,
             const Real m31, const Real m32, const Real m33 );
    Matrix3( const Vec3 &v1, const Vec3 &v2, const Vec3 &v3 );
    Matrix3( const Matrix3 &other );

    Matrix3 &operator=( const Matrix3 &m );
    Matrix3 &operator*=( const Matrix3 &m );
    Matrix3 &operator+=( const Matrix3 &m );
    Matrix3 &operator-=( const Matrix3 &m );

    bool operator==( const Matrix3 &m ) const;
    bool operator!=( const Matrix3 &m ) const;

    Vec3 &operator[]( const U8 axis );

    void SetColumn( const U8 column, const Vec3 &v );
    Vec3 GetColumn( const U8 column ) const;

    void SetRow( const U8 row, const Vec3 &v );
    Vec3 GetRow( const U8 row ) const;

    void SetRotation( const Quaternion &q );
    Quaternion GetRotation() const;

    void SetEuler( const Real yaw, const Real pitch, const Real roll );
    Vec3 GetEuler() const;

    Matrix3 Scale( const Vec3 &v ) const;
    Matrix3 GetTranspose() const;
    Matrix3 GetAbsolute() const;
    Matrix3 GetAdjoint() const;
    Matrix3 GetInverse() const;

    void SetIdentity();

    Real GetCofactor( const U8 row, const U8 column ) const;
    Real GetDeterminant() const;

    void SetValue( const Real m11, const Real m12, const Real m13,
                   const Real m21, const Real m22, const Real m23,
                   const Real m31, const Real m32, const Real m33 );

    static Matrix3 GetZero();

    static Matrix3 GetIdentity();

private:

    Vec3 mValues[3];

    Real Dotx( const Vec3 &v ) const;
    Real Doty( const Vec3 &v ) const;
    Real Dotz( const Vec3 &v ) const;
};

Matrix3 operator+( const Matrix3 &m1, const Matrix3 &m2 );
Matrix3 operator-( const Matrix3 &m1, const Matrix3 &m2 );
Matrix3 operator*( const Matrix3 &m1, const Matrix3 &m2 );
Matrix3 operator*( const Matrix3 &m, const Real s );
Vec3 operator*( const Matrix3 &m, const Vec3 &v );

#endif