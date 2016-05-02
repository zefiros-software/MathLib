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
#ifndef __VEC3_H__
#define __VEC3_H__

#include "math/config.h"
#include "math/scalar/vec2.h"
#include "math/generic/floatingPointVector.h"

BEGIN_MATH_NAMESPACE

class Vec3 : public FloatingPointVector< Real, 3 >
{
public:

    inline Vec3()
    {
        
    }
    
    inline Vec3( Real p1 )
    {
        SetValues( p1, p1, p1 );
    }
    
    inline Vec3( Real p1, Real p2, Real p3 )
    {
        SetValues( p1, p2, p3 );
    }
    
    inline Vec3( const Vec2 &v1, Real p3 )
    {
        SetValues( v1[0], v1[1], p3 );
    }
    
    inline Vec3( Real p1, const Vec2 &v1 )
    {
        SetValues( p1, v1[0], v1[1] );
    }
    
    template< class TYPE2 >
    inline Vec3( const PrimaryVectorBase< TYPE2, 3 > &v1 )
    {
        SetValues( (Real) v1[0], (Real) v1[1], (Real) v1[2] );
    }

    inline Vec3(const FloatingPointVector< Real, 3 > &v1)
    {
        SetValues(v1[0], v1[1], v1[2]);
    }

    // Vec3 specific intrinsics
    inline Vec3 Rotate(const Vec3 &axis, const Real angle) const
    {
        Vec3 v1 = axis * axis.Dot(*this);
        return v1 + (*this - v1) * Mathf::Cos(angle) + axis.Cross(*this) * Mathf::Sin(angle);
    }

    inline Vec3 Cross(const Vec3 &v) const
    {
        return Vec3( mValues[1] * v.mValues[2] - mValues[2] * v.mValues[1],
                     mValues[2] * v.mValues[0] - mValues[0] * v.mValues[2],
                     mValues[0] * v.mValues[1] - mValues[1] * v.mValues[0]);
    }
    
    static inline Vec3 GetZero()
    {
        return Vec3( 0.0f, 0.0f, 0.0f );
    }
    
    static inline Vec3 GetOne()
    {
        return Vec3( 0.0f, 0.0f, 0.0f );
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
};

#endif