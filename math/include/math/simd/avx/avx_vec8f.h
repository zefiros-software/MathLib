#pragma once
#ifndef __AVX2_VEC8f_H__
#define __AVX2_VEC8f_H__

#include "math/types.h"

#include "math/simd/simdMathf.h"
#include "math/simd/simdBaseTraits.h"
#include "math/simd/simdVectorBase.h"
#include "math/simd/simdHelper.h"


#include <immintrin.h>
#include <iostream>
#include <limits>



class AvxVec8f;
class AvxVec8i;
class AvxVec8f_b;

template <>
struct AvxSimdTraits<F32> : public BaseSimdTraits<F32, S32, 8, 32>
{
    
    typedef AvxVec8f vec_type;
    typedef AvxVec8i veci_type;
    typedef AvxVec8f_b vecb_type;
    static const size_t bytesPerValue = 4;
    static const size_t registers = 2;

};

//************************
//
// AVX float 8 bool vector
//
//************************

class AvxVec8f_b 
{
    friend inline AvxVec8f_b operator!( const AvxVec8f_b &lhs );
    friend inline AvxVec8f_b operator&( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator|( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator^( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator==( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator!=( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator&&( AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
    friend inline AvxVec8f_b operator||( AvxVec8f_b &lhs, const AvxVec8f_b &rhs );
public:

    inline AvxVec8f_b();
    inline AvxVec8f_b( bool val );
    inline AvxVec8f_b( const bool *ptr );
    inline AvxVec8f_b( const __m256 &rhs );
    inline AvxVec8f_b( const AvxSimdTraits<F32>::bool_array &array );
    
    inline operator __m256 () const;
    
    inline bool operator []( U32 loc ) const;
    
    //inline void LoadBinaryMask( U8 mask );
    inline U64 StoreMask() const
    {
        return (U64)_mm256_movemask_ps( mValue );
    }
    
    inline void LoadBinaryMask( U64 mask )
    {
        // compare flags containing incrementing bitflags
        static const __m256 compare = _mm256_castsi256_ps( _mm256_set_epi32( 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01  ) );
        
        __m256 temp = _mm256_castsi256_ps( _mm256_set1_epi32( (S32) mask ) );
        
        mValue = _mm256_cmp_ps( _mm256_and_ps( temp, compare ), compare, 16 );
    }

    
    inline bool Any() const;
    inline bool All() const;
    
    inline AvxVec8f_b& operator&= ( const AvxVec8f_b& rhs );
    inline AvxVec8f_b& operator|= ( const AvxVec8f_b& rhs );
    inline AvxVec8f_b& operator^= ( const AvxVec8f_b& rhs );
    
private:
    
    // Used to convert from and to the internal
    // SIMD bool representation of sign bit value
    static bool ConvertToBool( U32 val );
    static U32  ConvertFromBool( bool b );
    
private:
    
    __m256 mValue;
};

inline AvxVec8f_b::AvxVec8f_b()
{}

inline AvxVec8f_b::AvxVec8f_b( bool val ) :
mValue( _mm256_castsi256_ps( _mm256_set1_epi32( ConvertFromBool( val ) ) ) )
{
}

inline AvxVec8f_b::AvxVec8f_b( const bool *ptr ):
mValue( _mm256_castsi256_ps( _mm256_set_epi32(
                     ConvertFromBool( ptr[7] ), ConvertFromBool( ptr[6] ), ConvertFromBool( ptr[5] ), ConvertFromBool( ptr[4] ),
                     ConvertFromBool( ptr[3] ), ConvertFromBool( ptr[2] ), ConvertFromBool( ptr[1] ), ConvertFromBool( ptr[0] ) ) ) )
{
}

inline AvxVec8f_b::AvxVec8f_b( const __m256 &rhs ) :
mValue( rhs )
{
}

inline AvxVec8f_b::AvxVec8f_b( const AvxSimdTraits<F32>::bool_array &array ) :
mValue( _mm256_castsi256_ps( _mm256_set_epi32(
                ConvertFromBool( array.values[7] ), ConvertFromBool( array.values[6] ), ConvertFromBool( array.values[5] ), ConvertFromBool( array.values[4] ),
                ConvertFromBool( array.values[3] ), ConvertFromBool( array.values[2] ), ConvertFromBool( array.values[1] ), ConvertFromBool( array.values[0] ) ) ) )
{
    
}

inline AvxVec8f_b::operator __m256 () const
{
    return mValue;
}

inline bool AvxVec8f_b::operator []( U32 loc ) const
{
    return ConvertToBool( SimdHelper::ExtractValueFromVector<AvxVec8f_b, __m256, U32>( mValue, loc ) );
}

inline bool AvxVec8f_b::All() const
{
    return !(!*this).Any();
}

inline bool AvxVec8f_b::Any() const
{
    return !bool(_mm256_testz_ps( mValue, mValue));
}

inline bool AvxVec8f_b::ConvertToBool( U32 val )
{
    // Check if the sign bit is set
    return S32(val) < S32(0);
}

inline U32  AvxVec8f_b::ConvertFromBool( bool b )
{
    // Set the complete mask and enable the sign bit
    return -U32( b );
}


inline AvxVec8f_b& AvxVec8f_b::operator&= ( const AvxVec8f_b& rhs )
{
    (*this) = (*this) && rhs;
    return (*this);
}

inline AvxVec8f_b& AvxVec8f_b::operator|= ( const AvxVec8f_b& rhs )
{
    (*this) = (*this) || rhs;
    return (*this);
}

inline AvxVec8f_b& AvxVec8f_b::operator^= ( const AvxVec8f_b& rhs )
{
    (*this) = (*this) ^ rhs;
    return (*this);
}

inline AvxVec8f_b operator&&( AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return lhs & rhs;
}

inline AvxVec8f_b operator||( AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return lhs | rhs;
}

inline AvxVec8f_b operator!( const AvxVec8f_b &lhs )
{
    return _mm256_xor_ps(AvxVec8f_b(true), lhs );
}

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
    return !( lhs != rhs );
}

inline AvxVec8f_b operator!=( const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
{
    return _mm256_xor_ps(lhs, rhs);
}

namespace SIMD
{
    inline AvxVec8f_b IfThenElse( const AvxVec8f_b &sel, const AvxVec8f_b &lhs, const AvxVec8f_b &rhs )
    {
        return _mm256_blendv_ps( rhs, lhs, sel );
    }
}





//************************
//
// AVX int vector
//
//************************

class AvxVec8i
{
    
    friend AvxVec8i operator+( const AvxVec8i &lhs, const AvxVec8i &rhs );
    friend AvxVec8i operator-( const AvxVec8i &lhs, const AvxVec8i &rhs );
    
public:
    
    inline AvxVec8i();
    inline AvxVec8i( S32 val );
    inline AvxVec8i( const S32 *ptr );
    inline AvxVec8i( const __m256i &rhs );
    
    inline operator __m256i() const;
    
    inline S32 operator []( U32 loc ) const;
    
    inline AvxVec8f_b AsBool() const;
    inline AvxVec8f_b ConvertToBool() const;
    
    inline AvxVec8f AsFloat() const;
    inline AvxVec8f ConvertToFloat() const;
    
    DEFINE_ASSIGNMENT_BASE_OPERATORS( AvxVec8i, S32 );
    
private:
    
    __m256i mValue;
};

//
// Internal
//

AvxVec8i::AvxVec8i()
{}


inline AvxVec8i::AvxVec8i( S32 val ) : mValue( _mm256_set1_epi32( val ) )
{
}

inline AvxVec8i::AvxVec8i( const S32 *ptr ) :
mValue( _mm256_set_epi32( ptr[7], ptr[6], ptr[5], ptr[4],
                          ptr[3], ptr[2], ptr[1], ptr[0] ) )
{
}

inline AvxVec8i::AvxVec8i( const __m256i &rhs ) : mValue( rhs )
{
    
}


inline AvxVec8i::operator __m256i() const
{
    return mValue;
}

inline S32 AvxVec8i::operator []( U32 loc ) const
{
    return SimdHelper::ExtractValueFromVector<AvxVec8i, __m256i, S32>( mValue, loc );
}

inline AvxVec8i operator+( const AvxVec8i &lhs )
{
    return lhs;
}

inline AvxVec8i operator-( const AvxVec8i &lhs )
{
    return AvxVec8i(0.0) - lhs;
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

inline AvxVec8f_b AvxVec8i::AsBool() const
{
    return _mm256_castsi256_ps(mValue);
}

inline AvxVec8f_b AvxVec8i::ConvertToBool() const
{
    // Result: convert_bool(0)=false, convert_bool(else)=true
//#ifdef __AVX2__
    return *this != AvxVec8i(S32(0));
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

inline AvxVec8i operator+( const AvxVec8i &lhs, const AvxVec8i &rhs )
{
#ifdef __AVX2__
    return _mm256_add_epi32(lhs, rhs);
#else
    __m128i vlo = _mm256_castsi256_si128(lhs);
    __m128i vhi = _mm256_extractf128_si256(lhs, 1);
    __m128i xvlo = _mm256_castsi256_si128(rhs);
    __m128i xvhi = _mm256_extractf128_si256(rhs, 1);
    vlo = _mm_add_epi32(vlo, xvlo);
    vhi = _mm_add_epi32(vhi, xvhi);
    return _mm256_insertf128_si256(_mm256_castsi128_si256(vlo), vhi, 1);
#endif
}

inline AvxVec8i operator-( const AvxVec8i &lhs, const AvxVec8i &rhs )
{
#ifdef __AVX2__
    return _mm256_sub_epi32(lhs, rhs);
#else
    __m128i vlo = _mm256_castsi256_si128(lhs);
    __m128i vhi = _mm256_extractf128_si256(lhs, 1);
    __m128i xvlo = _mm256_castsi256_si128(rhs);
    __m128i xvhi = _mm256_extractf128_si256(rhs, 1);
    vlo = _mm_sub_epi32(vlo, xvlo);
    vhi = _mm_sub_epi32(vhi, xvhi);
    return _mm256_insertf128_si256(_mm256_castsi128_si256(vlo), vhi, 1);
#endif
}

inline AvxVec8i operator^( const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return _mm256_xor_si256(lhs, rhs);
#else
    return _mm256_castps_si256(
        _mm256_xor_ps(_mm256_castsi256_ps(lhs), _mm256_castsi256_ps(rhs)));
#endif
}

inline AvxVec8i operator&(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return _mm256_and_si256(lhs, rhs);
#else
    return _mm256_castps_si256(
                               _mm256_and_ps(_mm256_castsi256_ps(lhs), _mm256_castsi256_ps(rhs)));
#endif
}

inline AvxVec8i operator|(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return _mm256_or_si256(lhs, rhs);
#else
    return _mm256_castps_si256(
                               _mm256_or_ps(_mm256_castsi256_ps(lhs), _mm256_castsi256_ps(rhs)));
#endif
}

inline AvxVec8i operator~( const AvxVec8i &lhs )
{
    return AvxVec8i(~U32(0)) ^ lhs;
}

inline AvxVec8f_b operator==(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return _mm256_castsi256_ps(_mm256_cmpeq_epi32(lhs, rhs));
#else
    return !(lhs != x);
#endif
}

inline AvxVec8f_b operator!=(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return !(lhs == rhs);
#else
    return (lhs ^ rhs).convert_bool();
#endif
}

inline AvxVec8f_b operator<(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
#ifdef __AVX2__
    return _mm256_castsi256_ps(_mm256_cmpgt_epi32(rhs, lhs));
#else
    // return (*this - x).as_bool();
    boolvec_t r;
    for (int i = 0; i < size; ++i) {
        r.set_elt(i, (lhs)[i] < rhs[i]);
    }
    return r;
#endif
}

inline AvxVec8f_b operator<=(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
    return !(lhs > rhs);
}

inline AvxVec8f_b operator>(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
    return rhs < lhs;
}

inline AvxVec8f_b operator>=(const AvxVec8i &lhs, const AvxVec8i &rhs)
{
    return !(lhs < rhs);
}

// } END

//************************
//
// AVX float vector
//
//************************

class AvxVec8f
{
    friend AvxVec8f operator+( const AvxVec8f &lhs, const AvxVec8f &rhs );
    friend AvxVec8f operator-( const AvxVec8f &lhs, const AvxVec8f &rhs );
    friend AvxVec8f operator*( const AvxVec8f &lhs, const AvxVec8f &rhs );
    friend AvxVec8f operator/( const AvxVec8f &lhs, const AvxVec8f &rhs );
    
public:

    inline AvxVec8f();
    inline AvxVec8f( F32 val );
    inline AvxVec8f( const F32 *ptr );
    inline AvxVec8f( const __m256 &rhs );
    inline AvxVec8f( const AvxSimdTraits<F32>::type_array &array );
    
    inline operator __m256() const;

    inline F32 operator []( U32 loc ) const;
    
    inline void LoadUnaligned( const F32 *src );
    inline void LoadAligned( const F32 *src );

    inline void StoreUnaligned( F32 *dest ) const;
    inline void StoreAligned( F32 *dest ) const;
    
    inline AvxVec8i AsInt() const;
    inline AvxVec8i ConvertToInt() const;

    //template< U32 index >
    //inline AvxVec8f BroadCastIndex() const;
     
    inline static AvxVec8f GetZero();
    //inline static AvxVec8f GetFullMask();

    DEFINE_ASSIGNMENT_BASE_OPERATORS( AvxVec8f, F32 );
    DEFINE_ASSIGNMENT_EXT_OPERATORS( AvxVec8f, F32 );
    DEFINE_INC_OPERATORS( AvxVec8f, F32 )
    
    //
    // Non-generic
    //
    
    //inline __m256d CastDoubleLower() const;
    //inline __m256d CastDoubleUpper() const;

private:

    __m256 mValue;
};

//
// Internal
//

inline AvxVec8f::AvxVec8f()
{}


inline AvxVec8f::AvxVec8f( F32 val ) : mValue( _mm256_set1_ps( val ) )
{
}

inline AvxVec8f::AvxVec8f( const F32 *ptr ) :
mValue( _mm256_set_ps( ptr[7], ptr[6], ptr[5], ptr[4],
                       ptr[3], ptr[2], ptr[1], ptr[0] ) )
{
}

inline AvxVec8f::AvxVec8f( const __m256 &rhs ) : mValue( rhs )
{
    
}

inline AvxVec8f::AvxVec8f( const AvxSimdTraits<F32>::type_array &array ) :
    mValue( _mm256_load_ps( array.values ) )
{
    
}

inline AvxVec8f::operator __m256() const
{
    return mValue;
}

inline F32 AvxVec8f::operator []( U32 loc ) const
{
    return SimdHelper::ExtractValueFromVector<AvxVec8f, __m256, F32>( mValue, loc );
}

inline void AvxVec8f::LoadUnaligned( const F32 *src )
{
    mValue =  _mm256_loadu_ps( src );
}

inline void AvxVec8f::LoadAligned( const F32 *src )
{
    mValue = _mm256_load_ps( src );
}

inline void AvxVec8f::StoreUnaligned( F32 *dest ) const
{
    _mm256_storeu_ps( dest, mValue );
}

inline void AvxVec8f::StoreAligned( F32 *dest ) const
{
    _mm256_store_ps( dest, mValue );
}

inline AvxVec8i AvxVec8f::AsInt() const
{
    return _mm256_castps_si256(mValue);
}

inline AvxVec8i AvxVec8f::ConvertToInt() const
{
    return _mm256_cvttps_epi32(mValue);
}

inline AvxVec8f AvxVec8f::GetZero()
{
    return _mm256_setzero_ps();
}

/*
template< U32 index >
inline AvxVec8f AvxVec8f::BroadCastIndex() const
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

inline AvxVec8f AvxVec8f::GetFullMask()
{
    EasyConvert easyc;
    easyc.u = 0xFFFFFFFF;
    return _mm256_set1_ps( easyc.f );
}
*/

//
// Non-generic
//

/*
inline __m256d AvxVec8f::CastDoubleLower() const
{
    //extract lower half
    __m128 temp = _mm256_extractf128_ps( mValue, 0 );
    
    return _mm256_cvtps_pd( temp );
}

inline __m256d AvxVec8f::CastDoubleUpper() const
{
    //extract upper half
    __m128 temp = _mm256_extractf128_ps( mValue, 1 );
    
    return _mm256_cvtps_pd( temp );
}
*/

//
// Math
//

inline AvxVec8f operator+( const AvxVec8f &lhs )
{
    return lhs;
}

inline AvxVec8f operator-( const AvxVec8f &lhs )
{
    return _mm256_sub_ps( AvxVec8f(0.0), lhs );
}

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
    return _mm256_cmp_ps( lhs, rhs, _CMP_EQ_OQ );
}

inline AvxVec8f_b operator!= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, _CMP_NEQ_UQ );
}

inline AvxVec8f_b operator< ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, _CMP_LT_OQ );
}

inline AvxVec8f_b operator<= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, _CMP_LE_OQ );
}

inline AvxVec8f_b operator> ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, _CMP_GT_OQ );
}

