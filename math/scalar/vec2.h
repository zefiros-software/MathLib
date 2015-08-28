/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2014 Koen Visscher, Paul Visscher and individual contributors.
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
#ifndef __VEC2_H__
#define __VEC2_H__

#include "math/types.h"
#include "math/scalar/mathf.h"
#include "math/scalar/vec2i.h"
#include "math/scalar/vec2.h"

#include <assert.h>

class Vec2I;

class Vec2
{
    friend Vec2 operator+( const Vec2 &, const Vec2 & );
    friend Vec2 operator*( const Vec2 &, const Vec2 & );
    friend Vec2 operator-( const Vec2 &, const Vec2 & );
    friend Vec2 operator-( const Vec2 & );
    friend Vec2 operator*( const Vec2 &, const Real );
    friend Vec2 operator*( const Real , const Vec2 & );
    friend Vec2 operator/( const Vec2 &, const Real );
    friend Vec2 operator/( const Vec2 &, const Vec2 & );
public:

    inline Vec2()
    {
    }
    
    inline Vec2( const Real x, const Real y )
    {
        mValues[0] = x;
        mValues[1] = y;
    }
    
    inline Vec2( const Vec2 &v )
    {
        mValues[0] = v.mValues[0];
        mValues[1] = v.mValues[1];
    }
    
    inline Vec2( const Vec2I &v )
    {
        mValues[0] = ( Real )v.GetX();
        mValues[1] = ( Real )v.GetY();
    }
    
    inline Real operator[]( U32 i ) const
    {
        assert( i < 2 );
        
        return mValues[i];
    }
    
    inline Real &operator[]( U32 i )
    {
        assert( i < 2 );
        
        return mValues[i];
    }
    
    inline Vec2 &operator=( const Vec2 &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
    
        return *this;
    }
    
