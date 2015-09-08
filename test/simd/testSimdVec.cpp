#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"

#include "math/util/memory/alignedAllocator.h"
#include "math/util/memory/stackAlign.h"
#include "math/util/hardware/simdStatus.h"

#include "math/simd/avx.h"
#include "math/simd/sse41.h"
#include "math/simd/fpu.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdlib>

static SimdStatus hardwareStatus;

template< typename TYPE >
Real RandomVal()
{
    return static_cast <TYPE>(rand())/static_cast <TYPE>( (RAND_MAX/100) );
}

void PrintFeatureSupport( std::string feat, bool issupp )
{
    std::cout  << feat << ( issupp ? " OK " : " - " ) << std::endl;
} 

TEST( P( Hardware ), SimdStatus )
{
    std::cout << hardwareStatus.Vendor() << std::endl;
    
    PrintFeatureSupport("SSE"   , hardwareStatus.SupportsSSE() );
    PrintFeatureSupport("SSE2"  , hardwareStatus.SupportsSSE2()  );
    PrintFeatureSupport("SSE3"  , hardwareStatus.SupportsSSE3() );
    PrintFeatureSupport("SSE4.1", hardwareStatus.SupportsSSE4_1() );
    PrintFeatureSupport("SSE4.2", hardwareStatus.SupportsSSE4_2() );
    PrintFeatureSupport("AVX"   , hardwareStatus.SupportsAVX() );
    PrintFeatureSupport("FMA"   , hardwareStatus.SupportsFMA() );
    
     std::cout << "SIMD_LEVEL: " << hardwareStatus.SIMDLevel() << std::endl;
}

template< typename SimdTraitsReal >
struct SIMD_TESTS
{
    // SIMD types
    typedef typename SimdTraitsReal::vec_type simd_vec;
    typedef typename SimdTraitsReal::value_type simd_value_type;
    typedef typename SimdTraitsReal::bool_type simd_bool;
    
