/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2017 Zefiros Software.
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
#include "math/scalar/mathf.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec3.h"

#include <assert.h>
#include <cstddef>

template< class Number >
class Vec4;

typedef Vec4< F32 > Vec4f;
typedef Vec4< F64 > Vec4d;

#ifndef REAL_UNDEFINED
typedef Vec4< Real > Vec4r;
#endif

template< class Number >
class Vec4
{
    friend Vec4 operator+( const Vec4 &, const Vec4 & );
    friend Vec4 operator*( const Vec4 &, const Vec4 & );
    friend Vec4 operator-( const Vec4 &, const Vec4 & );
    friend Vec4 operator-( const Vec4 & );
    friend Vec4 operator*( const Vec4 &, const Number );
    friend Vec4 operator*( const Number , const Vec4 & );
    friend Vec4 operator/( const Vec4 &, const Number );
    friend Vec4 operator/( const Vec4 &, const Vec4 & );

public:

    inline Vec4()
    {
    }

    inline Vec4( const Number x, const Number y, const Number z, const Number w )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    template< class Vector4D >
    inline Vec4( const Vector4D &v )
    {
        mValues[0] = ( Number )v.GetX();
        mValues[1] = ( Number )v.GetY();
        mValues[2] = ( Number )v.GetZ();
        mValues[3] = ( Number )v.GetW();
    }

    inline Vec4( Number x, const Vec3< Number > &v )
    {
        mValues[0] = x;
        mValues[1] = ( Number )v[0];
        mValues[2] = ( Number )v[1];
        mValues[3] = ( Number )v[2];
    }

    inline Vec4( const Vec3< Number > &v, Number w )
    {
        mValues[0] = ( Number )v[0];
        mValues[1] = ( Number )v[1];
        mValues[2] = ( Number )v[2];
        mValues[3] = w;
    }

    inline Vec4( const Vec2< Number > &v1, const Vec2< Number > &v2 )
    {
        mValues[0] = ( Number )v1[0];
        mValues[1] = ( Number )v1[1];
        mValues[2] = ( Number )v2[0];
        mValues[3] = ( Number )v2[1];
    }

    inline Vec4 &operator=( const Vec4 &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];
        mValues[3] = other.mValues[3];

        return *this;
    }

    inline Vec4 &operator-=( const Vec4 &v )
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];
        mValues[2] -= v.mValues[2];
        mValues[3] -= v.mValues[3];

        return *this;
    }

    inline Vec4 &operator+=( const Vec4 &v )
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];
        mValues[2] += v.mValues[2];
        mValues[3] += v.mValues[3];

        return *this;
    }

    inline Vec4 &operator/=( Number s )
    {
        assert( s != 0.0f );

        mValues[0] /= s;
        mValues[1] /= s;
        mValues[2] /= s;
        mValues[3] /= s;

        return *this;
    }

    inline Vec4 &operator*=( Number s )
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;
        mValues[3] *= s;

        return *this;
    }

    inline bool operator==( const Vec4 &other ) const
    {
        return Mathf::Equal( mValues[0], other.mValues[0] ) && Mathf::Equal( mValues[1], other.mValues[1] ) &&
               Mathf::Equal( mValues[2], other.mValues[2] ) && Mathf::Equal( mValues[3], other.mValues[3] );
    }

    inline bool operator!=( const Vec4 &other ) const
    {
        return !( *this == other );
    }

    inline Number &operator[]( const U8 axis )
    {
        return mValues[ axis ];
    }

    inline const Number &operator[]( const U8 axis ) const
    {
        return mValues[ axis ];
    }
    
    inline Number* Data() 
    {
        return &mValues[0];
    }
    
    inline const Number* Data() const
    {
        return &mValues[0];
    }

    inline Number Dot( const Vec4 &v ) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1] + mValues[2] * v.mValues[2] + mValues[3] * v.mValues[3];
    }

    inline Number Length2() const
    {
        return Dot( *this );
    }

    inline Number Length() const
    {
        return Mathf::Sqrt( Length2() );
    }

    inline Number Distance2( const Vec4 &v ) const
    {
        return ( *this - v ).Length2();
    }

    inline Number Distance( const Vec4 &v ) const
    {
        return ( *this - v ).Length();
    }

    inline void SetValue( const Number x, const Number y, const Number z, const Number w )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }

    inline Vec4 SafeNormalise()
    {
        Vec4 absv = Absolute();
        U8 max = absv.MaxAxis();

        if ( absv.mValues[max] > 0 )
        {
            assert( absv[max] != 0.0f );
            assert( Length() != 0.0f );

            *this /= absv.mValues[max];
            return *this /= Length();
        }

        SetValue( 1.0f, 0.0f, 0.0f, 0.0f );
        return *this;
    }

    inline Vec4 Normalise()
    {
        return *this /= Length();
    }

    inline Vec4 Lerp( const Vec4 &v, const Number t ) const
    {
        return Vec4( mValues[0] + ( v.mValues[0] - mValues[0] ) * t, mValues[1] + ( v.mValues[1] - mValues[1] ) * t,
                     mValues[2] + ( v.mValues[2] - mValues[2] ) * t, mValues[3] + ( v.mValues[3] - mValues[3] ) * t );
    }

    inline Vec4 Absolute() const
    {
        return Vec4( Mathf::Abs( mValues[0] ), Mathf::Abs( mValues[1] ), Mathf::Abs( mValues[2] ), Mathf::Abs( mValues[3] ) );
    }

    inline U8 MinAxis() const
    {
        U8 axis = 0;
        Number minvalue = mValues[0];

        for ( U8 i = 1; i < 4; ++i )
        {
            if ( minvalue > mValues[i] )
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
        Number maxvalue = mValues[0];

        for ( U8 i = 1; i < 4; ++i )
        {
            if ( maxvalue < mValues[i] )
            {
                maxvalue = mValues[i];
                axis = i;
            }
        }

        return axis;
    }

    inline void SetX( const Number x )
    {
        mValues[0] = x;
    }

    inline Number GetX() const
    {
        return mValues[0];
    }

    inline void SetY( const Number y )
    {
        mValues[1] = y;
    }

    inline Number GetY() const
    {
        return mValues[1];
    }

    inline void SetZ( const Number z )
    {
        mValues[2] = z;
    }

    inline Number GetZ() const
    {
        return mValues[2];
    }

    inline void SetW( const Number w )
    {
        mValues[3] = w;
    }

    inline Number GetW() const
    {
        return mValues[3];
    }

    inline void SetZero()
    {
        SetValue( 0.0f, 0.0f, 0.0f, 0.0f );
    }

    inline bool IsZero() const
    {
        return mValues[0] == 0.0f && mValues[1] == 0.0f && mValues[2] == 0.0f && mValues[3] == 0.0f;
    }

    inline bool IsFuzzyZero() const
    {
        return Length2() <= Mathf::GetEpsilon< Number >() * 10;
    }

    inline void Clear()
    {
        SetValue( 0.0f, 0.0f, 0.0f, 0.0f );
    }

    static inline Vec4 GetZero()
    {
        return Vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    }

    static inline Vec4 GetOne()
    {
        return Vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    }



private:

    Number mValues[4];
};

