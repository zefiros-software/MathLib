#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/mathf.h"
#include "math/util/memory/alignedAllocator.h"
#include "math/util/memory/stackAlign.h"
#include "math/util/hardware/simdStatus.h"

#include "math/simd/avx.h"
//#include "math/simd/sse41.h"
//#include "math/simd/fpu.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>

const static size_t NUM_RAND_TEST_PERMUTATIONS = 1000;


static SimdStatus hardwareStatus;

template< typename TYPE >
TYPE RandomVal()
{
    return static_cast <TYPE>( rand() ) / static_cast <TYPE>( ( RAND_MAX / 100 ) );
}

template< typename TYPE >
TYPE RandomVal( TYPE maxVal )
{
    return RandomVal< TYPE >() % maxVal;
}


void PrintFeatureSupport( std::string feat, bool issupp )
{
    std::cout  << feat << ( issupp ? " OK " : " - " ) << std::endl;
}

TEST( P( Hardware ), SimdStatus )
{
    std::cout << hardwareStatus.Vendor() << std::endl;

    PrintFeatureSupport( "SSE"   , hardwareStatus.SupportsSSE() );
    PrintFeatureSupport( "SSE2"  , hardwareStatus.SupportsSSE2() );
    PrintFeatureSupport( "SSE3"  , hardwareStatus.SupportsSSE3() );
    PrintFeatureSupport( "SSE4.1", hardwareStatus.SupportsSSE4_1() );
    PrintFeatureSupport( "SSE4.2", hardwareStatus.SupportsSSE4_2() );
    PrintFeatureSupport( "AVX"   , hardwareStatus.SupportsAVX() );
    PrintFeatureSupport( "FMA"   , hardwareStatus.SupportsFMA() );

    std::cout << "SIMD_LEVEL: " << hardwareStatus.SIMDLevel() << std::endl;
}


template< typename SimdTraitsReal >
struct SIMD_TESTS
{
    // SIMD types
    typedef typename SimdTraitsReal::vec_type simd_vec;
    typedef typename SimdTraitsReal::value_type simd_value_type;
    typedef typename SimdTraitsReal::int_type simd_int_type;
    typedef typename SimdTraitsReal::veci_type simd_veci;
    typedef typename SimdTraitsReal::vecb_type simd_bool;
    typedef typename SimdTraitsReal::type_array type_array;
    typedef typename SimdTraitsReal::int_array int_array;
    typedef typename SimdTraitsReal::bool_array bool_array;

