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
#ifndef __ENGINE_VEC3_H__
#define __ENGINE_VEC3_H__

#include "math/types.h"
#include "math/scalar/mathf.h"
#include "math/scalar/vec2.h"
#include "math/scalar/vec3i.h"

template< class Number >
class Vec3;

typedef Vec3< F32 > Vec3f;
typedef Vec3< F64 > Vec3d;

#ifndef REAL_UNDEFINED
typedef Vec3< Real > Vec3r;
#endif

template< class Number >
class Vec3
{
    template< class T >
    friend Vec3< T > operator+( const Vec3< T > &, const Vec3< T > & );
    
    template< class T >
    friend Vec3< T > operator*( const Vec3< T > &, const Vec3< T > & );
    
    template< class T >
    friend Vec3< T > operator-( const Vec3< T > &, const Vec3< T > & );
    
    template< class T >
    friend Vec3< T > operator-( const Vec3< T > & );
    
    template< class T >
    friend Vec3< T > operator*( const Vec3< T > &, const T );
    
    template< class T >
    friend Vec3< T > operator*( const T , const Vec3< T > & );
    
    template< class T >
    friend Vec3< T > operator/( const Vec3< T > &, const T );
    
    template< class T >
    friend Vec3< T > operator/( const Vec3< T > &, const Vec3< T > & );

public:
    
    inline Vec3()
    {
    }

    inline Vec3( const Number x, const Number y, const Number z )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
    }

    inline Vec3( const Vec3I &v )
    {
        mValues[0] = ( Number )v.GetX();
        mValues[1] = ( Number )v.GetY();
        mValues[2] = ( Number )v.GetZ();
    }
    
    inline Vec3( const Vec2< Number > &v, Number z )
    {
        mValues[0] = ( Number )v[0];
        mValues[1] = ( Number )v[1];
        mValues[2] = z;
    }

    inline Vec3( Number x, const Vec2< Number > &v )
    {
        mValues[0] = x;
        mValues[1] = ( Number )v[0];
        mValues[2] = ( Number )v[1];
    }

    inline Vec3 &operator=( const Vec3 &other )
    {
        mValues[0] = other.mValues[0];
        mValues[1] = other.mValues[1];
        mValues[2] = other.mValues[2];

        return *this;
    }

    inline Vec3 &operator-=( const Vec3 &v )
    {
        mValues[0] -= v.mValues[0];
        mValues[1] -= v.mValues[1];
        mValues[2] -= v.mValues[2];

        return *this;
    }

    inline Vec3 &operator+=( const Vec3 &v )
    {
        mValues[0] += v.mValues[0];
        mValues[1] += v.mValues[1];
        mValues[2] += v.mValues[2];

        return *this;
    }

    inline Vec3 &operator/=( const Number s )
    {
        assert( s != 0.0f );

        mValues[0] /= s;
        mValues[1] /= s;
        mValues[2] /= s;

        return *this;
    }

    inline Vec3 &operator*=( const Number s )
    {
        mValues[0] *= s;
        mValues[1] *= s;
        mValues[2] *= s;

        return *this;
    }

    inline bool operator==( const Vec3 &other ) const
    {
        return Mathf::Equal( mValues[0], other.mValues[0] ) &&
               Mathf::Equal( mValues[1], other.mValues[1] ) &&
               Mathf::Equal( mValues[2], other.mValues[2] );
    }

    inline bool operator!=( const Vec3 &other ) const
    {
        return !( *this == other );
    }

    inline Number &operator[]( const size_t axis )
    {
        return mValues[ axis ];
    }

    inline const Number operator[]( const size_t axis ) const
    {
        return mValues[ axis ];
    }

    inline Number Dot( const Vec3 &v ) const
    {
        return mValues[0] * v.mValues[0] + mValues[1] * v.mValues[1] + mValues[2] * v.mValues[2];
    }

    inline Number Length2() const
    {
        return Dot( *this );
    }

    inline Number Length() const
    {
        return Mathf::Sqrt( Length2() );
    }

    inline Number Distance2( const Vec3 &v ) const
    {
        return ( *this - v ).Length2();
    }

    inline Number Distance( const Vec3 &v ) const
    {
        return ( *this - v ).Length();
    }

    inline void SetValue( const Number x, const Number y, const Number z )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
    }

    inline Vec3 SafeNormalise()
    {
        Vec3 absv = Absolute();
        U8 max = absv.MaxAxis();

        if ( absv.mValues[max] > 0 )
        {
            assert( absv[max] != 0.0f );
            assert( Length() != 0.0f );

            *this /= absv.mValues[max];
            return *this /= Length();
        }

        SetValue( 1.0f, 0.0f, 0.0f );
        return *this;
    }

    inline Vec3 Normalise()
    {
        assert( Length() != 0.0f );

        return *this /= Length();
    }

    inline Vec3 Lerp( const Vec3 &v, const Number t ) const
    {
        return Vec3( Mathf::Lerp( mValues[0], v.mValues[0], t ), Mathf::Lerp( mValues[1], v.mValues[1], t ),
                     Mathf::Lerp( mValues[2], v.mValues[2], t ) );
    }

    inline Vec3 Slerp( const Vec3 &v, const Number t ) const
    {
        Number dotp = Dot( v );

        // Make sure the floating point accuracy doesn't
        // crash our program
        Mathf::Clamp< Number >( dotp , -1.0f, 1.0f );

        Number theta = Mathf::Acos( dotp ) * t;
        Vec3 relative = v - *this * dotp;
        relative.Normalise();

        return *this * Mathf::Cos( theta ) + relative * Mathf::Sin( theta );

    }

    inline Vec3 Nlerp( const Vec3 &v, const Number t ) const
    {
        return Lerp( v, t ).Normalise();
    }

    inline Vec3 Rotate( const Vec3 &axis, const Number angle ) const
    {
        Vec3 v1 = axis * axis.Dot( *this );
        return v1 + ( *this - v1 ) * Mathf::Cos( angle ) + axis.Cross( *this ) * Mathf::Sin( angle );
    }

    inline Vec3 Cross( const Vec3 &v ) const
    {
        return Vec3( mValues[1] * v.mValues[2] - mValues[2] * v.mValues[1],
                     mValues[2] * v.mValues[0] - mValues[0] * v.mValues[2],
                     mValues[0] * v.mValues[1] - mValues[1] * v.mValues[0] );
    }

    inline Vec3 Absolute() const
    {
        return Vec3( Mathf::Abs( mValues[0] ), Mathf::Abs( mValues[1] ), Mathf::Abs( mValues[2] ) );
    }

    inline U8 MinAxis() const
    {
        return mValues[0] < mValues[1] ? ( mValues[0] < mValues[2] ? 0 : 2 ) : ( mValues[1] < mValues[2] ? 1 : 2 );
    }

    inline U8 MaxAxis() const
    {
        return mValues[0] < mValues[1] ? ( mValues[1] < mValues[2] ? 2 : 1 ) : ( mValues[0] < mValues[2] ? 2 : 0 );
    }

    inline Number Angle( const Vec3 &v ) const
    {
        Number s = Mathf::Sqrt( Length2() * v.Length2() );

        assert( s != 0.0f );

        return Mathf::Acos( Mathf::Clamp< Number >( Dot( v ) / s, -1.0f, 1.0f ) );
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

    inline void SetZero()
    {
        SetValue( 0.0f, 0.0f, 0.0f );
    }

    inline bool IsZero() const
    {
        return mValues[0] == 0.0f && mValues[1] == 0.0f && mValues[2] == 0.0f;
    }

    inline bool IsFuzzyZero() const
    {
        return Length2() < Mathf::GetEpsilon< Number >();
    }

    inline void Clear()
    {
        SetValue( 0.0f, 0.0f, 0.0f );
    }

    static inline Vec3 GetZero()
    {
        return Vec3( 0.0f, 0.0f, 0.0f );
    }

    static inline Vec3 GetOne()
    {
        return Vec3( 1.0f, 1.0f, 1.0f );
    }

    static inline Vec3 GetBack()
    {
        return Vec3( 0.0f, -1.0f, 0.0f );
    }

    static inline Vec3 GetForward()
    {
        return Vec3( 0.0f, 1.0f, 0.0f );
    }

    static inline Vec3 GetDown()
    {
        return Vec3( 0.0f, 0.0f, -1.0f );
    }

    static inline Vec3 GetUp()
    {
        return Vec3( 0.0f, 0.0f, 1.0f );
    }

    static inline Vec3 GetLeft()
    {
        return Vec3( -1.0f, 0.0f, 0.0f );
    }

    static inline Vec3 GetRight()
    {
        return Vec3( 1.0f, 0.0f, 0.0f );
    }

private:

    Number mValues[3];
};

