#pragma once
#ifndef __AVX2_VEC8f_H__
#define __AVX2_VEC8f_H__

#include "math/types.h"

#include "math/simd/simdBaseTraits.h"
#include "math/simd/simdVectorBase.h"

#include "math/simd/avx/avx_vec8f_b.h"

#include <immintrin.h>
#include <iostream>
#include <limits>


class AvxVec8f;

template <>
struct AvxSimdTraits<F32> : public BaseSimdTraits<F32>
{
    
    typedef AvxVec8f vec_type;
    typedef AvxVec8f_b bool_type;
    static const size_t width = 8;
    static const size_t bytesPerValue = 4;
    static const size_t registers = 2;
    static const size_t alignment = 32;
};

class AvxVec8f : public SimdVectorBase< AvxVec8f, F32>
{
public:
    
    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    };

    AvxVec8f()
    {}
    
    inline AvxVec8f( const F32 *src ) : mValue( _mm256_load_ps( src ) )
    {
    }

    inline AvxVec8f( F32 val ) : mValue( _mm256_set1_ps( val ) )
    {
    }
    
    inline AvxVec8f( F32 v1, F32 v2, F32 v3, F32 v4,
                     F32 v5, F32 v6, F32 v7, F32 v8 ) : 
                     mValue( _mm256_set_ps( v8, v7, v6, v5,
                                            v4, v3, v2, v1 ) )
    {
    }

    inline AvxVec8f( const __m256 &rhs ) : mValue( rhs )
    {

    }

    inline AvxVec8f &operator=( const __m256 &rhs )
    {
        mValue = rhs;

        return *this;
    }

    inline operator __m256() const
    {
        return mValue;
    }

    inline void LoadUnaligned( const F32 *src )
    {
        mValue =  _mm256_loadu_ps( src );
    }

    inline void LoadAligned( const F32 *src )
    {
        mValue = _mm256_load_ps( src );
    }

    inline void StoreUnaligned( F32 *dest ) const
    {
        _mm256_storeu_ps( dest, mValue );
    }

    inline void StoreAligned( F32 *dest ) const
    {
        _mm256_store_ps( dest, mValue );
    }
    
    inline AvxVec8f RoundToNearest() const
    {
        //return _mm256_round_ps( mValue, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
        return _mm256_round_ps( mValue, 0x00 | 0x08 );

    }
    
    template< U32 index >
    inline AvxVec8f BroadCastIndex() const
    {
        __m256 temp;
        
        if ( index >= 4 )
        {
            
            temp = _mm256_permute2f128_ps( mValue, mValue, 1 | ( 1 << 4 ) );
        }
        else
        {
            temp = _mm256_permute2f128_ps( mValue, mValue, 0 );
        }
        
        const S32 selector = index % 4;
        const S32 select = ( selector ) | ( selector << 2 ) | ( selector << 4 ) | ( selector << 6 );
        
        return _mm256_shuffle_ps( temp, temp, select );
    }
    
    inline static AvxVec8f GetZero()
    {
        return _mm256_setzero_ps();
    }
    
    inline static AvxVec8f GetFullMask()
    {
        EasyConvert easyc;
        easyc.u = 0xFFFFFFFF;
        return _mm256_set1_ps( easyc.f );
    }

    //
    // Non-generic
    //
    
    inline __m256d CastDoubleLower() const
    {
        //extract lower half
        __m128 temp = _mm256_extractf128_ps( mValue, 0 );
        
        return _mm256_cvtps_pd( temp );
    }
    
    inline __m256d CastDoubleUpper() const
    {
        //extract upper half
        __m128 temp = _mm256_extractf128_ps( mValue, 1 );
        
        return _mm256_cvtps_pd( temp );      
    }

private:

    __m256 mValue;
};

//
// Math
//

inline AvxVec8f operator+( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_add_ps( lhs, rhs );
}

inline AvxVec8f operator-( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_sub_ps( lhs, rhs );
}

inline AvxVec8f operator*( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_mul_ps( lhs, rhs );
}

