#pragma once
#ifndef __AVXVEC4D_H__
#define __AVXVEC4D_H__

#include "math/types.h"

#include "math/simd/simdMathf.h"
#include "math/simd/simdVectorBase.h"
#include "math/simd/simdBaseTraits.h"

#include "math/util/memory/stackAlign.h"

#include <immintrin.h>
#include <iostream>
#include <limits>

class AvxVecd;
class AvxVeci;
class AvxVecd_b;

class AvxVec4d;
class AvxVec4i;
class AvxVec4d_b;

template <>
struct AvxSimdTraits<F64>  : public BaseSimdTraits<F64, S64, 4, 32>
{  
    typedef AvxVec4d vec_n_type;
    typedef AvxVec4i veci_n_type;
    typedef AvxVec4d_b vecb_n_type;
    typedef AvxVecd vec_1_type;
    typedef AvxVeci veci_1_type;
    typedef AvxVecd_b vecb_1_type;
    static const size_t bytesPerValue = 8;
    static const size_t registers = 2;
};

//************************
//
// AVX double 8 bool vector
//
//************************

class AvxVec4d_b
{
    friend inline AvxVec4d_b operator&&( AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator||( AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator!(  AvxVec4d_b lhs );
    friend inline AvxVec4d_b operator&(  AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator|(  AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator^(  AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator==( AvxVec4d_b lhs, AvxVec4d_b rhs );
    friend inline AvxVec4d_b operator!=( AvxVec4d_b lhs, AvxVec4d_b rhs );
    
public:
    
    inline AvxVec4d_b();
    inline AvxVec4d_b( bool val );
    //inline AvxVec4d_b( const bool *ptr );
    inline AvxVec4d_b( const __m256d &rhs );
    //inline AvxVec4d_b( const AvxSimdTraits<F64>::bool_array &array );
    
    inline operator __m256d () const;
    
    static inline bool ConvertToBool( U64 val );
    static inline U64 ConvertFromBool( bool b );
    
private:
    
    __m256d mValue;
};

inline bool AvxVec4d_b::ConvertToBool( U64 val )
{
    // Check if the sign bit is set
    return S64(val) < S64(0);
}

inline U64 AvxVec4d_b::ConvertFromBool( bool b )
{
    // Set the complete mask and enable the sign bit
    return -U64( b );
}


AvxVec4d_b::AvxVec4d_b()
{}

inline AvxVec4d_b::AvxVec4d_b( bool val ) :
mValue( _mm256_castsi256_pd( _mm256_set1_epi64x( ConvertFromBool( val ) ) ) )
{
}


inline AvxVec4d_b::AvxVec4d_b( const __m256d &rhs ) :
mValue( rhs )
{
}

inline AvxVec4d_b::operator __m256d () const
{
    return mValue;
}

inline AvxVec4d_b operator&&( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return lhs & rhs;
}

inline AvxVec4d_b operator||( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return lhs | rhs;
}

inline AvxVec4d_b operator!( AvxVec4d_b lhs )
{
    return _mm256_xor_pd(AvxVec4d_b(true), lhs );
}


inline AvxVec4d_b operator&( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return _mm256_and_pd( lhs, rhs );
}

inline AvxVec4d_b operator|( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return _mm256_or_pd( lhs, rhs );
}

inline AvxVec4d_b operator^( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return _mm256_xor_pd( lhs, rhs );
}

inline AvxVec4d_b operator==( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return !( lhs != rhs );
}

inline AvxVec4d_b operator!=( AvxVec4d_b lhs, AvxVec4d_b rhs )
{
    return _mm256_xor_pd(lhs, rhs);
}

namespace SIMD
{
    inline bool ExtractValue(  AvxVec4d_b lhs, U32 loc )
    {
        return ConvertToBool( SimdHelper::ExtractValueFromVector<AvxVec4d_b, __m256d, U64>( lhs, loc ) );
    }
    
    inline U64 StoreMask( AvxVec4d_b lhs )
    {
        return (U64)_mm256_movemask_pd( lhs );
    }
    
    inline void LoadBinaryMask( AvxVec4d_b &lhs, U64 mask )
    {
        lhs = _mm256_castsi256_pd( _mm256_setr_epi64x(
                                   -(S64) ( ( mask >> 0 ) & 0x1 ),
                                   -(S64) ( ( mask >> 1 ) & 0x1 ),
                                            -(S64) ( ( mask >> 2 ) & 0x1 ),
                                            -(S64) ( ( mask >> 3 ) & 0x1 )
                                                         ) );
    }
    
    inline bool Any( AvxVec4d_b lhs )
    {
        return !bool( _mm256_testz_si256( _mm256_castpd_si256(lhs), _mm256_castpd_si256(lhs) ) );
    }
    
    inline bool All( AvxVec4d_b lhs )
    {
        return !Any(lhs);
    }
    
    inline AvxVec4d_b IfThenElse( AvxVec4d_b sel, AvxVec4d_b lhs, AvxVec4d_b rhs )
    {
        return _mm256_blendv_ps( rhs, lhs, sel );
    }
}



//************************
//
// AVX l int vector
//
//************************


class AvxVec4i
{
    friend inline AvxVec4i operator+( const AvxVec4i &lhs, const AvxVec4i &rhs );
    friend inline AvxVec4i operator-( const AvxVec4i &lhs, const AvxVec4i &rhs );
    
public:
    
    inline AvxVec4i();
    inline AvxVec4i( S64 val );
    inline AvxVec4i( const S64 *ptr );
    inline AvxVec4i( const __m256i &rhs );
    
    inline operator __m256i() const;
    
    inline S64 operator []( U32 loc ) const;
    
    inline AvxVec4d_b AsBool() const;
    inline AvxVec4d_b ConvertToBool() const;
    
    inline AvxVec4d AsFloat() const;
    inline AvxVec4d ConvertToFloat() const;
    
    DEFINE_ASSIGNMENT_BASE_OPERATORS( AvxVec4i, S64 );
    
private:
    
    __m256i mValue;
};

inline AvxVec4i::AvxVec4i()
{}

inline AvxVec4i::AvxVec4i( S64 val ) :
    mValue( _mm256_set1_epi64x( val ) )
{
}

inline AvxVec4i::AvxVec4i( const S64 *src ) :
    mValue( _mm256_set_epi64x( src[3], src[2], src[1], src[0] ) )
{
}

inline AvxVec4i::AvxVec4i( const __m256i &rhs ) :
    mValue( rhs )
{
    
}

inline AvxVec4i::operator __m256i() const
{
    return mValue;
}

inline S64 AvxVec4i::operator []( U32 loc ) const
{
    return SimdHelper::ExtractValueFromVector<AvxVec4i, __m256i, S64>( mValue, loc );
}

inline AvxVec4i operator+( const AvxVec4i &lhs )
{
    return lhs;
}

inline AvxVec4i operator-( const AvxVec4i &lhs )
{
    return AvxVec4i(0.0) - lhs;
}

/* Inspired by part
 
 Copyright (c) 2012, 2013 Erik Schnetter <eschnetter@gmail.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

// { START

inline AvxVec4d_b AvxVec4i::AsBool() const
{
    return _mm256_castsi256_pd(mValue);
}

inline AvxVec4d_b AvxVec4i::ConvertToBool() const
{
    // Result: convert_bool(0)=false, convert_bool(else)=true
//#ifdef __AVX2__
    return *this != AvxVec4i(S64(0));
/*
#else
    // There is no intrinsic to compare to zero. Instead, we check
    // whether x is positive and x-1 is negative.
    intvec_t x = *this;
    // We know that boolvec_t values depend only on the sign bit
    // return (~(x-1) | x).as_bool();
    // return x.as_bool() || !(x-1).as_bool();
    return x.as_bool() || (x + (FP::signbit_mask - 1)).as_bool();
#endif
*/
}

inline AvxVec4i operator+( const AvxVec4i &lhs, const AvxVec4i &rhs )
{
#ifdef __AVX2__
    return _mm256_add_epi64(lhs, rhs.mValue);
#else
    __m128i vlo = _mm256_castsi256_si128(lhs);
    __m128i vhi = _mm256_extractf128_si256(lhs, 1);
    __m128i xvlo = _mm256_castsi256_si128(rhs.mValue);
    __m128i xvhi = _mm256_extractf128_si256(rhs.mValue, 1);
    vlo = _mm_add_epi64(vlo, xvlo);
    vhi = _mm_add_epi64(vhi, xvhi);
    return _mm256_insertf128_si256(_mm256_castsi128_si256(vlo), vhi, 1);
#endif
}

inline AvxVec4i operator-( const AvxVec4i &lhs, const AvxVec4i &rhs )
{
#ifdef __AVX2__
    return _mm256_sub_epi64(lhs, rhs.mValue);
#else
    __m128i vlo = _mm256_castsi256_si128(lhs);
    __m128i vhi = _mm256_extractf128_si256(lhs, 1);
    __m128i xvlo = _mm256_castsi256_si128(rhs.mValue);
    __m128i xvhi = _mm256_extractf128_si256(rhs.mValue, 1);
    vlo = _mm_sub_epi64(vlo, xvlo);
    vhi = _mm_sub_epi64(vhi, xvhi);
    return _mm256_insertf128_si256(_mm256_castsi128_si256(vlo), vhi, 1);
#endif
}

inline AvxVec4i operator&(const AvxVec4i &lhs, const AvxVec4i &rhs)
{
#ifdef __AVX2__
    return _mm256_and_si256(lhs, rhs);
#else
    return _mm256_castpd_si256(
                               _mm256_and_pd(_mm256_castsi256_pd(lhs), _mm256_castsi256_pd(rhs)));
#endif
}

inline AvxVec4i operator|(const AvxVec4i &lhs, const AvxVec4i &rhs)
{
#ifdef __AVX2__
    return _mm256_or_si256(lhs, rhs);
#else
    return _mm256_castpd_si256(
                               _mm256_or_pd(_mm256_castsi256_pd(lhs), _mm256_castsi256_pd(rhs)));
#endif
}

inline AvxVec4i operator^(const AvxVec4i &lhs, const AvxVec4i &rhs)
{
#ifdef __AVX2__
    return _mm256_xor_si256(lhs, rhs);
#else
    return _mm256_castpd_si256(
                               _mm256_xor_pd(_mm256_castsi256_pd(lhs), _mm256_castsi256_pd(rhs)));
#endif
}

inline AvxVec4i operator~(const AvxVec4i &lhs)
{
    return AvxVec4i(~U64(0)) ^ lhs;
}


// } END

//************************
//
// AVX double vector
//
//************************

class AvxVec4d
{
    friend AvxVec4d operator+( AvxVec4d lhs, AvxVec4d rhs );
    friend AvxVec4d operator-( AvxVec4d lhs, AvxVec4d rhs );
    friend AvxVec4d operator*( AvxVec4d lhs, AvxVec4d rhs );
    friend AvxVec4d operator/( AvxVec4d lhs, AvxVec4d rhs );
    
public:

    inline AvxVec4d();
    inline AvxVec4d( F64 val );
    //inline AvxVec4d( const F64 *src );
    //inline AvxVec4d( F64 v0, F64 v1, F64 v2, F64 v3 );
    inline AvxVec4d( const __m256d &rhs );
    //inline AvxVec4d( const AvxSimdTraits<F64>::type_array &array );

    inline operator __m256d() const;

    static inline AvxVec4d GetZero();
    
    //DEFINE_ASSIGNMENT_BASE_OPERATORS( AvxVec4d, F64 );
    //DEFINE_ASSIGNMENT_EXT_OPERATORS( AvxVec4d, F64 );
    //DEFINE_INC_OPERATORS( AvxVec4d, F64 )

private:

    __m256d mValue;
};


//
// Internal
//

inline AvxVec4d::AvxVec4d()
{}

inline AvxVec4d::AvxVec4d( F64 val ) : mValue( _mm256_set1_pd( val ) )
{
}

inline AvxVec4d::AvxVec4d( const __m256d &rhs ) : mValue( rhs )
{
    
}

inline AvxVec4d::operator __m256d() const
{
    return mValue;
}

inline AvxVec4d AvxVec4d::GetZero()
{
    return _mm256_setzero_pd();
}


namespace SIMD
{
    inline F64 ExtractValue( AvxVec4d lhs, U32 loc )
    {
        return SimdHelper::ExtractValueFromVector<AvxVec4d, __m256d, F64>( lhs, loc );
    }
    
    inline AvxVec4d LoadU( const F64 *src )
    {
        return  _mm256_loadu_pd( src );
    }
    
    inline AvxVec4d Load( const F64 *src )
    {
        return _mm256_load_pd( src );
    }
    
    inline void StoreU( AvxVec4d lhs, F64 *dest )
    {
        _mm256_storeu_pd( dest, lhs );
    }
    
    inline void Store( AvxVec4d lhs,  F64 *dest )
    {
        _mm256_store_pd( dest, lhs );
    }
    
    inline AvxVec4i AsInt( AvxVec4d lhs )
    {
        return _mm256_castpd_si256(lhs);
    }
    
    inline AvxVec4i ConvertToInt( AvxVec4d lhs )
    {
        AvxVec4i r;
        
        for (U32 i = 0; i < 4; ++i)
        {
            SimdHelper::SetValueInVector<AvxVec4i, __m256i, S64>( r, i, S64(ExtractValue(lhs,i)) );
        }
        
        return r;
    }
    
    
    
}


//
// Math
//

inline AvxVec4d operator+( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_add_pd( lhs, rhs );
}

inline AvxVec4d operator-( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_sub_pd( lhs, rhs );
}

inline AvxVec4d operator*( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_mul_pd( lhs, rhs );
}

inline AvxVec4d operator/( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_div_pd( lhs, rhs );
}

//
// Comparison
//

inline AvxVec4d_b operator== ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 0 );
}

inline AvxVec4d_b operator!= ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 12 );
}

