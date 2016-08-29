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

#ifndef __MATHF_H__
#define __MATHF_H__

#include "math/types.h"
#include "math/config.h"

#include <assert.h>
#include <cfloat>
#include <cmath>

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

BEGIN_MATH_NAMESPACE

namespace Mathf
{
    template< class Number >
    inline Number GetEpsilon();

    template<>
    inline F64 GetEpsilon()
    {
        return DBL_EPSILON;
    }

    template<>
    inline F32 GetEpsilon()
    {
        return FLT_EPSILON;
    }

    template< class Number >
    inline Number GetPi()
    {
        return ( Number )M_PI;
    }

    template< class Number >
    inline Number Get2Pi()
    {
        return ( Number )M_PI_2;
    }

    template< class Number >
    inline Number GetSqrt2()
    {
        return ( Number )M_SQRT2;
    }

    template< class Number >
    inline Number GetE()
    {
        return ( Number )M_E;
    }

    template< class Number >
    inline Number GetLog2E()
    {
        return ( Number )M_LOG2E;
    }

    template< class Number >
    inline Number GetLog10E()
    {
        return ( Number )M_LOG10E;
    }

    template< class Number >
    inline Number GetLn2()
    {
        return ( Number )M_LN2;
    }

    template< class Number >
    inline Number GetLn10()
    {
        return ( Number )M_LN10;
    }

    F32 Acos( const F32 f );
    F32 Asin( const F32 f );
    F32 Atan( const F32 f );
    F32 Atan2( const F32 x, const F32 y );
    F32 Cos( const F32 f );
    F32 Sin( const F32 f );
    F32 Tan( const F32 f );

    F64 Acos( const F64 f );
    F64 Asin( const F64 f );
    F64 Atan( const F64 f );
    F64 Atan2( const F64 x, const F64 y );
    F64 Cos( const F64 f );
    F64 Sin( const F64 f );
    F64 Tan( const F64 f );

    F32 Ceil( const F32 f );
    F32 Floor( const F32 f );

    F64 Ceil( const F64 f );
    F64 Floor( const F64 f );

    template< class Number >
    inline Number Round( const Number f )
    {
        return f >= 0.0 ? f + 0.5f : ( ( f - ( Number )( S64 )f ) <= -0.5 ? f : f - 0.5f );
    }

    F32 Log( const F32 f );
    F32 Log2( const F32 f );
    F64 Log( const F64 f );
    F64 Log2( const F64 f );
    U32 Log2( const U32 f );
    U32 Log2( U64 n );
    F32 Log10( const F32 f );
    F64 Log10( const F64 f );

    template< class Number >
    inline Number Pow( const Number base, const Number exp )
    {
        return ( Number )std::pow( base, exp );
    }

    template< class Number >
    inline Number Clamp( const Number f, const Number min, const Number max )
    {
        return f < min ? min : ( f > max ? max : f );
    }

    template< class Number >
    inline Number RadToDeg( const Number f )
    {
        return f * 180.0f / GetPi< Number >();
    }

    template< class Number >
    inline Number DegToRad( const Number f )
    {
        return f * GetPi< Number >() / 180.0f;
    }

    template< class Number >
    inline Number Lerp( const Number a, const Number b, const Number t )
    {
        return a + ( b - a ) * t;
    }

    bool IsPow2( const U32 n );

    inline U32 NextPow2( const U32 x )
    {
        U32 y = x - 1;
        y |= y >> 1;
        y |= y >> 2;
        y |= y >> 4;
        y |= y >> 8;
        y |= y >> 16;
        return ++y;
    }

    template< class Number >
    inline Number Square( Number a )
    {
        return a * a;
    }

    template< class Number >
    inline Number Sqrt( const Number f )
    {
        assert( f >= 0.0f );

        return std::sqrt( f );
    }

    F32 Abs( const F32 f );
    S32 Abs( const S32 f );

    F64 Abs( const F64 f );
    S64 Abs( const S64 f );

    template< class Number >
    inline Number Rint( Number x )
    {
        return std::rint( x );
    }

    template< class Number >
    inline bool Equal( const Number a, const Number b )
    {
        return Abs( a - b ) <= GetEpsilon< Number >();
    }

    template< typename Number >
    inline Number GetMin( const Number &a, const Number &b )
    {
        return a < b ? a : b;
    }

    template< typename Number >
    inline Number GetMax( const Number &a, const Number &b )
    {
        return a > b ? a : b;
    }

    template< typename Number >
    inline Number Rcp( const Number &_a )
    {
        return ( Number )1.0 / _a;
    }
}

#endif