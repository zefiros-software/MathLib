#pragma once
#ifndef __AVX2_VEC8B_H__
#define __AVX2_VEC8B_H__

#include "math/types.h"

#include "math/scalar/mathf.h"

#include "math/simd/vectorize.h"
#include "math/simd/simdVectorBoolBase.h"

#include <immintrin.h>
#include <iostream>
#include <limits>

class AvxVec8f_b : public SimdVectorBoolBase< AvxVec8f_b > 
{
public:

    union EasyConv
    {
        U32 u;
        S32 i;
        F32 f;
    };

    AvxVec8f_b()
    {}

    inline AvxVec8f_b( bool val ) : 
    mValue( _mm256_castsi256_ps( _mm256_set1_epi32( -(int)val ) ) )
    {
    }
    
    /*
    inline AvxVec8f_b( bool b0, bool b1, bool b2, bool b3,
                        bool b4, bool b5, bool b6, bool b7 ) :
    mValue( _mm256_castsi256_ps( _mm256_setr_epi32( -(int)b0, -(int)b1, -(int)b2, -(int)b3,
                                                    -(int)b4, -(int)b5, -(int)b6, -(int)b7 ) ) )
    {
    }
    */
    
    inline AvxVec8f_b( const __m256 &rhs ) :
    mValue( rhs )
    {
    }

    inline AvxVec8f_b &operator=( const __m256 &rhs )
    {
        mValue = rhs;
        
        return *this;
    }
    
    inline operator __m256 () const
    {
        return mValue;
    }
    
    inline void LoadBinaryMask( U8 mask )
    {
        //EasyConv conv1;
        //conv1.u = 0xFFFFFFFF;
        
        mValue = _mm256_castsi256_ps( _mm256_setr_epi32(  
                                      -(S32)( ( mask >> 0 ) & 0x1 ),
                                      -(S32) ( ( mask >> 1 ) & 0x1 ),
                                      -(S32) ( ( mask >> 2 ) & 0x1 ),
                                      -(S32) ( ( mask >> 3 ) & 0x1 ),
                                      -(S32) ( ( mask >> 4 ) & 0x1 ),
                                      -(S32) ( ( mask >> 5 ) & 0x1 ),
                                      -(S32) ( ( mask >> 6 ) & 0x1 ),
                                      -(S32) ( ( mask >> 7 ) & 0x1 )  
                                    ) );
    } 
    
    // TODO: MIGHT CAUSE PROBLEMS WITH MANUAL LOADED VALS
    inline U64 StoreMask() const
    {       
        return (U64)_mm256_movemask_ps( mValue );
    }
     
    void StoreAligned( F32 *dest ) const
    {
        _mm256_store_ps( dest, mValue );
    }

    void LoadAligned( const F32 *src ) 
    {
        mValue = _mm256_load_ps( src );
    }
    
    bool IsEmpty() const
    {
        return _mm256_testz_ps( mValue, mValue) == 1;
    }

private:

    __m256 mValue;
};

inline AvxVec8f_b operator&( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_and_ps( lhs, rhs );
}

inline AvxVec8f_b operator|( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_or_ps( lhs, rhs );
}

inline AvxVec8f_b operator^( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_xor_ps( lhs, rhs );
}

inline AvxVec8f_b operator==( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 16 );
}

inline AvxVec8f_b operator!=( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, 28 );
}

inline bool SIMD_Hadd( const AvxVec8f_b &lhs )
{
    return (bool)_mm256_movemask_ps( lhs );
}

#endif