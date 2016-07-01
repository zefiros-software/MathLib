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

class AvxVec4d;
class AvxVec4i;
class AvxVec4d_b;

template <>
struct AvxSimdTraits<F64>  : public BaseSimdTraits<F64, S64, 4, 32>
{  
    typedef AvxVec4d vec_type;
    typedef AvxVec4i veci_type;
    typedef AvxVec4d_b vecb_type;
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
    friend inline AvxVec4d_b operator&&( AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator||( AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator!( const AvxVec4d_b &lhs );
    friend inline AvxVec4d_b operator&( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator|( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator^( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator==( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    friend inline AvxVec4d_b operator!=( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs );
    
public:
    
    inline AvxVec4d_b();
    inline AvxVec4d_b( bool val );
    inline AvxVec4d_b( const bool *ptr );
    inline AvxVec4d_b( const __m256d &rhs );
    inline AvxVec4d_b( const AvxSimdTraits<F64>::bool_array &array );
    
    inline operator __m256d () const;
    
    inline bool operator []( U32 loc ) const;
    
    // TODO: MIGHT CAUSE PROBLEMS WITH MANUAL LOADED VALS
    /*
    inline U64 StoreMask() const;
    inline void LoadBinaryMask( U8 mask );
    */
    
    inline U64 StoreMask() const
    {
        return (U64)_mm256_movemask_pd( mValue );
    }
    
    inline void LoadBinaryMask( U64 mask )
    {
        mValue = _mm256_castsi256_pd( _mm256_setr_epi64x(
                                                         -(S64) ( ( mask >> 0 ) & 0x1 ),
                                                         -(S64) ( ( mask >> 1 ) & 0x1 ),
                                                         -(S64) ( ( mask >> 2 ) & 0x1 ),
                                                         -(S64) ( ( mask >> 3 ) & 0x1 )
                                                         ) );
    } 


    
    inline bool Any() const;
    inline bool All() const;
    
    inline AvxVec4d_b& operator&= ( const AvxVec4d_b& rhs );
    inline AvxVec4d_b& operator|= ( const AvxVec4d_b& rhs );
    inline AvxVec4d_b& operator^= ( const AvxVec4d_b& rhs );
    
private:
    
    // Used to convert from and to the internal
    // SIMD bool representation of sign bit value
    static inline  bool ConvertToBool( U64 val );
    static inline  U64  ConvertFromBool( bool b );
    
private:
    
    __m256d mValue;
};

AvxVec4d_b::AvxVec4d_b()
{}

inline AvxVec4d_b::AvxVec4d_b( bool val ) :
mValue( _mm256_castsi256_pd( _mm256_set1_epi64x( ConvertFromBool( val ) ) ) )
{
}

inline AvxVec4d_b::AvxVec4d_b( const bool *ptr ) :
mValue( _mm256_castsi256_pd( _mm256_set_epi64x(
                        ConvertFromBool( ptr[3] ), ConvertFromBool( ptr[2] ),
                        ConvertFromBool( ptr[1] ), ConvertFromBool( ptr[0] ) ) ) )
{
}


inline AvxVec4d_b::AvxVec4d_b( const __m256d &rhs ) :
mValue( rhs )
{
}

inline AvxVec4d_b::AvxVec4d_b( const AvxSimdTraits<F64>::bool_array &array ) :
mValue( _mm256_castsi256_pd( _mm256_set_epi64x(
                                ConvertFromBool( array.values[3] ), ConvertFromBool( array.values[2] ),
                                ConvertFromBool( array.values[1] ), ConvertFromBool( array.values[0] ) ) ) )
{
    
}

inline bool AvxVec4d_b::operator []( U32 loc ) const
{
    return ConvertToBool( SimdHelper::ExtractValueFromVector<AvxVec4d_b, __m256d, U64>( mValue, loc ) );
}

bool AvxVec4d_b::Any() const
{
    return !bool( _mm256_testz_si256( _mm256_castpd_si256(mValue), _mm256_castpd_si256(mValue) ) );
}

inline bool AvxVec4d_b::All() const
{
    return !(!*this).Any();
}

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

inline AvxVec4d_b::operator __m256d () const
{
    return mValue;
}

// TODO: MIGHT CAUSE PROBLEMS WITH MANUAL LOADED VALS
/*
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
*/

inline AvxVec4d_b& AvxVec4d_b::operator&= ( const AvxVec4d_b& rhs )
{
    (*this) = (*this) && rhs;
    return (*this);
}

inline AvxVec4d_b& AvxVec4d_b::operator|= ( const AvxVec4d_b& rhs )
{
    (*this) = (*this) || rhs;
    return (*this);
}

inline AvxVec4d_b& AvxVec4d_b::operator^= ( const AvxVec4d_b& rhs )
{
    (*this) = (*this) ^ rhs;
    return (*this);
}

inline AvxVec4d_b operator&&( AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return lhs & rhs;
}

inline AvxVec4d_b operator||( AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return lhs | rhs;
}

inline AvxVec4d_b operator!( const AvxVec4d_b &lhs )
{
    return _mm256_xor_pd(AvxVec4d_b(true), lhs );
}


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
    return !( lhs != rhs );
}

inline AvxVec4d_b operator!=( const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_xor_pd(lhs, rhs);
}

template<>
inline AvxVec4d_b Mathf::SIMD< AvxSimdTraits<F64> >::IfThenElse( const AvxVec4d_b &sel, const AvxVec4d_b &lhs, const AvxVec4d_b &rhs )
{
    return _mm256_blendv_ps( rhs, lhs, sel );
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
    friend AvxVec4d operator+( const AvxVec4d &lhs, const AvxVec4d &rhs );
    friend AvxVec4d operator-( const AvxVec4d &lhs, const AvxVec4d &rhs );
    friend AvxVec4d operator*( const AvxVec4d &lhs, const AvxVec4d &rhs );
    friend AvxVec4d operator/( const AvxVec4d &lhs, const AvxVec4d &rhs );
    
public:

    inline AvxVec4d();
    inline AvxVec4d( F64 val );
    inline AvxVec4d( const F64 *src );
    inline AvxVec4d( F64 v0, F64 v1, F64 v2, F64 v3 );
    inline AvxVec4d( const __m256d &rhs );
    inline AvxVec4d( const AvxSimdTraits<F64>::type_array &array );

    inline operator __m256d() const;

    inline F64 operator []( U32 loc ) const;
    
    inline void LoadUnaligned( const F64 *src );
    inline void LoadAligned( const F64 *src );
    inline void StoreUnaligned( F64 *dest ) const;
    inline void StoreAligned( F64 *dest ) const;
    
    AvxVec4i AsInt() const;
    AvxVec4i ConvertToInt() const;
    
    /*
    template< U32 index >
    inline AvxVec4d BroadCastIndex() const;
    */
     
    //inline static AvxVec4d GetZero();
    //inline static AvxVec4d GetFullMask();
    
    DEFINE_ASSIGNMENT_BASE_OPERATORS( AvxVec4d, F64 );
    DEFINE_ASSIGNMENT_EXT_OPERATORS( AvxVec4d, F64 );
    DEFINE_INC_OPERATORS( AvxVec4d, F64 )

private:

    __m256d mValue;
};


//
// Internal
//

inline AvxVec4d::AvxVec4d()
{}

inline AvxVec4d::AvxVec4d( const F64 *src ) :
    mValue( _mm256_setr_pd( src[0], src[1], src[2], src[3] ) )
{
}

inline AvxVec4d::AvxVec4d( F64 val ) : mValue( _mm256_set1_pd( val ) )
{
}


inline AvxVec4d::AvxVec4d( F64 v0, F64 v1, F64 v2, F64 v3 ) :
mValue( _mm256_setr_pd( v0, v1, v2, v3 ) )
{
}

inline AvxVec4d::AvxVec4d( const __m256d &rhs ) : mValue( rhs )
{
    
}

inline AvxVec4d::AvxVec4d( const AvxSimdTraits<F64>::type_array &array ) :
    mValue( _mm256_load_pd( array.values ) )
{
    
}

inline AvxVec4d::operator __m256d() const
{
    return mValue;
}

inline F64 AvxVec4d::operator []( U32 loc ) const
{
    return SimdHelper::ExtractValueFromVector<AvxVec4d, __m256d, F64>( mValue, loc );
}

inline void AvxVec4d::LoadUnaligned( const F64 *src )
{
    mValue =  _mm256_loadu_pd( src );
}

inline void AvxVec4d::LoadAligned( const F64 *src )
{
    mValue = _mm256_load_pd( src );
}

inline void AvxVec4d::StoreUnaligned( F64 *dest ) const
{
    _mm256_storeu_pd( dest, mValue );
}

inline void AvxVec4d::StoreAligned( F64 *dest ) const
{
    _mm256_store_pd( dest, mValue );
}

inline AvxVec4i AvxVec4d::AsInt() const
{
    return _mm256_castpd_si256(mValue);
}

inline AvxVec4i AvxVec4d::ConvertToInt() const
{
    AvxVec4i r;
    
    for (U32 i = 0; i < 4; ++i)
    {
        SimdHelper::SetValueInVector<AvxVec4i, __m256i, S64>( r, i, S64((*this)[i]) );
    }
    
    return r;
}

/*
template< U32 index >
inline AvxVec4d AvxVec4d::BroadCastIndex() const
{
    __m256d temp;
    
    if ( index >= 2 )
    {
        
        temp = _mm256_permute2f128_pd( mValue, mValue, 1 | ( 1 << 4 ) );
    }
    else
    {
        temp = _mm256_permute2f128_pd( mValue, mValue, 0 );
    }
    
    const S32 selector = index % 2;
    const S32 select = ( selector ) | ( selector << 1 ) | ( selector << 2 ) | ( selector << 3 );
    
    return _mm256_shuffle_pd( temp, temp, select );
}
*/

/*

inline AvxVec4d AvxVec4d::GetZero()
{
    return _mm256_setzero_pd();
}

inline AvxVec4d AvxVec4d::GetFullMask()
{
    EasyConvert easyc;
    easyc.ul = 0xFFFFFFFFFFFFFFFF;
    return _mm256_set1_pd( easyc.d );
}
*/
 
//
// Math
//

inline AvxVec4d operator+( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_add_pd( lhs, rhs );
}

inline AvxVec4d operator-( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_sub_pd( lhs, rhs );
}

inline AvxVec4d operator*( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_mul_pd( lhs, rhs );
}

inline AvxVec4d operator/( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_div_pd( lhs, rhs );
}

//
// Comparison
//

inline AvxVec4d_b operator== ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 0 );
}

inline AvxVec4d_b operator!= ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 12 );
}

inline AvxVec4d_b operator< ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 17 );
}

