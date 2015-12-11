#pragma once
#ifndef __AVX_VEC4D_B_H__
#define __AVX_VEC4D_B_H__
#include "math/types.h"

#include "math/scalar/mathf.h"

#include "math/simd/vectorize.h"
#include "math/simd/simdVectorBoolBase.h"

#include <immintrin.h>
#include <iostream>
#include <limits>

class AvxVec4d_b : public SimdVectorBoolBase< AvxVec4d_b > 
{
public:

    union EasyConvert
    {
        F64 d;
        S64 il;
        U64 ul;
    };

    AvxVec4d_b()
    {}

    inline AvxVec4d_b( bool val ) : 
    mValue( _mm256_castsi256_pd( _mm256_set1_epi64x( -(S64)val ) ) )
    {
    }
    
    /*
    inline AvxVec4d_b( bool b0, bool b1, bool b2, bool b3) :
    mValue( _mm256_castsi256_pd( _mm256_setr_epi64x( -(S64)b0, -(S64)b1, -(S64)b2, -(S64)b3 ) ) )
    {
    }
    */
    
    inline AvxVec4d_b( const __m256d &rhs ) :
    mValue( rhs )
    {
    }

    inline AvxVec4d_b &operator=( const __m256d &rhs )
    {
        mValue = rhs;
        
        return *this;
    }
    
    inline operator __m256d () const
    {
        return mValue;
    }
    
    // TODO: MIGHT CAUSE PROBLEMS WITH MANUAL LOADED VALS
    inline U64 StoreMask() const
    {       
        return (U64)_mm256_movemask_pd( mValue );
    }
     
    void StoreAligned( F64 *dest ) const
    {
        _mm256_store_pd( dest, mValue );
    }

    void LoadAligned( const F64 *src ) 
    {
        mValue = _mm256_load_pd( src );
    }
    
    
    inline void LoadBinaryMask( U8 mask )
    {
        mValue = _mm256_castsi256_pd( _mm256_setr_epi64x(  
                                      -(S64) ( ( mask >> 0 ) & 0x1 ),
                                      -(S64) ( ( mask >> 1 ) & 0x1 ),
                                      -(S64) ( ( mask >> 2 ) & 0x1 ),
                                      -(S64) ( ( mask >> 3 ) & 0x1 ) 
                                    ) );
    } 
    
    bool IsEmpty() const
    {
        return _mm256_testz_si256( _mm256_castpd_si256(mValue), _mm256_castpd_si256(mValue) ) == 1;
    }

private:

    __m256d mValue;
};

inline AvxVec4d_b operator&( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_and_pd( lhs, rhs );
}

inline AvxVec4d_b operator|( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_or_pd( lhs, rhs );
}

inline AvxVec4d_b operator^( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_xor_pd( lhs, rhs );
}

inline AvxVec4d_b operator==( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 16 );
}

inline AvxVec4d_b operator!=( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 28 );
}

inline bool SIMD_Hadd( const AvxVec4d_b &lhs )
{
    return (bool)_mm256_movemask_pd( lhs );
}

#endif