    static void TestBoolVecConstructors()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            simd_bool trueVec( true );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_TRUE( SIMD::ExtractValue( trueVec, i ) );
            }

            simd_bool falseVec( false );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_FALSE( SIMD::ExtractValue( falseVec, i ) );
            }

            // Fill an bool array
            bool_array fillArray;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                fillArray.values[i] = RandomVal<U32>( 2 );
            }

            simd_bool fillVec( fillArray );
            simd_bool fillVec2( fillArray.values );
            simd_bool fillVec3( fillVec );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( fillVec[i],  bool( fillArray.values[i] ) );
                ASSERT_EQ( fillVec2[i], bool( fillArray.values[i] ) );
                ASSERT_EQ( fillVec3[i], bool( fillArray.values[i] ) );

            }
        }
    }

    static void TestBoolVecAnyAll()
    {
        bool_array boolArray;

        for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
        {
            boolArray.values[i] = false;
        }

        simd_bool boolVec( boolArray );

        ASSERT_FALSE( boolVec.Any() );
        ASSERT_FALSE( boolVec.All() );

        for ( U32 i = 0; i < ( SimdTraitsReal::width - 1 ); ++i )
        {
            boolArray.values[i] = true;

            boolVec = simd_bool( boolArray );

            ASSERT_TRUE( boolVec.Any() );
            ASSERT_FALSE( boolVec.All() );
        }

        boolArray.values[( SimdTraitsReal::width - 1 ) ] = true;
        boolVec = simd_bool( boolArray );

        ASSERT_TRUE( boolVec.Any() );
        ASSERT_TRUE( boolVec.All() );
    }

    static void TestBoolVecAnd()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult.values[i] = boolArray1.values[i] & boolArray2.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );

            simd_bool boolVecResult = boolVec1 & boolVec2;
            boolVec1 &= boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult[i], boolArrayResult.values[i] );
                ASSERT_EQ( boolVec1[i], boolArrayResult.values[i] );
            }
        }
    }

    static void TestBoolVecOr()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult.values[i] = boolArray1.values[i] | boolArray2.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );

            simd_bool boolVecResult = boolVec1 | boolVec2;
            boolVec1 |= boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult[i], boolArrayResult.values[i] );
                ASSERT_EQ( boolVec1[i], boolArrayResult.values[i] );
            }
        }
    }

    static void TestBoolVecXOr()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult.values[i] = boolArray1.values[i] ^ boolArray2.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );

            simd_bool boolVecResult = boolVec1 ^ boolVec2;
            boolVec1 ^= boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult[i], boolArrayResult.values[i] );
                ASSERT_EQ( boolVec1[i], boolArrayResult.values[i] );
            }
        }
    }

    static void TestBoolVecAndAnd()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult.values[i] = boolArray1.values[i] && boolArray2.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );

            simd_bool boolVecResult = boolVec1 && boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult[i], boolArrayResult.values[i] );
            }
        }
    }

    static void TestBoolVecOrOr()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult.values[i] = boolArray1.values[i] || boolArray2.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );

            simd_bool boolVecResult = boolVec1 || boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult[i], boolArrayResult.values[i] );
            }
        }
    }

    static void TestBoolVecEqNeq()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArrayResult1;
            bool_array boolArrayResult2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult1.values[i] = boolArray1.values[i] == boolArray2.values[i];
                boolArrayResult2.values[i] = boolArray1.values[i] != boolArray2.values[i];
            }

            const simd_bool boolVec1( boolArray1 );
            const simd_bool boolVec2( boolArray2 );

            const simd_bool boolVecResult1 = boolVec1 == boolVec2;
            const simd_bool boolVecResult2 = boolVec1 != boolVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult1[i], boolArrayResult1.values[i] );
                ASSERT_EQ( boolVecResult2[i], boolArrayResult2.values[i] );
            }
        }
    }

    static void TestBoolVecNot()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArrayResult1;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult1.values[i] = !boolArray1.values[i];
            }

            simd_bool boolVec1( boolArray1 );

            simd_bool boolVecResult1 = !boolVec1;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult1[i], boolArrayResult1.values[i] );
            }
        }
    }

    static void TestBoolIfThenElse()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            bool_array boolArray1;
            bool_array boolArray2;
            bool_array boolArray3;
            bool_array boolArrayResult1;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                boolArray1.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray2.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArray3.values[i] = bool( RandomVal<U32>( 2 ) );
                boolArrayResult1.values[i] = boolArray1.values[i] ? boolArray2.values[i] : boolArray3.values[i];
            }

            simd_bool boolVec1( boolArray1 );
            simd_bool boolVec2( boolArray2 );
            simd_bool boolVec3( boolArray3 );

            simd_bool boolVecResult1 = SIMD::IfThenElse( boolVec1, boolVec2, boolVec3 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( boolVecResult1[i], boolArrayResult1.values[i] );
            }
        }
    }

    static void TestIntVecConstruct()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            simd_int_type val = RandomVal< simd_int_type >();

            simd_veci testVec1( val );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( val, testVec1[i] );
            }

            int_array valArray;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                valArray.values[i] = RandomVal< simd_int_type >();
            }

            simd_veci testVec3( valArray.values );
            simd_veci testVec4( testVec3 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( testVec3[i], valArray.values[i] );
                ASSERT_EQ( testVec4[i], valArray.values[i] );
            }

        }
    }


    static void TestTypeVecConstruct()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            simd_value_type val = RandomVal< simd_value_type >();

            simd_vec testVec1 = SIMD::Scatter( val );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( val, testVec1[i] );
            }

            type_array valArray;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                valArray.values[i] = RandomVal< simd_value_type >();
            }

            simd_vec testVec2 = SIMD::Load( valArray.values );
            simd_vec testVec3 = SIMD::Load( valArray.values );
            simd_vec testVec4( testVec2 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( testVec2[i], valArray.values[i] );
                ASSERT_REAL_EQ( testVec3[i], valArray.values[i] );
                ASSERT_REAL_EQ( testVec4[i], valArray.values[i] );
            }

        }
    }

    static void TestTypeVecLoadStore()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array valArray;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                valArray.values[i] = RandomVal< simd_value_type >();
            }

            simd_vec testVec2, testVec3;

            testVec2 = SIMD::Load( valArray.values );
            testVec3 = SIMD::LoadU( valArray.values );

            type_array testArray1, testArray2;
            SIMD::Store( testVec2, testArray1.values );
            SIMD::StoreU( testVec3, testArray2.values );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( testVec2[i], valArray.values[i] );
                ASSERT_REAL_EQ( testVec3[i], valArray.values[i] );
                ASSERT_REAL_EQ( testArray1.values[i], valArray.values[i] );
                ASSERT_REAL_EQ( testArray2.values[i], valArray.values[i] );
            }

        }
    }

    static void TestTypeVecAdd()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArray2.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] + typeArray2.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );

            simd_vec vecResult = tVec1 + tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( vecResult[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecSub()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArray2.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] - typeArray2.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );

            simd_vec vecResult = tVec1 - tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( vecResult[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecMul()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArray2.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] * typeArray2.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );

            simd_vec vecResult = tVec1 * tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( vecResult[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecDiv()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArray2.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] / typeArray2.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );

            simd_vec vecResult = tVec1 / tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( vecResult[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecIncr()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] + 1.0;
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = tVec1++;
            simd_vec tVec3 = ++tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec1[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( tVec3[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecDecr()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = typeArray1.values[i] - 1.0;
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = tVec1--;
            simd_vec tVec3 = --tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec1[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( tVec3[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecSqrt()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] = Mathf::Sqrt( typeArray1.values[i] );
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Sqrt( tVec1 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecRcpSqrt()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] =  Mathf::Rcp( Mathf::Sqrt( typeArray1.values[i] ) );
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::RcpSqrt( tVec1 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecRcp()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] =  Mathf::Rcp( typeArray1.values[i] );
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Rcp( tVec1 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecRint()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] =  Mathf::Rint( typeArray1.values[i] );
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Rint( tVec1 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecSin()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArrayResult.values[i] =  Mathf::Sin( typeArray1.values[i] );
            }

            simd_vec tVec1( typeArray1 );
            simd_vec tVec2 = SIMD::Sin( tVec1 );

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( tVec2[i], typeArrayResult.values[i] );
            }
        }
    }

    static void TestTypeVecSum()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;

            simd_value_type sumRef = 0.0;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();

                sumRef += typeArray1.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_value_type sum = SIMD::Sum( tVec1 );

            ASSERT_REAL_EQ( sum, sumRef );
        }
    }

    static void TestTypeVecConditionals()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;

            bool_array typeArrayResultEq;
            bool_array typeArrayResultNeq;
            bool_array typeArrayResultLt;
            bool_array typeArrayResultLe;
            bool_array typeArrayResultGt;
            bool_array typeArrayResultGe;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>() / ( std::numeric_limits< simd_value_type >::max() / 10.0 );
                typeArray2.values[i] = RandomVal<simd_value_type>() / ( std::numeric_limits< simd_value_type >::max() / 10.0 );


                typeArrayResultEq.values[i]  = typeArray1.values[i] == typeArray2.values[i];
                typeArrayResultNeq.values[i] = typeArray1.values[i] != typeArray2.values[i];
                typeArrayResultLt.values[i]  = typeArray1.values[i] <  typeArray2.values[i];
                typeArrayResultLe.values[i]  = typeArray1.values[i] <= typeArray2.values[i];
                typeArrayResultGt.values[i]  = typeArray1.values[i] >  typeArray2.values[i];
                typeArrayResultGe.values[i]  = typeArray1.values[i] >= typeArray2.values[i];
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );

            simd_bool tVecEq  = tVec1 == tVec2;
            simd_bool tVecNeq = tVec1 != tVec2;
            simd_bool tVecLt  = tVec1 <  tVec2;
            simd_bool tVecLe  = tVec1 <= tVec2;
            simd_bool tVecGt  = tVec1 >  tVec2;
            simd_bool tVecGe  = tVec1 >= tVec2;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_EQ( tVecEq[i],  typeArrayResultEq.values[i] );
                ASSERT_EQ( tVecNeq[i], typeArrayResultNeq.values[i] );
                ASSERT_EQ( tVecLt[i],  typeArrayResultLt.values[i] );
                ASSERT_EQ( tVecLe[i],  typeArrayResultLe.values[i] );
                ASSERT_EQ( tVecGt[i],  typeArrayResultGt.values[i] );
                ASSERT_EQ( tVecGe[i],  typeArrayResultGe.values[i] );
            }
        }
    }

    static void TestTypeVecMasking()
    {
        for ( size_t t = 0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array typeArray1;
            type_array typeArray2;
            type_array typeArray3;

            type_array typeArrayResult;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                typeArray1.values[i] = RandomVal<simd_value_type>();
                typeArray2.values[i] = RandomVal<simd_value_type>();
                typeArray3.values[i] = RandomVal<simd_value_type>();

                typeArrayResult.values[i]  = typeArray1.values[i] < typeArray2.values[i] ? typeArray3.values[i] : 0.0;
            }

            simd_vec tVec1 = SIMD::Load( typeArray1.values );
            simd_vec tVec2 = SIMD::Load( typeArray2.values );
            simd_vec tVec3 = SIMD::Load( typeArray3.values );

            simd_bool compare = tVec1 < tVec2;
            simd_vec vecResult1 = SIMD::IfThenElse( compare, tVec3, SIMD::Scatter( simd_value_type( 0.0 ) ) );
            simd_vec vecResult2 = tVec3 & compare;
            simd_vec vecResult3 = compare & tVec3;

            for ( U32 i = 0; i < SimdTraitsReal::width; ++i )
            {
                ASSERT_REAL_EQ( vecResult1[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( vecResult2[i], typeArrayResult.values[i] );
                ASSERT_REAL_EQ( vecResult3[i], typeArrayResult.values[i] );
            }
        }
    }

    /*
    template< U32 index >
    static void BroadCastRotation( const type_array &compare, const simd_vec &vec  )
    {
        const simd_vec testVec1 = vec.BroadCastIndex< index >();

        ASSERT_REAL_EQ( vec[index], compare.values[index] );

        if ( index != 0 )
        {
            BroadCastRotation< index - 1 >( compare, vec );
        }

    }

    static void TestTypeVecValueBroadcast()
    {
        for ( size_t t=0; t < NUM_RAND_TEST_PERMUTATIONS; ++t )
        {
            type_array valArray;

            for ( U32 i=0; i < SimdTraitsReal::width; ++i )
            {
                valArray.values[i] = RandomVal< simd_value_type >();
            }

            simd_vec vec1( valArray );

            for ( U32 i=0; i < SimdTraitsReal::width; ++i )
            {

            }

        }
    }
    */

};


