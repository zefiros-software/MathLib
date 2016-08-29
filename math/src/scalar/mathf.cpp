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
#include "math/scalar/mathf.h"

#include <assert.h>
#include <cstdlib>
#include <limits>

#define _USE_MATH_DEFINES
#include <math.h>

BEGIN_MATH_NAMESPACE

F32 Mathf::Acos( const F32 f )
{
    assert( f >= -1.0f && f <= 1.0f );
    return acosf( f );
}

F32 Mathf::Asin( const F32 f )
{
    assert( f >= -1.0f && f <= 1.0f );
    return asinf( f );
}

F32 Mathf::Atan( const F32 f )
{
    return atanf( f );
}

F32 Mathf::Atan2( const F32 x, const F32 y )
{
    return atan2f( x, y );
}

F32 Mathf::Cos( const F32 f )
{
    return cosf( f );
}

F32 Mathf::Sin( const F32 f )
{
    return sinf( f );
}

F32 Mathf::Tan( const F32 f )
{
    return tanf( f );
}

F64 Mathf::Acos( const F64 f )
{
    assert( f >= -1.0f && f <= 1.0f );
    return acos( f );
}

F64 Mathf::Asin( const F64 f )
{
    assert( f >= -1.0f && f <= 1.0f );
    return asin( f );
}

F64 Mathf::Atan( const F64 f )
{
    return atan( f );
}

F64 Mathf::Atan2( const F64 x, const F64 y )
{
    return atan2( x, y );
}

F64 Mathf::Cos( const F64 f )
{
    return cos( f );
}

F64 Mathf::Sin( const F64 f )
{
    return sin( f );
}

F64 Mathf::Tan( const F64 f )
{
    return tan( f );
}

F32 Mathf::Ceil( const F32 f )
{
    return ceilf( f );
}

F32 Mathf::Floor( const F32 f )
{
    return floorf( f );
}

F64 Mathf::Ceil( const F64 f )
{
    return ceil( f );
}

F64 Mathf::Floor( const F64 f )
{
    return floor( f );
}

bool Mathf::IsPow2( const U32 n )
{
    return ( !( n & ( n - 1 ) ) && n );
}

F32 Mathf::Abs( const F32 f )
{
    return fabsf( f );
}

S32 Mathf::Abs( const S32 f )
{
    return abs( f );
}

F64 Mathf::Abs( const F64 f )
{
    return fabs( f );
}

S64 Mathf::Abs( const S64 f )
{
    return abs( f );
}