inline AvxVec4d_b operator<= ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 18 );
}

inline AvxVec4d_b operator> ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 30 );
}

inline AvxVec4d_b operator>= ( const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_cmp_pd( lhs, rhs, 29 );
}

/*
inline AvxVec4d operator&( const AvxVec4d &lhs, const AvxVec4d &rhs ) 
{
    return _mm256_and_pd( lhs, rhs );
}
*/

inline AvxVec4d operator&( const AvxVec4d &lhs, const AvxVec4d_b &rhs ) 
{
    return _mm256_and_pd( lhs, rhs );
}

inline AvxVec4d operator&( const AvxVec4d_b &lhs, const AvxVec4d &rhs ) 
{
    return _mm256_and_pd( lhs, rhs );
}

//DEFINE_COMMON_OPERATORS( AvxVec4d, F64 );

//
// Special
//

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::Sqrt( const AvxVec4d &lhs )
{
    return _mm256_sqrt_pd( lhs );
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::Rcp( const AvxVec4d &lhs )
{
    return ( 1.0 / lhs ); 
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::RcpSqrt( const AvxVec4d &lhs )
{
    return Rcp( Sqrt( lhs ) );
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::IfThenElse( const AvxVec4d_b &sel, const AvxVec4d &lhs, const AvxVec4d &rhs )
{
    return _mm256_blendv_pd( rhs, lhs, sel );
}

template<>
inline F64 Mathf::SIMD< AvxSimdTraits<F64> >::Sum( const AvxVec4d &lhs )
{
    const __m128d x128 = _mm_add_pd(_mm256_extractf128_pd(lhs, 1), _mm256_castpd256_pd128(lhs));
    const __m128d x64 = _mm_add_sd( x128, _mm_shuffle_pd(x128, x128, 0x3 ) );
    return _mm_cvtsd_f64(x64);
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::Rint( const AvxVec4d &lhs )
{
    return _mm256_round_pd( lhs, _MM_FROUND_TO_NEAREST_INT );
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::Sin( const AvxVec4d &lhs )
{
    return Mathf::_SGA< AvxSimdTraits<F64> >::SGA_Sin_F64( lhs );
}


/*
template<>
template< U32 index >
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::HaddToIndex( const AvxVec4d &lhs )
{
    const __m128d x128 = _mm_add_pd(_mm256_extractf128_pd(lhs, 1), _mm256_castpd256_pd128(lhs));
    const __m128d x64 = _mm_add_pd( _mm_shuffle_pd(x128, x128, 0 ), _mm_shuffle_pd(x128, x128, 0x3 ) );

    // Two cases, either target is hi register or target is low register
    __m256d zero = _mm256_setzero_pd();
        
    const U32 controll = 1 << ( index % 2 );
    __m256d result = _mm256_blend_pd( zero, _mm256_castpd128_pd256(x64), controll );
    
    if ( index >= 2 )
    {
        //switch halves
        result = _mm256_permute2f128_pd( result, result, 1 );
    }
    
    return result;
}
*/
 
template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::MAD( const AvxVec4d &mul1, const AvxVec4d &mul2, const AvxVec4d &add )
{
    return ( mul1 * mul2 ) + add;
}

template<>
inline AvxVec4d Mathf::SIMD< AvxSimdTraits<F64> >::MSUB( const AvxVec4d &mul1, const AvxVec4d &mul2, const AvxVec4d &sub )
{
    return ( mul1 * mul2 ) - sub;
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