#define TestPlatforms( function, semantic ) \
    TEST( P( AVX_VecReal_F32 ), semantic ) \
    { \
        srand( 2015 ); \
        if( hardwareStatus.SupportsAVX() ) \
        { \
            SIMD_TESTS< AvxSimdTraits<F32> >:: function (); \
        } \
    } \
    TEST( P( AVX_VecReal_F64 ), semantic ) \
    { \
        srand( 2015 ); \
        if( hardwareStatus.SupportsAVX() ) \
        { \
            SIMD_TESTS< AvxSimdTraits<F64> >:: function (); \
        } \
    }
/*
    TEST( P( SSE41_VecReal ), semantic ) \
    { \
        srand( 2015 ); \
        if( hardwareStatus.SupportsSSE4_1() ) \
        { \
            SIMD_TESTS< SSE4_1SimdTraits<Real> >:: function (); \
        } \
    } \
    TEST( P( FPU_VecReal ), semantic ) \
    { \
        srand( 2015 ); \
        SIMD_TESTS< FpuSimdTraits<Real> >:: function (); \
    } \
*/

/*
TestPlatforms( TestBoolVecConstructors, BoolVecConstructors );
TestPlatforms( TestBoolVecAnyAll, BoolVecAnyAll );
TestPlatforms( TestBoolVecAnd, BoolVecAnd );
TestPlatforms( TestBoolVecOr, BoolVecOr );
TestPlatforms( TestBoolVecXOr, BoolVecXOr );
TestPlatforms( TestBoolVecAndAnd, BoolVecAndAnd );
TestPlatforms( TestBoolVecOrOr, BoolVecOrOr );
TestPlatforms( TestBoolVecEqNeq, BoolVecEqNeq );
TestPlatforms( TestBoolVecNot, BoolVecNot );
TestPlatforms( TestBoolIfThenElse, BoolIfThenElse );
*/

