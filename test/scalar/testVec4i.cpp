#include "gtest/gtest.h"

#include "helper.h"

#include "math/types.h"
#include "math/scalar/vec4.h"
#include "math/scalar/vec2i.h"
#include "math/scalar/vec3i.h"
#include "math/scalar/vec4i.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

TEST(P(Vec4iTest), ConstructAndAccess)
{
    Vec4i testConst;
    Vec4i testConst1(10);
    Vec4i testConst2(10, 20, 30, 40);

    ASSERT_EQ(testConst1[0], 10);
    ASSERT_EQ(testConst1[1], 10);
    ASSERT_EQ(testConst1[2], 10);
    ASSERT_EQ(testConst1[3], 10);

    ASSERT_EQ(testConst2[0], 10);
    ASSERT_EQ(testConst2[1], 20);
    ASSERT_EQ(testConst2[2], 30);
    ASSERT_EQ(testConst2[3], 40);
    
    Vec2i testConst3( 10, 20 );
    Vec2i testConst4( 30, 40 );
    
    Vec4i testConst5( testConst3, testConst4 );
    
    ASSERT_EQ(testConst5[0], 10);
    ASSERT_EQ(testConst5[1], 20);
    ASSERT_EQ(testConst5[2], 30);
    ASSERT_EQ(testConst5[3], 40);
    
    Vec3i testConst6( 10, 20, 30 );
    
    Vec4i testConst7( testConst6, 40 );
    
    ASSERT_EQ(testConst7[0], 10);
    ASSERT_EQ(testConst7[1], 20);
    ASSERT_EQ(testConst7[2], 30);
    ASSERT_EQ(testConst7[3], 40);
    
    Vec4i testConst8( 40, testConst6 );
    
    ASSERT_EQ(testConst8[0], 40);
    ASSERT_EQ(testConst8[1], 10);
    ASSERT_EQ(testConst8[2], 20);
    ASSERT_EQ(testConst8[3], 30);
}

TEST(P(Vec4iTest), RealCast)
{
    Vec4i  testConst(10, 20, 30, 40);
    Vec4   testCast(testConst);

    ASSERT_REAL_EQ(testCast[0], 10.0);
    ASSERT_REAL_EQ(testCast[1], 20.0);
    ASSERT_REAL_EQ(testCast[2], 30.0);
    ASSERT_REAL_EQ(testCast[3], 40.0);
}


TEST(P(Vec4iTest), Width)
{
    U32 l = Vec4i::Width();
    
    ASSERT_EQ(l, 4u);
}

TEST(P(Vec4iTest), OperatorAddInp)
{
    Vec4i testConst1( 10 );
    Vec4i testConst2( 1, 2, 3, 4 );
    
    testConst1 += testConst2;
    
    ASSERT_EQ(testConst1[0], 11);
    ASSERT_EQ(testConst1[1], 12);
    ASSERT_EQ(testConst1[2], 13);
    ASSERT_EQ(testConst1[3], 14);
}

TEST(P(Vec4iTest), OperatorSubInp)
{
    Vec4i testConst1( 10 );
    Vec4i testConst2( 1, 2, 3, 4 );
    
    testConst1 -= testConst2;
    
    ASSERT_EQ(testConst1[0], 9);
    ASSERT_EQ(testConst1[1], 8);
    ASSERT_EQ(testConst1[2], 7);
    ASSERT_EQ(testConst1[3], 6);
}


TEST(P(Vec4iTest), OperatorDivInp)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    
    testConst1 /= 5;
    
    ASSERT_EQ(testConst1[0], 2);
    ASSERT_EQ(testConst1[1], 4);
    ASSERT_EQ(testConst1[2], 6);
    ASSERT_EQ(testConst1[3], 8);
}

TEST(P(Vec4iTest), OperatorMulInp)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    
    testConst1 *= 10;
    
    ASSERT_EQ(testConst1[0], 100);
    ASSERT_EQ(testConst1[1], 200);
    ASSERT_EQ(testConst1[2], 300);
    ASSERT_EQ(testConst1[3], 400);
}

TEST(P(Vec4iTest), OperatorEq)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 20, 30, 40 );
    Vec4i testConst3( 10, 20, 20, 40 );
    Vec4i testConst4( 10, 20, 30, 20 );
    Vec4i testConst5( 20 );
    
    
    ASSERT_TRUE( testConst1 == testConst1 );
    ASSERT_FALSE( testConst1 == testConst2 );
    ASSERT_FALSE( testConst1 == testConst3 );
    ASSERT_FALSE( testConst1 == testConst4 );
    ASSERT_FALSE( testConst1 == testConst5 );
}

TEST(P(Vec4iTest), OperatorNeq)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 20, 30, 40 );
    Vec4i testConst3( 10, 20, 20, 40 );
    Vec4i testConst4( 10, 20, 30, 20 );
    Vec4i testConst5( 20 );
    
    ASSERT_FALSE( testConst1 != testConst1 );
    ASSERT_TRUE( testConst1 != testConst2 );
    ASSERT_TRUE( testConst1 != testConst3 );
    ASSERT_TRUE( testConst1 != testConst4 );
    ASSERT_TRUE( testConst1 != testConst5 );
}

TEST(P(Vec4iTest), Dot)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 40, 80, 160 );
    ASSERT_EQ( testConst1.Dot( testConst2 ), 10*20 + 20*40 + 30*80 + 40*160 );
}