    static void TestBroadCast()
    {
        simd_value_type val =  RandomVal< simd_value_type >();
        
        simd_vec testVec1(val);
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( val, tempOut1[i] );      
        }
    }
    
    static void TestLoadUnload()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData );
        testVec2.LoadUnaligned( tempData );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempOut2[ SimdTraitsReal::width ];
        
        testVec1.StoreAligned( tempOut1 );
        testVec2.StoreUnaligned( tempOut2 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData[i], tempOut1[i] );   
            ASSERT_REAL_EQ( tempData[i], tempOut2[i] );   
        }
    }
    
    static void TestOperatorAddInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        testVec1 += testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] + tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorAddValInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        
        testVec1 += toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] + toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorSubInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        testVec1 -= testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] - tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorSubValInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        
        testVec1 -= toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] - toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorMulInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        testVec1 *= testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] * tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorMulValInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        
        testVec1 *= toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] * toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorDivInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        testVec1 /= testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] / tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorDivValInp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        
        testVec1 /= toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] / toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorIncr()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        ++testVec1;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] + simd_value_type( 1 ), tempOut1[i] );   
        }
    }
    
    static void TestOperatorDecr()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        --testVec1;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec1.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] - simd_value_type( 1 ), tempOut1[i] );   
        }
    }
    
    //
    // DEBUG FROM HERE
    //
    
    static void TestOperatorAdd()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_vec testVec3 = testVec1 + testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] + tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorAddVal()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = testVec1 + toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] + toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorSub()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_vec testVec3 = testVec1 - testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] - tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorSubVal()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = testVec1 - toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] - toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorMul()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_vec testVec3 = testVec1 * testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] * tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorMulVal()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = testVec1 * toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] * toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestOperatorDiv()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_vec testVec3 = testVec1 / testVec2;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] / tempData2[i], tempOut1[i] );   
        }
    }
    
    static void TestOperatorDivVal()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_value_type toAddVal = RandomVal< simd_value_type >();
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = testVec1 / toAddVal;
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] / toAddVal, tempOut1[i] );   
        }
    }
    
    static void TestRoundToNearest()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = testVec1.RoundToNearest();
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( (simd_value_type)((S64)(tempData1[i] + 0.5 )), tempOut1[i] );   
        }
    }
    
    static void TestSqrt()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = SIMD_Sqrt( testVec1 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( Mathf::Sqrt(tempData1[i]), tempOut1[i] );   
        }
    }
    
    static void TestRcp()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        simd_vec testVec3 = SIMD_Rcp( testVec1 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( Mathf::Rcp(tempData1[i]), tempOut1[i] );   
        }
    }
    
    static void TestRotateOne()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        for ( size_t rotation = 0; rotation < SimdTraitsReal::width; ++rotation )
        {
            Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
            testVec1.StoreAligned( tempOut1 );
            
            const U32 registerOffset = SimdTraitsReal::width / SimdTraitsReal::registers;
            U32 shift = rotation / registerOffset;
            
            for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
            {
                 // as we do not rotate the vdw indices we need to calculate their true indices after rotation
                 U32 offset = it / registerOffset;
    
                 // ( it + rotation ): rolling offset with rotation to accomodate the full matrix mul.
                 // & ( registerOffset - 1 ): rotation is only in width of one register ( AVX has 2x 128 bit ); cheap version of  % registerOffset
                 // ( shift ^ offset ) provides and easy means to shift both register one and register two at the correct time            
                 U32 rotatedIndex = ( ( it + rotation ) & ( registerOffset - 1 ) ) + ( ( shift ^ offset ) * registerOffset );
           
                 ASSERT_REAL_EQ( tempData1[rotatedIndex], tempOut1[it] ); 
            }
            
            bool permute128 = false;
            
            switch( SimdTraitsReal::width )
            {
                case 4:
                    permute128 = ( rotation == 1 || rotation == 3 );
                    break;
                case 8:
                    permute128 = ( rotation == 3 || rotation == 7 );
                    break;
            };
            
            testVec1.RotateOne( permute128 );
        }
    }
    
    static void TestOperatorEqSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 20.2;
        tempData2[0] = 20.2;
        for ( U32 i=1; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 == testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] == tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestOperatorNeqSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 20.2;
        tempData2[0] = 20.2;
        for ( U32 i=1; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 != testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] != tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestOperatorLtSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 18.2;
        tempData2[0] = 20.2;
        for ( U32 i=1; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 < testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] < tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestOperatorLeSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 20.2;
        tempData2[0] = 20.2;
        tempData1[1] = 18.2;
        tempData2[1] = 20.2;
        for ( U32 i=2; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 <= testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] <= tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestOperatorGtSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 20.2;
        tempData2[0] = 20.2;
        tempData1[1] = 22.2;
        tempData2[1] = 20.2;
        for ( U32 i=2; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 > testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] > tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestOperatorGeSelect()
    {
        simd_vec simd_true( 1.0 );
        simd_vec simd_false( 0.0 );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 20.2;
        tempData2[0] = 20.2;
        tempData1[1] = 22.2;
        tempData2[1] = 20.2;
        
        for ( U32 i=2; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        } 
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 >= testVec2;
        
        simd_vec testVec3 = SIMD_Select( comp, simd_true, simd_false );
        
        Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
        testVec3.StoreAligned( tempOut1 );
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            ASSERT_REAL_EQ( tempData1[i] >= tempData2[i] ? 1.0 : 0.0, tempOut1[i] );   
        }
    }
    
    static void TestMaskLoad()
    {
        U64 flags = 0;
        
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            flags |= (U64)1 << ( ( i * SimdTraitsReal::width ) + i );
        }
        
        std::cout << "MASK: " << std::endl;
        for ( U32 i=0; i < SimdTraitsReal::width; ++i )
        {
            for ( U32 j=0; j < SimdTraitsReal::width; ++j )
            {
                std::cout << "\t " << ( ( flags >> ( ( i * SimdTraitsReal::width ) + j )  ) & 0x01 );
            }
            
            std::cout << std::endl;
        }
        
        std::cout << "Result: " << std::endl;
        for ( size_t rotation = 0; rotation < SimdTraitsReal::width; ++rotation )
        {
            simd_bool mask;
            mask.LoadMask( rotation, flags );
            
            simd_vec simd_true( 1.0 );
            simd_vec simd_false( 0.0 );
            
            simd_vec testVec3 = SIMD_Select( mask, simd_true, simd_false );
        
            Real StackAlign( SimdTraitsReal::alignment ) tempOut1[ SimdTraitsReal::width ];
            testVec3.StoreAligned( tempOut1 );
            
    	    const U32 registerOffset = SimdTraitsReal::width / SimdTraitsReal::registers;
            U32 shift = rotation / registerOffset;      
            
            Real StackAlign( SimdTraitsReal::alignment ) ddd[ SimdTraitsReal::width ];
            mask.StoreAligned( ddd );
            
            std::cout << "M: ";
            for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
            {
            
                std::cout << "\t " << ddd[it];
            }
            std::cout << std::endl;
            
            std::cout << "R: ";
            for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
            {
                 // as we do not rotate the vdw indices we need to calculate their true indices after rotation
                 U32 offset = it / registerOffset;
    
                 // ( it + rotation ): rolling offset with rotation to accomodate the full matrix mul.
                 // & ( registerOffset - 1 ): rotation is only in width of one register ( AVX has 2x 128 bit ); cheap version of  % registerOffset
                 // ( shift ^ offset ) provides and easy means to shift both register one and register two at the correct time            
                 U32 rotatedIndex = ( ( it + rotation ) & ( registerOffset - 1 ) ) + ( ( shift ^ offset ) * registerOffset );

                std::cout << "\t " << tempOut1[it];
                
                if ( rotation == 0 )
                ASSERT_REAL_EQ( 1.0, tempOut1[it] );   
                else
                ASSERT_REAL_EQ( 0.0, tempOut1[it] );   
            }
            
            std::cout << std::endl;
        }
    }
    
    static void TestMaskStore()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        Real StackAlign( SimdTraitsReal::alignment ) tempData2[ SimdTraitsReal::width ];
        
        tempData1[0] = 18.2;
        tempData2[0] = 20.2;
        for ( U32 i=1; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
            tempData2[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1, testVec2;
        testVec1.LoadAligned( tempData1 );
        testVec2.LoadAligned( tempData2 );
        
        simd_bool comp = testVec1 < testVec2;
        
        U64 mask = comp.StoreMask();
        
        std::cout << "MASK: " << mask << std::endl;
        
        for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
        {  
            std::cout << tempData1[it] << " " << tempData2[it] << " " << ( tempData1[it] < tempData2[it] ? 1 : 0 ) << " " << ( (mask >> it) & 0x01 ) << std::endl;
        }
        
        for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
        {
            ASSERT_REAL_EQ( tempData1[it] < tempData2[it] ? 1 : 0, (mask >> it) & 0x01 );       
            
        }
        
    }
    
    static void TestHadd()
    {
        Real StackAlign( SimdTraitsReal::alignment ) tempData1[ SimdTraitsReal::width ];
        
        for ( U32 i=1; i < SimdTraitsReal::width; ++i )
        {
            tempData1[i] = RandomVal< simd_value_type >();
        }
        
        simd_vec testVec1;
        testVec1.LoadAligned( tempData1 );
        
        Real comb = SIMD_Hadd( testVec1 );
        
        Real cadd = 0.0;
        
        for ( size_t it = 0, itend = SimdTraitsReal::width; it < itend; ++it )
        {
            cadd += tempData1[it];
        }
        
        ASSERT_REAL_EQ( comb, cadd );
    }
   
};

