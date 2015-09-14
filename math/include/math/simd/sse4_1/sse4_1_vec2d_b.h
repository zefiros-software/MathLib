#pragma once
#ifndef __SSE4_1_VEC2D_B_H__
#define __SSE4_1_VEC2D_B_H__

#include "math/types.h"

#include "math/simd/vectorize.h"
#include "math/simd/simdVectorBoolBase.h"

#include <smmintrin.h>
#include <limits>

class SSE41Vec2d_b : public SimdVectorBoolBase< SSE41Vec2d_b >
{
public:

    SSE41Vec2d_b()
    {}

    inline SSE41Vec2d_b( bool val ) :
        mValue( _mm_castsi128_pd( _mm_set1_epi32( -( int )val ) ) )
    {
    }

    /*
    inline SSE41Vec2d_b( bool b0, bool b1, bool b2, bool b3 ) :
        mValue( _mm_castsi128_pd( _mm_setr_epi32( -( int )b0, -( int )b1, -( int )b2, -( int )b3 ) ) )
    {
    }
    */
    
    inline SSE41Vec2d_b( const __m128d &rhs ) :
        mValue( rhs )
    {
    }

    inline SSE41Vec2d_b &operator=( const __m128d &rhs )
    {
        mValue = rhs;

        return *this;
    }

    inline operator __m128d() const
    {
        return mValue;
    }

    //template< U32 rotate >
    inline void LoadMask( U32 rotate, U64 mask )
    {
        const U32 rot0 = ( ( 0 + rotate ) & 0x1 );
        const U32 rot1 = ( ( 1 + rotate ) & 0x1 );

        // we use the value as bool, so it doesnt matter
        // if we epi32 this one 
        mValue = _mm_castsi128_pd( _mm_setr_epi32(
                                       -( S64 )( ( mask >> ( 0  + rot0 ) ) & 0x1 ),
                                       -( S64 )( ( mask >> ( 0  + rot0 ) ) & 0x1 ),
                                       -( S64 )( ( mask >> ( 2  + rot1 ) ) & 0x1 ),
                                       -( S64 )( ( mask >> ( 2  + rot1 ) ) & 0x1 )
                                    	       ) );
    }

    inline U64 StoreMask() const
    {       
        return (U64)_mm_movemask_pd( mValue );
    }

    void StoreAligned( F64 *dest ) const
    {
        _mm_store_pd( dest, mValue );
    }

    void LoadAligned( const F64 *src )
    {
        mValue = _mm_load_pd( src );
    }

private:

    __m128d mValue;
};

inline SSE41Vec2d_b operator&( const SSE41Vec2d_b &lhs, const SSE41Vec2d_b &rhs )
{
    return _mm_and_pd( lhs, rhs );
}

inline SSE41Vec2d_b operator|( const SSE41Vec2d_b &lhs, const SSE41Vec2d_b &rhs )
{
    return _mm_or_pd( lhs, rhs );
}

inline SSE41Vec2d_b operator^( const SSE41Vec2d_b &lhs, const SSE41Vec2d_b &rhs )
{
    return _mm_xor_pd( lhs, rhs );
}

inline SSE41Vec2d_b operator==( const SSE41Vec2d_b &lhs, const SSE41Vec2d_b &rhs )
{
    return _mm_cmpeq_pd( lhs, rhs );
}

inline SSE41Vec2d_b operator!=( const SSE41Vec2d_b &lhs, const SSE41Vec2d_b &rhs )
{
    return _mm_cmpneq_pd( lhs, rhs );
}

inline bool SIMD_Hadd( const SSE41Vec2d_b &lhs )
{
    __m128d tmp0 = _mm_hadd_pd( lhs, lhs );
    
    return (bool)_mm_cvtsd_si32( tmp0 );
}

#endif