TEST(P(Vec4iTest), Length2)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    ASSERT_EQ( testConst1.Length2(), 10*10 + 20*20 + 30*30 + 40*40 );
}

TEST(P(Vec4iTest), Distance2)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 40, 80, 160 );
    ASSERT_EQ( testConst1.Distance2(testConst2), Mathf::Square( 10 - 20 ) + 
                                                 Mathf::Square( 20 - 40 ) + 
                                                 Mathf::Square( 30 - 80 ) + 
                                                 Mathf::Square( 40 - 160 ) );
}

TEST(P(Vec4iTest), Abs)
{
    Vec4i testConst1( -10, -20, -30, -40 );
    Vec4i testConst2 = testConst1.Absolute();
    
    ASSERT_EQ(testConst2[0], 10);
    ASSERT_EQ(testConst2[1], 20);
    ASSERT_EQ(testConst2[2], 30);
    ASSERT_EQ(testConst2[3], 40);
}

TEST(P(Vec4iTest), MinAxis)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( -10, -20, -30, -40 );
    
    ASSERT_EQ(testConst1.MinAxis(), 0);
    ASSERT_EQ(testConst2.MinAxis(), 3);
}

TEST(P(Vec4iTest), MaxAxis)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( -10, -20, -30, -40 );
    
    ASSERT_EQ(testConst1.MaxAxis(), 3);
    ASSERT_EQ(testConst2.MaxAxis(), 0);
}

TEST(P(Vec4iTest), SetZero)
{
    Vec4i testConst1( 10, 20, 30, 40 );
    testConst1.SetZero();
    
    ASSERT_EQ(testConst1[0], 0);
    ASSERT_EQ(testConst1[1], 0);
    ASSERT_EQ(testConst1[2], 0);
    ASSERT_EQ(testConst1[3], 0);
}

TEST(P(Vec4iTest), FuzzyZero)
{
    Vec4i testConst1( 0, 0, 0, 0 );
    Vec4i testConst2( 1, 1, 1, 1);
    
    ASSERT_TRUE(  testConst1.IsFuzzyZero() );
    ASSERT_FALSE( testConst2.IsFuzzyZero() );
    
}

TEST(P(Vec4iTest), Clear )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    testConst1.Clear();
    
    ASSERT_EQ(testConst1[0], 0);
    ASSERT_EQ(testConst1[1], 0);
    ASSERT_EQ(testConst1[2], 0);
    ASSERT_EQ(testConst1[3], 0);
}

TEST(P(Vec4iTest), OperatorAdd )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 40, 80, 160 );
    
     Vec4i testConst3 = testConst1 + testConst2;
    
    ASSERT_EQ(testConst3[0], 30 );
    ASSERT_EQ(testConst3[1], 60 );
    ASSERT_EQ(testConst3[2], 110 );
    ASSERT_EQ(testConst3[3], 200 );
}

TEST(P(Vec4iTest), OperatorSub )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 40, 80, 160 );
    
     Vec4i testConst3 = testConst1 - testConst2;
    
    ASSERT_EQ(testConst3[0], -10 );
    ASSERT_EQ(testConst3[1], -20 );
    ASSERT_EQ(testConst3[2], -50 );
    ASSERT_EQ(testConst3[3], -120 );
}

TEST(P(Vec4iTest), OperatorNeg )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    
     Vec4i testConst3 = -testConst1;
    
    ASSERT_EQ(testConst3[0], -10 );
    ASSERT_EQ(testConst3[1], -20 );
    ASSERT_EQ(testConst3[2], -30 );
    ASSERT_EQ(testConst3[3], -40 );
}

TEST(P(Vec4iTest), OperatorMulVec )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 20, 40, 80, 160 );
    
     Vec4i testConst3 = testConst1 * testConst2;
    
    ASSERT_EQ(testConst3[0], 10*20 );
    ASSERT_EQ(testConst3[1], 20*40 );
    ASSERT_EQ(testConst3[2], 30*80 );
    ASSERT_EQ(testConst3[3], 40*160 );
}

TEST(P(Vec4iTest), OperatorMulConst )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    
    Vec4i testConst3 = testConst1 * 10;
    
    ASSERT_EQ(testConst3[0], 100 );
    ASSERT_EQ(testConst3[1], 200 );
    ASSERT_EQ(testConst3[2], 300 );
    ASSERT_EQ(testConst3[3], 400 );
    
    Vec4i testConst4 = 10 * testConst1;
    
    ASSERT_EQ(testConst4[0], 100 );
    ASSERT_EQ(testConst4[1], 200 );
    ASSERT_EQ(testConst4[2], 300 );
    ASSERT_EQ(testConst4[3], 400 );
}

TEST(P(Vec4iTest), OperatorDivConst )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    
    Vec4i testConst3 = testConst1 / 5;
    
    ASSERT_EQ(testConst3[0], 2 );
    ASSERT_EQ(testConst3[1], 4 );
    ASSERT_EQ(testConst3[2], 6 );
    ASSERT_EQ(testConst3[3], 8 );
}

TEST(P(Vec4iTest), OperatorDivVec )
{
    Vec4i testConst1( 10, 20, 30, 40 );
    Vec4i testConst2( 2, 4, 6, 8 );
    
    Vec4i testConst3 = testConst1 / testConst2;
    
    ASSERT_EQ(testConst3[0], 5 );
    ASSERT_EQ(testConst3[1], 5 );
    ASSERT_EQ(testConst3[2], 5 );
    ASSERT_EQ(testConst3[3], 5 );
}