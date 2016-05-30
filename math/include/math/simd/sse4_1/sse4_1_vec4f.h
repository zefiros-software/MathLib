#pragma once
#ifndef __SSE4_1_VEC4f_H__
#define __SSE4_1_VEC4f_H__

#include "math/types.h"

#include "math/simd/simdBaseTraits.h"
#include "math/simd/simdVectorBase.h"

#include "math/simd/sse4_1/sse4_1_vec4f_b.h"

#include <smmintrin.h>
#include <iostream>
#include <limits>

class SSE41Vec4f;

template <>
struct SSE4_1SimdTraits<F32> : public BaseSimdTraits<F32>
{
    typedef SSE41Vec4f vec_type;
    typedef SSE41Vec4f_b bool_type;
    static const size_t width = 4;
    static const size_t bytesPerValue = 4;
    static const size_t registers = 1;
    static const size_t alignment = 16;
};

class SSE41Vec4f : public SimdVectorBase< SSE41Vec4f, F32>
{
public:

    union EasyConvert
    {
        F32 f;
        S32 i;
        U32 u;
    };

    SSE41Vec4f()
    {}

    inline SSE41Vec4f( F32 val ) : mValue( _mm_set1_ps( val ) )
    {
    }

    inline SSE41Vec4f( F32 v0, F32 v1, F32 v2, F32 v3 ) :
        mValue( _mm_set_ps( v3, v2, v1, v0 ) )
    {
    }
    
    inline SSE41Vec4f( const __m128 &rhs ) : mValue( rhs )
    {

    }

    inline SSE41Vec4f &operator=( const __m128 &rhs )
    {
        mValue = rhs;

        return *this;
    }

    inline operator __m128() const
    {
        return mValue;
    }

    void LoadUnaligned( const F32 *src )
    {
        mValue =  _mm_loadu_ps( src );
    }

    void LoadAligned( const F32 *src )
    {
        mValue = _mm_load_ps( src );
    }

    void StoreUnaligned( F32 *dest ) const
    {
        _mm_storeu_ps( dest, mValue );
    }

    void StoreAligned( F32 *dest ) const
    {
        _mm_store_ps( dest, mValue );
    }

    void RotateOne( U32 rotation )
    {
        const S32 select = ( 1 ) | ( 2 << 2 ) | ( 3 << 4 ) | ( 0 << 6 );
        mValue = _mm_shuffle_ps( mValue, mValue, select );
    }
    
    static inline U32 RotateIndex( U32 rotation, U32 index )
    {
        const U32 registerOffset = 4;
        
        const U32 rotatedIndex = ( ( index + rotation ) & ( registerOffset - 1 ) );
    
        return rotatedIndex;
    }

    inline SSE41Vec4f RoundToNearest() const
    {
        return _mm_round_ps( mValue, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
    }
    
    template< U32 index >
    inline SSE41Vec4f BroadCastIndex() const
    {     
        const S32 selector = index % 4;
        const S32 select = ( selector ) | ( selector << 2 ) | ( selector << 4 ) | ( selector << 6 );
        
        return _mm_shuffle_ps( mValue, mValue, select );
    }
    
    inline static SSE41Vec4f GetZero()
    {
        return _mm_setzero_ps();
    }
    
    inline static SSE41Vec4f GetFullMask()
    {
        EasyConvert easyc;
        easyc.u = 0xFFFFFFFF;
        return _mm_set1_ps( easyc.f );
    }

private:

    __m128 mValue;
};

//
// Math
//

inline SSE41Vec4f operator+( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_add_ps( lhs, rhs );
}

inline SSE41Vec4f operator-( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_sub_ps( lhs, rhs );
}

inline SSE41Vec4f operator*( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_mul_ps( lhs, rhs );
}

inline SSE41Vec4f operator/( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_div_ps( lhs, rhs );
}

//
// Comparison
//

inline SSE41Vec4f_b operator== ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmpeq_ps( lhs, rhs );
}

inline SSE41Vec4f_b operator!= ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmpneq_ps( lhs, rhs );
}

inline SSE41Vec4f_b operator< ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmplt_ps( lhs, rhs );
}

inline SSE41Vec4f_b operator<= ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmple_ps( lhs, rhs );
}

inline SSE41Vec4f_b operator> ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmpgt_ps( lhs, rhs );
}

inline SSE41Vec4f_b operator>= ( const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_cmpge_ps( lhs, rhs );
}

inline SSE41Vec4f operator&( const SSE41Vec4f &lhs, const SSE41Vec4f_b &rhs ) 
{
    return _mm_and_ps( lhs, rhs );
}

inline SSE41Vec4f operator&( const SSE41Vec4f_b &lhs, const SSE41Vec4f &rhs ) 
{
    return _mm_and_ps( lhs, rhs );
}

//
// Special
//

inline SSE41Vec4f SIMD_Sqrt( const SSE41Vec4f &lhs )
{
    return _mm_sqrt_ps( lhs );
}

inline SSE41Vec4f SIMD_Rcp( const SSE41Vec4f &lhs )
{
    return 1.0 / lhs;
    //return _mm_rcp_ps( lhs );
}

inline SSE41Vec4f SIMD_RcpSqrt( const SSE41Vec4f &lhs )
{
    __m128 temp = _mm_rsqrt_ps( lhs );
    
    // newton rhapson cycle
    __m128 temp2 = _mm_mul_ps( _mm_sub_ps( _mm_set1_ps(3.0f), _mm_mul_ps(_mm_mul_ps(temp, temp), lhs) ), temp );
    
    return _mm_mul_ps( _mm_set1_ps(0.5f), temp2 );
}

inline SSE41Vec4f SIMD_Select( const SSE41Vec4f_b &sel, const SSE41Vec4f &lhs, const SSE41Vec4f &rhs )
{
    return _mm_blendv_ps( rhs, lhs, sel );
}

//http://stackoverflow.com/questions/13219146/how-to-sum-m256-horizontally
inline F32 SIMD_Hadd( const SSE41Vec4f &lhs )
{
    __m128 tmp0 = _mm_hadd_ps( lhs, lhs );
    __m128 tmp1 = _mm_hadd_ps( tmp0, tmp0 );

    return _mm_cvtss_f32( tmp1 );
}

template< U32 index >
inline SSE41Vec4f SIMD_HaddToIndex( const SSE41Vec4f &lhs )
{
    __m128 tmp0 = _mm_hadd_ps( lhs, lhs );
    __m128 tmp1 = _mm_hadd_ps( tmp0, tmp0 );;
 
    // Two cases, either target is hi register or target is low register
    __m128 zero = _mm_setzero_ps();
        
    const U32 controll = 1 << ( index % 4 );
    __m128 result = _mm_blend_ps( zero, tmp1, controll );
    
    return result;
}

inline SSE41Vec4f FMA_ADD( const SSE41Vec4f &mul1, const SSE41Vec4f &mul2, const SSE41Vec4f &add )
{
    return mul1 * mul2 + add;
}

inline SSE41Vec4f FMA_SUB( const SSE41Vec4f &mul1, const SSE41Vec4f &mul2, const SSE41Vec4f &sub )
{
    return mul1 * mul2 - sub;
}

#endif