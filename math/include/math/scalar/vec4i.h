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
#ifndef __ENGINE_VEC4I_H__
#define __ENGINE_VEC4I_H__

#include "math/types.h"
#include "math/scalar/mathf.h"

#include <cstddef>

class Vec4I
{
    friend Vec4I operator+( const Vec4I &, const Vec4I & );
    friend Vec4I operator*( const Vec4I &, const Vec4I & );
    friend Vec4I operator-( const Vec4I &, const Vec4I & );
    friend Vec4I operator-( const Vec4I & );
    friend Vec4I operator*( const Vec4I &, const S32 );
    friend Vec4I operator*( const S32 , const Vec4I & );
    friend Vec4I operator/( const Vec4I &, const S32 );
    friend Vec4I operator/( const Vec4I &, const Vec4I & );

public:
    
    inline Vec4I()
    {
        mValues[0] = 0;
        mValues[1] = 0;
        mValues[2] = 0;
        mValues[3] = 0;
    }
    
    template< class Vector4D >
    inline Vec4I( const Vector4D &v )
    {
        SetValue( ( S32 )v.GetX(), ( S32 )v.GetY(), ( S32 )v.GetZ(), ( S32 )v.GetW() );
    }
    
    template< class Vector3D >
    inline Vec4I( const Vector3D &v, S32 w )
    {
        SetValue( ( S32 )v[0], ( S32 )v[1], ( S32 )v[2], w );
    }
    
    template< class Vector3D >
    inline Vec4I( S32 x, const Vector3D &v )
    {
        SetValue( x, ( S32 )v[0], ( S32 )v[1], ( S32 )v[2] );
    }
    
    template< class Vector2D >
    inline Vec4I( const Vector2D &v1, const Vector2D &v2 )
    {
        SetValue( ( S32 )v1[0], ( S32 )v1[1], ( S32 )v2[0], ( S32 )v2[1] );
    }
    
    inline Vec4I( const S32 &x, const S32 &y, const S32 &z, const S32 &w )
    {
        SetValue( x, y, z, w );
    }
    
    inline S32 &operator[]( const size_t axis )
    {
        return mValues[ axis ];
    }
    
    inline const S32 &operator[]( const size_t axis ) const
    {
        return mValues[ axis ];
    }
    
    inline S32 GetX() const
    {
        return mValues[0];
    }
    inline void SetX( const S32 &val )
    {
        mValues[0] = val;
    }
    
    inline S32 GetY() const
    {
        return mValues[1];
    }
    
    inline void SetY( const S32 &val )
    {
        mValues[1] = val;
    }
    
    inline S32 GetZ() const
    {
        return mValues[2];
    }
    
    inline void SetZ( const S32 &val )
    {
        mValues[2] = val;
    }
    
    inline S32 GetW() const
    {
        return mValues[3];
    }
    
    inline void SetW( const S32 &val )
    {
        mValues[3] = val;
    }
    
    inline void SetValue( const S32 &x, const S32 &y, const S32 &z, const S32 &w )
    {
        mValues[0] = x;
        mValues[1] = y;
        mValues[2] = z;
        mValues[3] = w;
    }
    
    inline void Clear()
    {
        SetValue( 0, 0, 0, 0 );
    }
    
    static inline Vec4I GetZero()
    {
        return Vec4I( 0, 0, 0, 0 );
    }
    
    static inline Vec4I GetOne()
    {
        return Vec4I( 1, 1, 1, 1 );
    }

private:

    S32 mValues[4];
};

inline Vec4I operator+( const Vec4I &v1, const Vec4I &v2 )
{
    return Vec4I( v1.mValues[0] + v2.mValues[0],
                  v1.mValues[1] + v2.mValues[1],
                  v1.mValues[2] + v2.mValues[2],
                  v1.mValues[3] + v2.mValues[3] );
}

inline Vec4I operator*( const Vec4I &v1, const Vec4I &v2 )
{
    return Vec4I( v1.mValues[0] * v2.mValues[0],
                  v1.mValues[1] * v2.mValues[1],
                  v1.mValues[2] * v2.mValues[2],
                  v1.mValues[3] * v2.mValues[3] );
}

inline Vec4I operator-( const Vec4I &v1, const Vec4I &v2 )
{
    return Vec4I( v1.mValues[0] - v2.mValues[0],
                  v1.mValues[1] - v2.mValues[1],
                  v1.mValues[2] - v2.mValues[2],
                  v1.mValues[3] - v2.mValues[3] );
}

inline Vec4I operator-( const Vec4I &v )
{
    return Vec4I( -v.mValues[0], -v.mValues[1], -v.mValues[2], -v.mValues[3] );
}

inline Vec4I operator*( const Vec4I &v, const S32 s )
{
    return Vec4I( v.mValues[0] * s, v.mValues[1] * s, v.mValues[2] * s, v.mValues[3] * s );
}

inline Vec4I operator*( const S32 s, const Vec4I &v )
{
    return v * s;
}

inline Vec4I operator/( const Vec4I &v, const S32 s )
{
    assert( s != 0.0f );
    
    return v / s ;
}

inline Vec4I operator/( const Vec4I &v1, const Vec4I &v2 )
{
    return Vec4I( v1.mValues[0] / v2.mValues[0],
                  v1.mValues[1] / v2.mValues[1],
                  v1.mValues[2] / v2.mValues[2],
                  v1.mValues[3] / v2.mValues[3] );
}

#endif