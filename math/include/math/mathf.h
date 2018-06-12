/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
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

#ifndef M_E
#   define M_E        2.71828182845904523536   // e
#endif

#ifndef M_LOG2E
#   define M_LOG2E    1.44269504088896340736   // log2(e)
#endif

#ifndef M_LOG10E
#   define M_LOG10E   0.434294481903251827651  // log10(e)
#endif

#ifndef M_LN2
#   define M_LN2      0.693147180559945309417  // ln(2)
#endif

#ifndef M_LN10
#   define M_LN10     2.30258509299404568402   // ln(10)
#endif

#ifndef M_PI
#   define M_PI       3.14159265358979323846   // pi
#endif

#ifndef M_PI_2
#   define M_PI_2     1.57079632679489661923   // pi/2
#endif

#ifndef M_PI_4
#   define M_PI_4     0.785398163397448309616  // pi/4
#endif

#ifndef M_1_PI
#   define M_1_PI     0.318309886183790671538  // 1/pi
#endif

#ifndef M_2_PI
#   define M_2_PI     0.636619772367581343076  // 2/pi
#endif

#ifndef M_2_SQRTPI
#   define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#endif

#ifndef M_SQRT2
#   define M_SQRT2    1.41421356237309504880   // sqrt(2)
#endif

#ifndef M_SQRT1_2
#   define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
#endif

BEGIN_MATH_NAMESPACE

namespace Mathf
{
    template< class tN >
    inline tN Epsilon()
    {
        return 0;
    }

    template<>
    inline F64 Epsilon()
    {
        return DBL_EPSILON;
    }

    template<>
    inline F32 Epsilon()
    {
        return FLT_EPSILON;
    }

    template< class tN >
    inline tN Pi()
    {
        return (tN)M_PI;
    }

    template< class tN >
    inline tN Pi2()
    {
        return (tN)M_PI_2;
    }

    template< class tN >
    inline tN Sqrt2()
    {
        return (tN)M_SQRT2;
    }

    template< class tN >
    inline tN E()
    {
        return (tN)M_E;
    }

    template< class tN >
    inline tN Log2E()
    {
        return (tN)M_LOG2E;
    }

    template< class tN >
    inline tN Log10E()
    {
        return (tN)M_LOG10E;
    }

    template< class tN >
    inline tN Ln2()
    {
        return (tN)M_LN2;
    }

    template< class tN >
    inline tN Ln10()
    {
        return (tN)M_LN10;
    }

    F32 Acos(F32 f);
    F32 Asin(F32 f);
    F32 Atan(F32 f);
    F32 Atan2(F32 x, F32 y);
    F32 Cos(F32 f);
    F32 Sin(F32 f);
    F32 Tan(F32 f);

    F64 Acos(F64 f);
    F64 Asin(F64 f);
    F64 Atan(F64 f);
    F64 Atan2(F64 x, F64 y);
    F64 Cos(F64 f);
    F64 Sin(F64 f);
    F64 Tan(F64 f);

    F32 Ceil(F32 f);
    F32 Floor(F32 f);

    F64 Ceil(F64 f);
    F64 Floor(F64 f);

    F32 Round(F32 f);
    F64 Round(F64 f);

    F32 Trunc(F32 f);
    F64 Trunc(F64 f);

    F32 Log(F32 f);
    F32 Log2(F32 f);
    F64 Log(F64 f);
    F64 Log2(F64 f);
    U32 Log2(U32 f);
    U32 Log2(U64 n);
    F32 Log10(F32 f);
    F64 Log10(F64 f);

    F32 Pow(F32 f, F32 exp);
    F64 Pow(F64 f, F64 exp);

    F32 Rint(F32 x);
    F64 Rint(F64 x);

    F32 Sqrt(F32 f);
    F64 Sqrt(F64 f);

    template< class tN >
    inline tN Clamp(tN f, tN min, tN max)
    {
        return f < min ? min : (f > max ? max : f);
    }

    template< class tN >
    inline tN RadToDeg(tN f)
    {
        return f * 180.0f / Pi< tN >();
    }

    template< class tN >
    inline tN DegToRad(tN f)
    {
        return f * Pi< tN >() / 180.0f;
    }

    template< class tN >
    inline Scalar Lerp(tN a, tN b, Scalar t)
    {
        return a + (b - a) * t;
    }

    bool IsPow2(U32 n);

    U32 NextPow2(U32 x);

    template< class tN >
    inline tN Square(tN a)
    {
        return a * a;
    }

    F32 Abs(F32 f);
    S32 Abs(S32 f);

    F64 Abs(F64 f);
    S64 Abs(S64 f);

    template< class tN >
    inline bool Equal(tN a, tN b)
    {
        return Abs(a - b) <= Epsilon< tN >();
    }

    template< typename tN >
    inline tN Min(tN a, tN b)
    {
        return a < b ? a : b;
    }

    template< typename tN >
    inline tN Max(tN a, tN b)
    {
        return a > b ? a : b;
    }

    template< typename tN >
    inline tN Rcp(tN &_a)
    {
        return (tN)1.0 / _a;
    }
}

#endif