#define TestPlatforms( function, semantic ) \
    TEST( P( AVX_VecReal ), semantic ) \
    { \
        srand( 2015 ); \
        if( hardwareStatus.SupportsAVX() ) \
        { \
            SIMD_TESTS< AvxSimdTraits<Real> >:: function (); \
        } \
    } \
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


TestPlatforms( TestBroadCast, BroadCast );

TestPlatforms( TestLoadUnload, LoadUnload );

TestPlatforms( TestOperatorAddInp,    OperatorAddInp );
TestPlatforms( TestOperatorAddValInp, OperatorAddValInp );

TestPlatforms( TestOperatorSubInp,    OperatorSubInp );
TestPlatforms( TestOperatorSubValInp, OperatorSubValInp );

TestPlatforms( TestOperatorMulInp,    OperatorMulInp );
TestPlatforms( TestOperatorMulValInp, OperatorMulValInp );

TestPlatforms( TestOperatorDivInp,    OperatorDivInp );
TestPlatforms( TestOperatorDivValInp, OperatorDivValInp );

TestPlatforms( TestOperatorIncr,      OperatorIncr );
TestPlatforms( TestOperatorDecr,      OperatorDescr );

TestPlatforms( TestOperatorAdd,    OperatorAdd );
TestPlatforms( TestOperatorAddVal, OperatorAddVal );

TestPlatforms( TestOperatorSub,    OperatorSub );
TestPlatforms( TestOperatorSubVal, OperatorSubVal );

TestPlatforms( TestOperatorMul,    OperatorMul );
TestPlatforms( TestOperatorMulVal, OperatorMulVal );

TestPlatforms( TestOperatorDiv,    OperatorDiv );
TestPlatforms( TestOperatorDivVal, OperatorDivVal );

TestPlatforms( TestRoundToNearest, RoundToNearest );
TestPlatforms( TestSqrt, Sqrt );
TestPlatforms( TestRcp, Rcp );

TestPlatforms( TestRotateOne, RotateOne );
TestPlatforms( TestMaskLoad, MaskLoad );
TestPlatforms( TestMaskStore, MaskStore );


TestPlatforms( TestOperatorEqSelect, OperatorEqSelect );
TestPlatforms( TestOperatorNeqSelect, OperatorNeqSelect );
TestPlatforms( TestOperatorGtSelect, OperatorGtSelect );
TestPlatforms( TestOperatorGeSelect, OperatorGeSelect );
TestPlatforms( TestOperatorLtSelect, OperatorLtSelect );
TestPlatforms( TestOperatorLeSelect, OperatorLeSelect );

TestPlatforms( TestHadd, Hadd );