inline AvxVec4d_b operator< ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 17 );
}

inline AvxVec4d_b operator<= ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 18 );
}

inline AvxVec4d_b operator> ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 30 );
}

inline AvxVec4d_b operator>= ( AvxVec4d lhs, AvxVec4d rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 29 );
}

inline AvxVec4d operator&( AvxVec4d lhs, AvxVec4d_b rhs )
{
    return _mm256_and_pd( lhs, rhs );
}

inline AvxVec4d operator&( AvxVec4d_b lhs, AvxVec4d rhs )
{
    return _mm256_and_pd( lhs, rhs );
}

//DEFINE_COMMON_OPERATORS( AvxVec4d, F64 );

//
// Special
//
namespace SIMD
{
    inline AvxVec4d Sqrt( AvxVec4d lhs )
    {
        return _mm256_sqrt_pd( lhs );
    }
    
    inline AvxVec4d Rcp( AvxVec4d lhs )
    {
        return ( AvxVec4d(1.0) / lhs );
    }
    
    inline AvxVec4d RcpSqrt( AvxVec4d lhs )
    {
        return Rcp( Sqrt( lhs ) );
    }
    
    inline AvxVec4d IfThenElse( AvxVec4d_b sel, AvxVec4d lhs, AvxVec4d rhs )
    {
        return _mm256_blendv_pd( rhs, lhs, sel );
    }
    
