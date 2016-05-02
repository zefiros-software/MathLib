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
#ifndef __VEC3I_H__
#define __VEC3I_H__

#include "math/config.h"
#include "math/scalar/vec2i.h"
#include "math/generic/primaryVectorBase.h"

BEGIN_MATH_NAMESPACE

class Vec3i : public PrimaryVectorBase< S32, 3 >
{
public:

    inline Vec3i()
    {
        
    }
    
    inline Vec3i( S32 p1 )
    {
        SetValues( p1, p1, p1 );
    }
    
    inline Vec3i( S32 p1, S32 p2, S32 p3 )
    {
        SetValues( p1, p2, p3 );
    }
    
    inline Vec3i( const Vec2i &v1, S32 p3 )
    {
        SetValues( v1[0], v1[1], p3 );
    }
    
    inline Vec3i( S32 p1, const Vec2i &v1 )
    {
        SetValues( p1, v1[0], v1[1] );
    }
     
    template< class TYPE2 >
    inline Vec3i( const PrimaryVectorBase< TYPE2, 3 > &v1 )
    {
        SetValues( (S32) v1[0], (S32) v1[1], (S32) v1[2] );
    }

    inline Vec3i(const PrimaryVectorBase< S32, 3 > &v1)
    {
        SetValues(v1[0], v1[1], v1[2]);
    }
        
};

#endif