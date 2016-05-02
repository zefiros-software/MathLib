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
#ifndef __ENGINE_VEC4_H__
#define __ENGINE_VEC4_H__

#include "math/types.h"

class Vec4I;
class Vec3;
class Vec2;

class Vec4
{
    friend Vec4 operator+( const Vec4 &, const Vec4 & );
    friend Vec4 operator*( const Vec4 &, const Vec4 & );
    friend Vec4 operator-( const Vec4 &, const Vec4 & );
    friend Vec4 operator-( const Vec4 & );
    friend Vec4 operator*( const Vec4 &, const Real );
    friend Vec4 operator*( const Real , const Vec4 & );
    friend Vec4 operator/( const Vec4 &, const Real );
    friend Vec4 operator/( const Vec4 &, const Vec4 & );

public:

    Vec4();
    Vec4( const Real x, const Real y, const Real z, const Real w );
    Vec4( const Vec3 &other, Real w );
    Vec4( const Vec2 &other1, const Vec2 &other2 );
    Vec4( const Vec4 &v );
    Vec4( const Vec4I &v );

    Vec4 &operator=( const Vec4 &other );
    Vec4 &operator-=( const Vec4 &v );
    Vec4 &operator+=( const Vec4 &v );
    Vec4 &operator/=( const Real s );
    Vec4 &operator*=( const Real s );

    bool operator==( const Vec4 &other ) const;
    bool operator!=( const Vec4 &other ) const;

    Real &operator[]( const U8 axis );
    const Real &operator[]( const U8 axis ) const;

    Real Dot( const Vec4 &v ) const;

    Real Length2() const;
    Real Length() const;

    Real Distance2( const Vec4 &v ) const;
    Real Distance( const Vec4 &v ) const;

    void SetValue( const Real x, const Real y, const Real z, const Real w );
    void Clear();

    Vec4 SafeNormalise();
    Vec4 Normalise();

    Vec4 Lerp( const Vec4 &v, Real t ) const;

    Vec4 Absolute() const;

    U8 MinAxis() const;
    U8 MaxAxis() const;

    void SetX( const Real x );
    Real GetX() const;

    void SetY( const Real y );
    Real GetY() const;

    void SetZ( const Real z );
    Real GetZ() const;

    void SetW( const Real w );
    Real GetW() const;

    Vec3 GetXYZ() const;

    void SetZero();
    bool IsZero() const;
    bool IsFuzzyZero() const;

    static Vec4 GetZero();

    static Vec4 GetOne();

private:

    Real mValues[4];
};

Vec4 operator+( const Vec4 &v1, const Vec4 &v2 );

Vec4 operator-( const Vec4 &v1, const Vec4 &v2 );
Vec4 operator-( const Vec4 &v );

Vec4 operator*( const Vec4 &v1, const Vec4 &v2 );
Vec4 operator*( const Vec4 &v, const Real s );
Vec4 operator*( const Real s, const Vec4 &v );

Vec4 operator/( const Vec4 &v, const Real s );
Vec4 operator/( const Vec4 &v1, const Vec4 &v2 );

#endif