inline AvxVec8f_b operator>= ( const AvxVec8f &lhs, const AvxVec8f &rhs )
{
    return _mm256_cmp_ps( lhs, rhs, _CMP_GE_OQ );
}

/*
inline AvxVec8f operator&( const AvxVec8f &lhs, const AvxVec8f &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}
*/

inline AvxVec8f operator&( const AvxVec8f &lhs, const AvxVec8f_b &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}

inline AvxVec8f operator&( const AvxVec8f_b &lhs, const AvxVec8f &rhs ) 
{
    return _mm256_and_ps( lhs, rhs );
}


//DEFINE_COMMON_OPERATORS( AvxVec8f, F32 );

//
// MATHF
//

namespace SIMD
{
    inline AvxVec8f Sqrt( const AvxVec8f &lhs )
    {
        return _mm256_sqrt_ps( lhs );
    }
    
    inline AvxVec8f RcpSqrt( const AvxVec8f &lhs )
    {
        __m256 temp = _mm256_rsqrt_ps( lhs );
        
        // newton rhapson cycle
        __m256 temp2 = _mm256_mul_ps( _mm256_sub_ps( _mm256_set1_ps(3.0f), _mm256_mul_ps(_mm256_mul_ps(temp, temp), lhs) ), temp );
        
        return _mm256_mul_ps( _mm256_set1_ps(0.5f), temp2 );
    }
    
