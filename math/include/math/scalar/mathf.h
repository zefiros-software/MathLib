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
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>

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

    template< class Number >
    inline Number Acos( const Number f )
    {
        assert( f >= -1.0f && f <= 1.0f );

        return std::acos( f );
    }

    template< class Number >
    inline Number Asin( const Number f )
    {
        assert( f >= -1.0f && f <= 1.0f );

        return asin( f );
    }

    template< class Number >
    inline Number Atan( const Number f )
    {
        return std::atan( f );
    }

    template< class Number >
    inline Number Atan2( const Number x, const Number y )
    {
        return std::atan2( x, y );
    }

    template< class Number >
    inline Number Cos( const Number f )
    {
        return std::cos( f );
    }

    template< class Number >
    inline Number Sin( const Number f )
    {
        return std::sin( f );
    }

    template< class Number >
    inline Number Tan( const Number f )
    {
        return std::tan( f );
    }

    template< class Number >
    inline Number Exp( const Number f )
    {
        return std::exp( f );
    }

    template< class Number >
    inline Number Ceil( const Number f )
    {
        return std::ceil( f );
    }

    template< class Number >
    inline Number Floor( const Number f )
    {
        return std::floor( f );
    }

    template< class Number >
    inline Number Round( const Number f )
    {
        return f >= 0.0 ? f + 0.5f : ( ( f - ( Number )( S32 )f ) <= -0.5 ? f : f - 0.5f );
    }

    template< class Number >
    inline Number Log( const Number f )
    {
        assert( f > 0.0f );

        return std::log( f );
    }

    template< class Number >
    inline Number Log2( const Number f )
    {
        assert( f > 0.0f );

        return ( Number )std::log2( f );
    }

    template< class Number >
    inline Number Log10( const Number f )
    {
        assert( f > 0.0f );

        return std::log10( f );
    }

    template< class Number >
    inline Number Pow( const Number base, const Number exp )
    {
        return std::pow( base, exp );
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

    inline bool IsPow2( const U32 n )
    {
        return ( !( n & ( n - 1 ) ) && n );
    }

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

    template< class Number >
    inline Number Abs( const Number f )
    {
        return std::abs( f );
    }

    template<>
    inline F32 Abs( const F32 f )
    {
        return fabsf( f );
    }

    template<>
    inline F64 Abs( const F64 f )
    {
        return fabs( f );
    }

    template< class Number >
    inline Number Rint( Number x )
    {
        return std::rint( x );
    }

    template< class Number >
    inline bool Equal( const Number a, const Number b )
    {
        return std::abs( a - b ) <= GetEpsilon< Number >();
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