    inline Vec2 &operator-=( const Vec2 &v )
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];
    
        return *this;
    }
    
    inline Vec2 &operator+=( const Vec2 &v )
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];
    
        return *this;
    }
    
    inline Vec2 &operator/=( const Real s )
    {
        assert( s != 0.0f );
    
        mValues[0] /= s;
        mValues[1] /= s;
    
        return *this;
    }
    
    inline Vec2 &operator*=( const Real s )
    {
        mValues[0] *= s;
        mValues[1] *= s;
    
        return *this;
    }
    
    inline bool operator==( const Vec2 &other ) const
    {
        return Mathf::Equal( mValues[0], other.mValues[0] ) && Mathf::Equal( mValues[1], other.mValues[1] );
    }
    
    inline bool operator!=( const Vec2 &other ) const
    {
        return !( *this == other );
    }
    
    inline Real Dot( const Vec2 &v ) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1];
    }
    
    inline Real Length2() const
    {
        return Dot( *this );
    }
    
    inline Real Length() const
    {
        return Mathf::Sqrt( Length2() );
    }
    
    inline Real Distance2( const Vec2 &v ) const
    {
        return ( *this - v ).Length2();
    }
    
    inline Real Distance( const Vec2 &v ) const
    {
        return ( *this - v ).Length();
    }
    
    inline void SetValue( const Real x, const Real y )
    {
        mValues[0] = x;
        mValues[1] = y;
    }
    
    inline Vec2 SafeNormalise()
    {
        Vec2 absv = Absolute();
        U8 max = absv.MaxAxis();
    
        if ( absv.mValues[max] > 0 )
        {
            *this /= absv.mValues[max];
            return *this /= Length();
        }
    
        SetValue( 1.0f, 0.0f );
        return *this;
    }
    
    inline Vec2 Normalise()
    {
        assert( Length() != 0.0f );
    
        return *this /= Length();
    }
    
    inline Vec2 Lerp( const Vec2 &v, const Real t ) const
    {
        return Vec2( mValues[0] + ( v.mValues[0] - mValues[0] ) * t, mValues[1] + ( v.mValues[1] - mValues[1] ) * t );
    }
    
    inline Vec2 Nlerp( const Vec2 &v, const Real t ) const
    {
        return Lerp( v, t ).Normalise();
    }
    
    inline Vec2 Rotate( const Real angle ) const
    {
        return Vec2( Mathf::Cos( angle ) * mValues[0] - Mathf::Sin( angle ) * mValues[1],
                     Mathf::Sin( angle ) * mValues[0] - Mathf::Cos( angle ) * mValues[1] );
    }
    
    inline Vec2 Absolute() const
    {
        return Vec2( Mathf::Abs( mValues[0] ), Mathf::Abs( mValues[1] ) );
    }
    
    inline U8 MinAxis() const
    {
        return mValues[0] < mValues[1] ? 0 : 1;
    }
    
    inline U8 MaxAxis() const
    {
        return mValues[0] > mValues[1] ? 0 : 1;
    }
    
    inline Real Angle( const Vec2 &v ) const
    {
        Real s = Mathf::Sqrt( Length2() * v.Length2() );
    
        assert( s != 0.0f );
    
        return Mathf::Acos( Mathf::Clamp( Dot( v ) / s, -1.0f, 1.0f ) );
    }
    
    inline void SetX( const Real x )
    {
        mValues[0] = x;
    }
    
    inline Real GetX() const
    {
        return mValues[0];
    }
    
    inline void SetY( const Real y )
    {
        mValues[1] = y;
    }
    
    inline Real GetY() const
    {
        return mValues[1];
    }
    
    inline void SetZero()
    {
        SetValue( 0.0f, 0.0f );
    }
    
    inline bool IsZero() const
    {
        return mValues[0] == 0.0f && mValues[1] == 0.0f;
    }
    
    inline bool IsFuzzyZero() const
    {
        return Length2() < Mathf::GetEpsilon();
    }
    
    inline void Clear()
    {
        SetValue( 0.0f, 0.0f );
    }
    
    static inline Vec2 GetZero()
    {
        return Vec2( 0.0f, 0.0f );
    }
    
    static inline Vec2 GetOne()
    {
        return Vec2( 1.0f, 1.0f );
    }
    
    static inline Vec2 GetDown()
    {
        return Vec2( 0.0f, -1.0f );
    }
    
    static inline Vec2 GetUp()
    {
        return Vec2( 0.0f, 1.0f );
    }
    
    static inline Vec2 GetLeft()
    {
        return Vec2( -1.0f, 0.0f );
    }
    
    static inline Vec2 GetRight()
    {
        return Vec2( 1.0f, 0.0f );
    }

private:

    Real mValues[2];
};

inline Vec2 operator+( const Vec2 &v1, const Vec2 &v2 )
{
    return Vec2( v1.mValues[0] + v2.mValues[0],
                 v1.mValues[1] + v2.mValues[1] );
}

inline Vec2 operator*( const Vec2 &v1, const Vec2 &v2 )
{
    return Vec2( v1.mValues[0] * v2.mValues[0],
                 v1.mValues[1] * v2.mValues[1] );
}

inline Vec2 operator-( const Vec2 &v1, const Vec2 &v2 )
{
    return Vec2( v1.mValues[0] - v2.mValues[0],
                 v1.mValues[1] - v2.mValues[1] );
}

inline Vec2 operator-( const Vec2 &v )
{
    return Vec2( -v.mValues[0], -v.mValues[1] );
}

inline Vec2 operator*( const Vec2 &v, const Real s )
{
    return Vec2( v.mValues[0] * s, v.mValues[1] * s );
}

inline Vec2 operator*( const Real s, const Vec2 &v )
{
    return v * s;
}

inline Vec2 operator/( const Vec2 &v, const Real s )
{
    assert( s != 0.0f );

    return v * ( Real( 1.0 ) / s );
}

inline Vec2 operator/( const Vec2 &v1, const Vec2 &v2 )
{
    return Vec2( v1.mValues[0] / v2.mValues[0],
                 v1.mValues[1] / v2.mValues[1] );
}

#endif