    inline F64 Sum( AvxVec4d lhs )
    {
        const __m128d x128 = _mm_add_pd(_mm256_extractf128_pd(lhs, 1), _mm256_castpd256_pd128(lhs));
        const __m128d x64 = _mm_add_sd( x128, _mm_shuffle_pd(x128, x128, 0x3 ) );
        return _mm_cvtsd_f64(x64);
    }
    
    // Inspired by GROMACS
    inline F64 SumStoreN( AvxVec4d lhs[4], F64 *dest )
    {
        // temp0: v0l v1l v0u v1u
        __m256d temp0 = _mm256_hadd_pd( lhs[0], lhs[1] );
        
        // temp1: v2l v3l v2u v3u
        __m256d temp1 = _mm256_hadd_pd( lhs[2], lhs[3] );
        
        // temp2: v0u v1u v2l v3l
        const S32 controll1 = ( 1 ) | ( 2 << 4 );
        __m256d temp2 = _mm256_permute2f128_pd(temp0, temp1, controll1);

        // temp0: v0lu v1ul X X
        temp0 = _mm256_add_pd( temp0, temp2 );
        
        // temp0: X X v2ul v3ul
        temp1 = _mm256_add_pd( temp1, temp2 );
        
        const S32 controll2 = ( 1 << 2 ) | ( 1 << 3 );
        // temp0: v0lu v1ul v2ul v3ul
        temp0 = _mm256_blend_pd(temp0, temp1, controll2);
        
        __m256d lv = Load( dest );
        Store( lv + temp0, dest );
        
        return Sum( AvxVec4d(temp0) );
    }
    
    inline AvxVec4d Rint( AvxVec4d lhs )
    {
        return _mm256_round_pd( lhs, _MM_FROUND_TO_NEAREST_INT );
    }
    
    inline AvxVec4d Sin( AvxVec4d lhs )
    {
        return Mathf::_SGA< AvxSimdTraits<F64> >::SGA_Sin_F64( lhs );
    }
    
    inline AvxVec4d MADD( AvxVec4d mul1, AvxVec4d mul2, AvxVec4d add )
    {
        return ( mul1 * mul2 ) + add;
    }
    
    inline AvxVec4d MSUB( AvxVec4d mul1, AvxVec4d mul2, AvxVec4d sub )
    {
        return ( mul1 * mul2 ) - sub;
    }

}

//
// Int vec
//

inline AvxVec4d AvxVec4i::AsFloat() const
{
    return _mm256_castsi256_pd(mValue);
}

inline AvxVec4d AvxVec4i::ConvertToFloat() const
{
    AvxVec4d r;
    
    for (U32 i = 0; i < 4; ++i)
    {
        SimdHelper::SetValueInVector<AvxVec4d, __m256d, F64>( r, i, F64((*this)[i]) );
    }
    
    return r;
}

#endif