//
// DISABLE FOR NOW
//

TestPlatforms( TestIntVecConstruct, IntVecConstruct );


TestPlatforms( TestTypeVecConstruct, TypeVecConstruct );
TestPlatforms( TestTypeVecLoadStore, TypeVecLoadStore );
//TestPlatforms( TestTypeVecValueBroadcast, TypeVecValueBroadcast );

TestPlatforms( TestTypeVecAdd, TypeVecAdd );
TestPlatforms( TestTypeVecSub, TypeVecSub );
TestPlatforms( TestTypeVecMul, TypeVecMul );
TestPlatforms( TestTypeVecDiv, TypeVecDiv );
//TestPlatforms( TestTypeVecIncr, TypeVecIncr );
//TestPlatforms( TestTypeVecDecr, TypeVecDecr );

TestPlatforms( TestTypeVecConditionals, TypeVecConditionals );
TestPlatforms( TestTypeVecMasking, TypeVecMasking );

TestPlatforms( TestTypeVecSqrt, TypeVecSqrt );
TestPlatforms( TestTypeVecRcpSqrt, TypeVecRcpSqrt );
TestPlatforms( TestTypeVecRcp, TypeVecRcp );
TestPlatforms( TestTypeVecRint, TypeVecRint );
//TestPlatforms( TestTypeVecSin, TypeVecSin );

TestPlatforms( TestTypeVecSum, TypeVecSum );