template< class Number >
inline Vec4< Number > operator+( const Vec4< Number > &v1, const Vec4< Number > &v2 )
{
    return Vec4< Number >( v1.mValues[0] + v2.mValues[0],
                           v1.mValues[1] + v2.mValues[1],
                           v1.mValues[2] + v2.mValues[2],
                           v1.mValues[3] + v2.mValues[3] );
}

template< class Number >
inline Vec4< Number > operator*( const Vec4< Number > &v1, const Vec4< Number > &v2 )
{
    return Vec4< Number >( v1.mValues[0] * v2.mValues[0],
                           v1.mValues[1] * v2.mValues[1],
                           v1.mValues[2] * v2.mValues[2],
                           v1.mValues[3] * v2.mValues[3] );
}

template< class Number >
inline Vec4< Number > operator-( const Vec4< Number > &v1, const Vec4< Number > &v2 )
{
    return Vec4< Number >( v1.mValues[0] - v2.mValues[0],
                           v1.mValues[1] - v2.mValues[1],
                           v1.mValues[2] - v2.mValues[2],
                           v1.mValues[3] - v2.mValues[3] );
}

template< class Number >
inline Vec4< Number > operator-( const Vec4< Number >  &v )
{
    return Vec4< Number > ( -v.mValues[0], -v.mValues[1], -v.mValues[2], -v.mValues[3] );
}

template< class Number >
inline Vec4< Number >  operator*( const Vec4< Number >  &v, const Number s )
{
    return Vec4< Number > ( v.mValues[0] * s, v.mValues[1] * s, v.mValues[2] * s, v.mValues[3] * s );
}

template< class Number >
Vec4< Number >  operator*( const Number s, const Vec4< Number >  &v )
{
    return v * s;
}

template< class Number >
inline Vec4< Number >  operator/( const Vec4< Number >  &v, const Number s )
{
    assert( s != 0.0f );

    return v * ( Number( 1.0 ) / s );
}

template< class Number >
inline Vec4< Number >  operator/( const Vec4< Number >  &v1, const Vec4< Number >  &v2 )
{
    return Vec4< Number > ( v1.mValues[0] / v2.mValues[0],
                            v1.mValues[1] / v2.mValues[1],
                            v1.mValues[2] / v2.mValues[2],
                            v1.mValues[3] / v2.mValues[3] );
}

#endif