template< class Number >
Vec3< Number > operator+( const Vec3< Number > &v1, const Vec3< Number > &v2 )
{
    return Vec3< Number >( v1.mValues[0] + v2.mValues[0],
                           v1.mValues[1] + v2.mValues[1],
                           v1.mValues[2] + v2.mValues[2] );
}

template< class Number >
Vec3< Number > operator*( const Vec3< Number > &v1, const Vec3< Number > &v2 )
{
    return Vec3< Number >( v1.mValues[0] * v2.mValues[0],
                           v1.mValues[1] * v2.mValues[1],
                           v1.mValues[2] * v2.mValues[2] );
}

template< class Number >
Vec3< Number > operator-( const Vec3< Number > &v1, const Vec3< Number > &v2 )
{
    return Vec3< Number >( v1.mValues[0] - v2.mValues[0],
                           v1.mValues[1] - v2.mValues[1],
                           v1.mValues[2] - v2.mValues[2] );
}

template< class Number >
Vec3< Number > operator-( const Vec3< Number > &v )
{
    return Vec3< Number >( -v.mValues[0], -v.mValues[1], -v.mValues[2] );
}

template< class Number >
Vec3< Number > operator*( const Vec3< Number > &v, const Number s )
{
    return Vec3< Number >( v.mValues[0] * s, v.mValues[1] * s, v.mValues[2] * s );
}

template< class Number >
Vec3< Number > operator*( Number s, const Vec3< Number > &v )
{
    return v * s;
}

template< class Number >
Vec3< Number > operator/( const Vec3< Number > &v, Number s )
{
    assert( s != 0.0f );
    
    return v * ( Number( 1.0 ) / s );
}

template< class Number >
Vec3< Number > operator/( const Vec3< Number > &v1, const Vec3< Number > &v2 )
{
    return Vec3< Number >( v1.mValues[0] / v2.mValues[0],
                           v1.mValues[1] / v2.mValues[1] ,
                           v1.mValues[2] / v2.mValues[2] );
}

// Vec3I conversion:
template < class T >
inline Vec3I::Vec3I( const Vec3< T > &v )
{
    SetValue( ( S32 )v.GetX(), ( S32 )v.GetY(), ( S32 )v.GetZ() );
}

#endif