    inline AvxVec8f Rcp( const AvxVec8f &lhs )
    {
        return 1.0 / lhs;
    }

    inline AvxVec8f IfThenElse( const AvxVec8f_b &sel, const AvxVec8f &lhs, const AvxVec8f &rhs )
    {
        return _mm256_blendv_ps( rhs, lhs, sel );
    }
    
    
    // REVIEW !!!!
    inline F32 Sum( const AvxVec8f &lhs )
    {
        const __m128 x128 = _mm_add_ps(_mm256_extractf128_ps(lhs, 1), _mm256_castps256_ps128(lhs));
        const __m128 x64 = _mm_add_ps(x128, _mm_movehl_ps(x128, x128));
        const __m128 x32 = _mm_add_ss(x64, _mm_shuffle_ps(x64, x64, 0x55));
        return _mm_cvtss_f32(x32);
    }
    
    inline AvxVec8f Rint( const AvxVec8f &lhs )
    {
        return _mm256_round_ps( lhs, _MM_FROUND_TO_NEAREST_INT );
    }
    
    inline AvxVec8f Sin( const AvxVec8f &lhs )
    {
        return Mathf::_SGA< AvxSimdTraits<F32> >::SGA_Sin_F32( lhs );
    }
    
    /*
    template< U32 index >
    inline AvxVec8f Mathf::SIMD< AvxSimdTraits<F32> >::SumToIndex( const AvxVec8f &lhs )
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
    */

    inline AvxVec8f MADD( const AvxVec8f &mul1, const AvxVec8f &mul2, const AvxVec8f &add )
    {
        return ( mul1 * mul2 ) + add;
    }
    
    inline AvxVec8f MSUB( const AvxVec8f &mul1, const AvxVec8f &mul2, const AvxVec8f &sub )
    {
        return ( mul1 * mul2 ) - sub;
    }
}
    
//
// Int vec
//

inline AvxVec8f AvxVec8i::AsFloat() const
{
    return _mm256_castsi256_ps(mValue);
}

inline AvxVec8f AvxVec8i::ConvertToFloat() const
{
    return _mm256_cvtepi32_ps(mValue);
}



#endif