inline AvxVec8f operator/( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_div_ps( lhs, rhs );
}

//
// Comparison
//

// O: Ordered // NaN and 1.0 gives false
// U: Unordered // NaN and 1.0 gives false
// S: Signal NaN exceptions
// Q: Do not throw NaN exceptions

inline AvxVec8f_b operator== ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 0 );
}

inline AvxVec8f_b operator!= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 12 );
}

inline AvxVec8f_b operator< ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 17 );
}

inline AvxVec8f_b operator<= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 18 );
}

inline AvxVec8f_b operator> ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 30 );
}

inline AvxVec8f_b operator>= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 29 );
}

inline AvxVec8f operator&( const AvxVec8f &lhs, const AvxVec8f &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}

inline AvxVec8f operator&( const AvxVec8f &lhs, const AvxVec8f_b &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}

inline AvxVec8f operator&( const AvxVec8f_b &lhs, const AvxVec8f &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}


//
// FMA
//

inline AvxVec8f FMA_ADD( const AvxVec8f &mul1, const AvxVec8f &mul2, const AvxVec8f &add )
{
#if SIMD_INSTRUCTION_SET >= 7
    return _mm256_fmadd_ps( mul1, mul2, add );
#else
    return ( mul1 * mul2 ) + add;
#endif
}

inline AvxVec8f FMA_SUB( const AvxVec8f &mul1, const AvxVec8f &mul2, const AvxVec8f &sub )
{
#if SIMD_INSTRUCTION_SET >= 7
    return _mm256_fmsub_ps( mul1, mul2, sub );
#else
    return ( mul1 * mul2 ) - sub;
#endif
}


//
// Special
//

inline AvxVec8f SIMD_Sqrt( const AvxVec8f &lhs )
{
    return _mm256_sqrt_ps( lhs );
}

inline AvxVec8f SIMD_RcpSqrt( const AvxVec8f &lhs )
{
    __m256 temp = _mm256_rsqrt_ps( lhs );
    
    // newton rhapson cycle
    __m256 temp2 = _mm256_mul_ps( _mm256_sub_ps( _mm256_set1_ps(3.0f), _mm256_mul_ps(_mm256_mul_ps(temp, temp), lhs) ), temp );
    
    return _mm256_mul_ps( _mm256_set1_ps(0.5f), temp2 );
}

inline AvxVec8f SIMD_Rcp( const AvxVec8f &lhs )
{
    return 1.0 / lhs;
}

inline AvxVec8f SIMD_Select( const AvxVec8f_b &sel, const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_blendv_ps( rhs, lhs, sel );
}

inline F32 SIMD_Hadd( const AvxVec8f &lhs )
{
    const __m128 x128 = _mm_add_ps(_mm256_extractf128_ps(lhs, 1), _mm256_castps256_ps128(lhs));
    const __m128 x64 = _mm_add_ps(x128, _mm_movehl_ps(x128, x128));
    const __m128 x32 = _mm_add_ss(x64, _mm_shuffle_ps(x64, x64, 0x55));
    return _mm_cvtss_f32(x32);
}

template< U32 index >
inline AvxVec8f SIMD_HaddToIndex( const AvxVec8f &lhs )
{
    const __m128 x128 = _mm_add_ps(_mm256_extractf128_ps(lhs, 1), _mm256_castps256_ps128(lhs));
    const __m128 x64 = _mm_add_ps(x128, _mm_movehl_ps(x128, x128));
    const __m128 x32 = _mm_add_ps(_mm_shuffle_ps(x64,x64,0), _mm_shuffle_ps(x64, x64, 0x55));
 
    // Two cases, either target is hi register or target is low register
    __m256 zero = _mm256_setzero_ps();
        
    const U32 controll = 1 << ( index % 4 );
    __m256 result = _mm256_blend_ps( zero, _mm256_castps128_ps256(x32), controll );
    
    if ( index >= 4 )
    {
        //switch halves
        result = _mm256_permute2f128_ps( result, result, 1 );
    }
    
    return result;
}


#endif